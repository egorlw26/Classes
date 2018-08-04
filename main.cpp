#include <iostream>

#include <GL/freeglut.h>

#include "Window/Window.h"

#include "Math/Math.h"

int main(int argc, char **argv)
{
	Window *win = new Window("Test", 800, 600);
	Light *light = new Light(Vec3<float>(2, 2, 2));

	while (!win->isClosed())
	{
		win->pollEvents();
		win->clear(0, 0, 0, 255);
		win->render();
	}

	return 0;
}