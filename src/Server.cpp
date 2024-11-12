#include "../include/Server.hpp"

void Server::listen(const std::string &listen_addr, unsigned short port)
{
	if(port == 0)
	{
		throw std::logic_error("Server::listen(): Cannot bind to port 0.");
	}

	// Initialize hints. Define what criteria we have for the addresses we want to be returned.
	struct addrinfo ai_base;
	memset(&ai_base, 0, sizeof(ai_base));
	ai_base.ai_family = AF_INET;
	ai_base.ai_socktype = SOCK_STREAM;
	ai_base.ai_protocol = TRANSPORT_PROTOCOL_TCP;

	// Actually get our address
	struct addrinfo *returned_ai = nullptr;
	int gai_success = getaddrinfo(listen_addr.c_str(), std::to_string(port).c_str(), &ai_base, &returned_ai);
	if(gai_success != 0)
	{
		throw NetworkError(gai_strerror(gai_success));
	}

	// Create a socket on which to listen
	int fd = socket(AF_INET, SOCK_STREAM, TRANSPORT_PROTOCOL_TCP);
	if(fd == -1)
	{
		throw NetworkError(strerror(errno));
	}

	int reuseaddr_yes = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_yes, sizeof(reuseaddr_yes));

	// Bind our socket to a local address
	if(bind(fd, returned_ai->ai_addr, returned_ai->ai_addrlen) == -1)
	{
		throw NetworkError(strerror(errno));
	}

	// Start listening on the socket
	if(::listen(fd, SERVER_SOCKET_BACKLOG) == -1)
	{
		throw NetworkError(strerror(errno));
	}

	__fd = fd;

	// Initialize our Context object
	__context.client_list = &__clients;
	__context.user_list = &__users;

	__startLoop();
}

void Server::close()
{
	for(size_t i = 0; i < __client_sockfds.size(); ++i)
	{
		shutdown(__client_sockfds[i].fd, SHUT_RDWR);
		char buf[RECV_BUF_SIZE];
		recv(__client_sockfds[i].fd, buf, RECV_BUF_SIZE - 1, 0);
		if(::close(__client_sockfds[i].fd))
		{
			throw NetworkError(strerror(errno));
		}
	}

	if(::close(__fd) == -1)
	{
		throw NetworkError(strerror(errno));
	}
}

void Server::__startLoop()
{
	__running = true;
	while(__running == true)
	{
		// Before doing anything else, accept any new clients
		checkForNewClients();

		// Only do this if there are actually clients on the line
		if(__clients.size() > 0)
		{
			struct pollfd returned_fds[__client_sockfds.size()];
			memcpy(returned_fds, __client_sockfds.data(), sizeof(struct pollfd) * __client_sockfds.size());

			// Check the sockets for activity
			int poll_result = poll(__client_sockfds.data(), __client_sockfds.size(), POLL_TIMEOUT_MS);
			if(poll_result == -1)
			{
				throw NetworkError(strerror(errno));
			}
			else if(poll_result > 0)
			{
				for(int i = 0; i < __client_sockfds.size(); ++i)
				{
					// Skip this client if there's no activity
					if(__client_sockfds[i].revents == 0)
					{
						continue;
					}

					// Receive the data the client's sending
					char buf[RECV_BUF_SIZE];
					int size = recv(returned_fds[i].fd, buf, RECV_BUF_SIZE - 1, 0);
					if(size == -1 || size == 0)
					{
						// Handle certain errno's a certain way
						if(size == -1)
						{
							if(errno != ECONNRESET)
							{
								throw NetworkError(strerror(errno));
								break;
							}
						}

						removeClient(returned_fds[i].fd);
						continue;
					}
					buf[size] = '\0';

					// Turn the received data into JSON
					nlohmann::json j;
					try
					{
						j = nlohmann::json::parse(buf);
					}
					catch(nlohmann::json::parse_error &e)
					{
						std::cerr << "JSON parsing error: Received malformed message: '" << buf << "'" << std::endl;
					}

					std::vector<std::shared_ptr<Instruction>> instruction_list;

					for(nlohmann::json &j_instruction : j)
					{
						if(j_instruction.contains("instruction_type") == false)
						{
							throw std::runtime_error("Tried to parse non-instruction JSON object as an instruction JSON object.");
						}

						std::shared_ptr<Instruction> ins = std::shared_ptr<Instruction>(InstructionFactory::create(nullptr, j_instruction["instruction_type"]));
						ins->fromJSON(j_instruction);
						instruction_list.push_back(ins);
					}

					// Turn the JSON into a Message object
					Client &c = __clients.at(returned_fds[i].fd);
					for(auto &i : instruction_list)
					{
						i->source_client = &c;
						i->broadcast_clients = &__clients;
					}

					try
					{
						__instruction_handler->handle(instruction_list);
					}
					catch(NetworkError &e)
					{
						if(e.no() == ECONNRESET)
						{
							__clients.erase(__clients.find(returned_fds[i].fd));
						}
					}
				}
			}
		}
	}
}

void Server::checkForNewClients()
{
	struct pollfd listening_pollfd;
	listening_pollfd.fd = __fd;
	listening_pollfd.events = POLLIN;

	int poll_result = poll(&listening_pollfd, 1, POLL_TIMEOUT_MS);
	if(poll_result == -1)
	{
		throw NetworkError(strerror(errno));
	}
	else if(poll_result > 0)
	{
		struct sockaddr client_addr;
		socklen_t client_addrlen = sizeof(client_addr);
		int new_client_fd = accept(listening_pollfd.fd, &client_addr, &client_addrlen);

		struct pollfd new_pollfd;
		new_pollfd.fd = new_client_fd;
		new_pollfd.events = POLLIN;
		__client_sockfds.push_back(new_pollfd);
		__clients.insert(std::make_pair(new_pollfd.fd, Client(new_pollfd.fd)));
	}
}

void Server::removeClient(int fd)
{
	__clients.erase(fd);
	for(auto iter = __client_sockfds.begin(); iter != __client_sockfds.end(); ++iter)
	{
		if((*iter).fd == fd)
		{
			__client_sockfds.erase(iter);
			break;
		}
	}
}
