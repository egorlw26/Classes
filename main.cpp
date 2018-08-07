#include <iostream>
#include <chrono>

#include <GL/freeglut.h>

#include "Window/Window.h"

#include "Math/Math.h"
#include "Render/3D/Cube/Cube.h"
#include "Render/3D/Sphere/Sphere.h"
#include "Render/2D/Segment/Segment.h"

int main(int argc, char **argv)
{
	Window *win = new Window("Test", 800, 600);
	Light *light = new Light(Vec3<float>(2, 2, 2));
	Cube *box = new Cube(Vec3<float>(400, 300, 0), 10);
	Sphere *sphere = new Sphere(Vec3<float>(400, 300, 0), 10, Color::Red);
	Segment *ab = new Segment(Vec3<float>(0, 0, 0), Vec3<float>(100, 100, 0),Color::Green);
	Segment *ab1 = new Segment(Vec3<float>(0, 100, 0), Vec3<float>(100, 100, 0), Color::Green);
	Segment *ab2 = new Segment(Vec3<float>(50, 0, 0), Vec3<float>(100, 100, 0), Color::Green);
	Segment *ab3 = new Segment(Vec3<float>(100, 0, 0), Vec3<float>(100, 100, 0), Color::Green);

	//win->addObject(sphere);
	win->addObject(ab);
	win->addObject(ab1);
	win->addObject(ab2);
	win->addObject(ab3);
	win->addLight(light);

	while (!win->isClosed())
	{
		win->pollEvents();
		win->clear(0, 0, 0, 255);
		//win->render();
		auto t1 = std::chrono::high_resolution_clock::now();
		win->rayTracing();
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;
		std::cout << std::endl;
	}

	return 0;
}