#ifndef INCLUDED_CHATSERVER_BASEEXECUTOR_HPP
#define INCLUDED_CHATSERVER_BASEEXECUTOR_HPP

#include "Context.hpp"
#include "InstructionFactory.hpp"

class Executor
{
public:
	virtual int execute(const nlohmann::json &recvd_instruction, Client *src_client, Context *context, InstructionFactory *factory = nullptr) = 0;
};

#endif
