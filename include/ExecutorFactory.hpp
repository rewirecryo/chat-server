#ifndef INCLUDED_CHATSERVER_EXECUTORFACTORY_HPP
#define INCLUDED_CHATSERVER_EXECUTORFACTORY_HPP

#include <memory>

#include "Executor.hpp"
#include "ExecutorTypes.hpp"
#include "Executors/ForwardMessageExecutor.hpp"
#include "Executors/FindUserExecutor.hpp"
#include "Executors/CreateUserExecutor.hpp"

class ExecutorFactory
{
public:
	static std::shared_ptr<Executor> create(ExecutorType type);
};

#endif
