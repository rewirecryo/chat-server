#ifndef INCLUDED_CHATSERVER_SERVER_HPP
#define INCLUDED_CHATSERVER_SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <poll.h>
#include <unistd.h>

#include "Client.hpp"
#include "InstructionHandler.hpp"
#include "InstructionFactory.hpp"

#define TRANSPORT_PROTOCOL_TCP 6
#define SERVER_SOCKET_BACKLOG 3
#define POLL_TIMEOUT_MS 250
#define RECV_BUF_SIZE 1024

class Server
{
public:
	/**
	 * @brief Start listening for new connections
	 *
	 * @param listen_addr Address to bind to
	 * @param port Port to bind to
	 */
	void listen(const std::string &listen_addr, unsigned short port);
		
	/**
	 * @brief Shut down the server
	 */
	void close();

	/**
	 * @brief Remove the client associated with a given file descriptor
	 *
	 * @param fd - File descriptor with which the client is associated
	 */
	void removeClient(int fd);
	
private:
	/**
	 * @brief Accept any clients that are trying to connect
	 */
	void checkForNewClients();

	/**
	 * @brief Set all the client-associated pollfd structs to be ready for another poll() call
	 */
	void resetPollFDs();

	/**
	 * @brief Start accepting connections and talking with clients
	 */
	void __startLoop();
		
private:
	short port;
	int __fd = -1;
	std::vector<struct pollfd> __client_sockfds;
	std::map<int, Client> __clients;
	bool __running = false;
	Context __context;
	std::shared_ptr<InstructionHandler> __instruction_handler;
};

#endif
