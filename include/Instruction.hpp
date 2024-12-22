#ifndef INCLUDED_CHATSERVER_INSTRUCTION_HPP
#define INCLUDED_CHATSERVER_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

#include "Client.hpp"
#include "InstructionTypes.hpp"

class Instruction
{
public:
	Instruction();

	virtual nlohmann::json toJSON()const = 0;

	int getType()const;

	void setInstructionID(int new_id);
	int getInstructionID()const;

	int getRespondee()const;
	void setRespondee(int respondee_id);
	
protected:
	void __setType(InstructionType new_type);
	nlohmann::json __jsonTemplate()const;

	int __respondee = -1;
	int __instruction_id = -1;
	InstructionType __type = InstructionType::UNKNOWN;
};

#endif
