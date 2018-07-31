#include "Window.h"

Window::Window(int *argc, char **argv, int xPos, int yPos, int width, int height, const char *title)
{
	glutInit(argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Test");

	void(*changeSize)(int, int) = [](int w, int h) 
	{
		glMatrixMode(GL_PROJECTION);
		glViewport(0, 0, w, h);
		glMatrixMode(GL_MODELVIEW);
	};
	glutReshapeFunc(changeSize);
}

void Window::clear()
{
}

void Window::render(void (*func)())
{
	m_render = func;
	glutDisplayFunc(func);
}

void Window::pollEvents()
{

}
