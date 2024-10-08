#ifndef INCLUDED_CHATSERVER_INSTRUCTION_HPP
#define INCLUDED_CHATSERVER_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

enum InstructionType
{
	UNKNOWN
};

class Instruction
{
public:
	virtual void fromJSON(const nlohmann::json &j) = 0;
	virtual nlohmann::json toJSON()const = 0;

	int getType()const;
	
private:
	const int __type = InstructionType::UNKNOWN;
};

#endif
