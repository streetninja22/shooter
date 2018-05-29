#pragma once


struct Pair
{
	int x;
	int y;
};



Pair operator+(Pair a, Pair b);

Pair operator-(Pair a, Pair b);

Pair operator+=(Pair& a, Pair& b);
