#ifndef INCLUDED_GRAW_EXCEPTIONS_HPP
#define INCLUDED_GRAW_EXCEPTIONS_HPP

#include <exception>

class NetworkError : public std::runtime_error
{
public:
	NetworkError(const std::string &str)
		: std::runtime_error(str)
	{
		__error_number = errno;
		__what_text = str;
	}

	const char *what()const noexcept
	{
		return __what_text.c_str();
	}

	int no()const
	{
		return __error_number;
	}
	
private:
	std::string __what_text = "";
	int __error_number = 0;
};

#endif
