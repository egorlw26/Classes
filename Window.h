#pragma once

#include <GL/freeglut.h>
#include <functional>

class Window
{
public:
	Window(int *argc, char **argv,int xPos,int yPos, int width, int height, const char *title);
	void clear();
	void render(void(*func)());
	void pollEvents();	

private:
	int m_xPos;
	int m_yPos;
	int m_width;
	int m_height;
	char *m_title;

	void (*m_render)();
};
