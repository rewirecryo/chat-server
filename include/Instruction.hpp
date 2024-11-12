#ifndef INCLUDED_CHATSERVER_INSTRUCTION_HPP
#define INCLUDED_CHATSERVER_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

#include "Client.hpp"
#include "InstructionTypes.hpp"
#include "Context.hpp"

class Instruction
{
public:
	Instruction(Client *src_cli);

	virtual void fromJSON(const nlohmann::json &j) = 0;
	virtual nlohmann::json toJSON()const = 0;

	int getType()const;

	virtual void execute() = 0;

	/**
	 * Client that sent this instruction
	 */
	Client *source_client = nullptr;

	/**
	 * Clients that this instruction is targeting
	 */
	std::vector<Client*> target_clients;

	/**
	 * The list of clients to broadcast to, if this instruction broadcasts anything
	 */
	std::map<int, Client> *broadcast_clients = nullptr;

	Context *context = nullptr;

private:
	const int __type = InstructionType::UNKNOWN;
};

#endif
