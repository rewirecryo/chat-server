#ifndef INCLUDED_CHATSERVER_FORWARDMESSAGEEXECUTOR_HPP
#define INCLUDED_CHATSERVER_FORWARDMESSAGEEXECUTOR_HPP

#include <nlohmann/json.hpp>

#include "../Instruction.hpp"
#include "../Context.hpp"
#include "../Executor.hpp"

class Client;
class InstructionFactory;
class ForwardMessageExecutor : public Executor
{
public:
	int execute(const nlohmann::json &recvd_instruction, Client *src_client, Context *context, InstructionFactory *factory = nullptr);
};
#endif
