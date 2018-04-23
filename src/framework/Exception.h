#pragma once
#include <string>

class Exception
{
	int m_code;
	std::string m_value;

public:
	Exception(int code, std::string value) : m_code(code), m_value(value)
	{
	}

	int getCode()
	{
		return m_code;
	}

	const std::string& getValue()
	{
		return m_value;
	}
};