#ifndef INCLUDED_CHATSERVER_CREATEUSEREXECUTOR_HPP
#define INCLUDED_CHATSERVER_CREATEUSEREXECUTOR_HPP

#include "../Executor.hpp"
#include "../InstructionTypes.hpp"
#include "../InstructionFactory.hpp"

class CreateUserExecutor : public Executor
{
public:
	int execute(const nlohmann::json &j_ins, Client *src_client, Context *context, InstructionFactory *factory = nullptr);
};

#endif
