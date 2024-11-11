#ifndef INCLUDED_CHATSERVER_INSTRUCTIONFACTORY_HPP
#define INCLUDED_CHATSERVER_INSTRUCTIONFACTORY_HPP

#include <memory>

#include "Instruction.hpp"
#include "Message.hpp"
#include "Client.hpp"

class InstructionFactory
{
public:
	static Instruction *create(Client *client, InstructionType type);
};

#endif
