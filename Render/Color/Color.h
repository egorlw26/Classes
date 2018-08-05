#pragma once
#include <algorithm>

struct Color
{
public:
	Color(unsigned char r, unsigned char g, unsigned char b);

	Color operator *(float value);
	
	unsigned char red;
	unsigned char green;
	unsigned char blue;

public:
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color White;
	static const Color Black;
	static const Color Yellow;
};

