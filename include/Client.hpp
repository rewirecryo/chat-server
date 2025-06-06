#ifndef INCLUDED_CHATSERVER_CLIENT_HPP
#define INCLUDED_CHATSERVER_CLIENT_HPP

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <nlohmann/json.hpp>

#include "NetworkError.hpp"

class Client
{
public:
	Client(int fd);

	/**
	 * @brief Kick a client off the server
	 */
	void kick();

	/**
	 * @brief Send text to this client
	 *
	 * @param msg Message to send
	 */
	void send(const void *buf, size_t size);

	void send(const nlohmann::json &j);


private:
	int __fd;
};

#endif
