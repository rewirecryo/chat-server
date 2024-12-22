#ifndef INCLUDED_CHATSERVER_INSTRUCTIONFACTORY_HPP
#define INCLUDED_CHATSERVER_INSTRUCTIONFACTORY_HPP

#include <memory>

#include "Instruction.hpp"
#include "../include/Instructions/ReceiveMessage.hpp"
#include "../include/Responses/CreateUser.hpp"
#include "../include/Responses/FindUser.hpp"
#include "Client.hpp"

class InstructionFactory
{
	using InstructionBacklog = std::map<size_t, std::shared_ptr<Instruction>>;
public:
	/**
	 * @brief Create an Instruction of a given type, add it to the instruction map, and
	 *
	 * @param type  Type of Instruction to create
	 *
	 * @return shared_ptr to the new instruction
	 */
	std::shared_ptr<Instruction> create(InstructionType type);

	std::shared_ptr<Instruction> add(std::shared_ptr<Instruction> new_ins);

	void send(Client *dest_client,  size_t instruction_id, bool should_fulfill = false);
	
	/**
	 * @brief Remove an instruction from the map
	 *
	 * @param instruction_id  Instruction to delete
	 */
	void fulfill(size_t instruction_id);

	std::shared_ptr<Instruction> getInstruction(size_t instruction_id);
	
private:
	size_t __next_id = 0;
	InstructionBacklog __instructions;
};

#endif
