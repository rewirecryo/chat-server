#ifndef INCLUDED_CHATSERVER_FINDUSEREXECUTOR_HPP
#define INCLUDED_CHATSERVER_FINDUSEREXECUTOR_HPP

#include "../Executor.hpp"

class FindUserExecutor : public Executor
{
public:
	int execute(const nlohmann::json &recvd_instruction, Client *client, Context *context, InstructionFactory *factory = nullptr);
};

#endif
