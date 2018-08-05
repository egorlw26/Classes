#include "Color.h"

const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::White(255, 255, 255);
const Color Color::Black(0, 0, 0);
const Color Color::Yellow(255, 255, 0);

Color::Color(unsigned char r, unsigned char g, unsigned char b)
	: red(r), green(g), blue(b)
{}


Color Color::operator*(float value)
{
	if (value*red > 255)
		red = 255;
	else
		red = unsigned char(value*red);

	if (value * green > 255)
		green = 255;
	else
		green = unsigned char(value*green);

	if (value * blue > 255)
		blue = 255;
	else
		blue = unsigned char(value*blue);

	return *this;
}

Color operator +(const Color &left, const Color &right)
{
	int red = left.red;
	int green = left.green;
	int blue = left.blue;
	if (red + right.red > 255)
		red = 255;
	else
		red += right.red;

	if (green + right.green > 255)
		green = 255;
	else
		green += right.green;

	if (blue + right.blue > 255)
		blue = 255;
	else
		blue += right.blue;

	return Color(red, green, blue);
}