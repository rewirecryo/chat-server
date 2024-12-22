#include "../include/ExecutorFactory.hpp"

std::shared_ptr<Executor> ExecutorFactory::create(ExecutorType type)
{
	switch(type)
	{
	case ExecutorType::FORWARD_MESSAGE:
		return std::make_shared<ForwardMessageExecutor>();
		break;
		
	case ExecutorType::CREATE_USER:
		return std::make_shared<CreateUserExecutor>();
		break;

	case ExecutorType::FIND_USER:
		return std::make_shared<FindUserExecutor>();
		break;
		
	default:
		throw std::runtime_error("ExecutorFactory::create(): Tried to create instruction with invalid type.");
	}
}
