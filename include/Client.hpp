#ifndef INCLUDED_GRAW_CLIENT_HPP
#define INCLUDED_GRAW_CLIENT_HPP

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>


#include "Message.hpp"
#include "NetworkError.hpp"

class Message;
class Client
{
public:
	Client(int fd);

	/**
	 * @brief Kick a client off the server
	 */
	void kick();

	/**
	 * @brief Send a properly-formatted message to this client
	 *
	 * @param msg Message to send
	 */
	void sendMessage(const Message &msg);

private:
	int __fd;
};

#endif
