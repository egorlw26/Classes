#pragma once

struct Color
{
public:
	Color(float r, float g, float b);

private:
	float red;
	float green;
	float blue;

public:
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color White;
	static const Color Black;
};

