#pragma once

#include <framework/Exception.h>

class GameException : public Exception
{
public:
	GameException(int code, std::string value) : Exception(code, value)
	{
	}
	
	
};


class ObjectNotFoundException : public GameException
{
public:
	ObjectNotFoundException() : GameException(5, "Object not found in space")
	{
	}
	
};

