#include "general.h"


Pair operator+(Pair a, Pair b)
{
	return {a.x + b.x, a.y + b.y};
}

Pair operator-(Pair a, Pair b)
{
	return {a.x - b.x, a.y - b.y};
}

Pair operator+=(Pair& a, Pair& b)
{
	return {a.x += b.x, a.y += b.y};
}
