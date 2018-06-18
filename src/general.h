#pragma once


struct Vector
{
	double x;
	double y;
};



Vector operator+(Vector a, Vector b);

Vector operator-(Vector a, Vector b);

Vector operator+=(Vector& a, Vector& b);

Vector operator*(Vector a, double b);

Vector operator/(Vector a, double b);