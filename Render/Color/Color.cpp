#include "Color.h"

const Color Color::Red(1, 0, 0);
const Color Color::Green(0, 1, 0);
const Color Color::Blue(0, 0, 1);
const Color Color::White(1, 1, 1);
const Color Color::Black(0, 0, 0);
const Color Color::Yellow(1, 1, 0);

Color::Color(float r, float g, float b)
	: red(r), green(g), blue(b)
{}