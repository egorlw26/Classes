#include <iostream>

#include <GL/freeglut.h>

#include "Window/Window.h"

#include "Math/Math.h"
#include "Render/3D/Cube/Cube.h"

int main(int argc, char **argv)
{
	Window *win = new Window("Test", 800, 600);
	Light *light = new Light(Vec3<float>(2, 2, 2));
	Cube *box = new Cube(Vec3<float>(0, 90, -50), 5);

	win->addObject(box);
	win->addLight(light);

	while (!win->isClosed())
	{
		win->pollEvents();
		win->clear(0, 0, 0, 255);
		win->render();
		//win->rayTracing();
	}

	return 0;
}