#include <iostream>
#include <string>
#include "../include/Server.hpp"

#define MIN_ARGC 2

Server server;

int main(int argc, char **argv)
{
	if(argc < MIN_ARGC)
	{
		std::cerr << "Usage: chat-server <listening_port>" << std::endl;
		return 1;
	}

	unsigned short port;
	try
	{
		port = std::stoi(argv[1]);
	}
	catch(const std::invalid_argument &e)
	{
		std::cerr << "Invalid port given." << std::endl;
		return 1;
	}
	catch(const std::out_of_range &e)
	{
		std::cerr << "Invalid port given." << std::endl;
		return 1;
	}

	server.listen("127.0.0.1", port);
	
	server.close();

	return 0;
}
