#include "general.h"


Vector operator+(Vector a, Vector b)
{
	return {a.x + b.x, a.y + b.y};
}

Vector operator-(Vector a, Vector b)
{
	return {a.x - b.x, a.y - b.y};
}

Vector operator+(Vector a, double b)
{
	return {a.x + b, a.y + b};
}

Vector operator-(Vector a, double b)
{
	return {a.x - b, a.y - b};
}

Vector operator+=(Vector& a, Vector& b)
{
	return {a.x += b.x, a.y += b.y};
}

Vector operator*(Vector a, double b)
{
	return {a.x * b, a.y * b};
}

Vector operator/(Vector a, double b)
{
	return{ a.x / b, a.y / b };
}
