#ifndef INCLUDED_CHATSERVER_MESSAGE_HPP
#define INCLUDED_CHATSERVER_MESSAGE_HPP

#include <nlohmann/json.hpp>
#include "Client.hpp"
#include "Instruction.hpp"

class Client;

class Message : public Instruction
{
public:
	void fromJSON(const nlohmann::json &j);

	/**
	 * @brief Convert this object to a JSON object
	 */
	nlohmann::json toJSON()const;

	Client *client = nullptr;
	std::string text;
};
#endif
