#include "GL\freeglut.h"
#include <iostream>
#include <algorithm>

const int width = 800, height = 600;

struct Color
{
	int red, green, blue;
	Color(int r, int g, int b)
		: red(r), green(g), blue(b)
	{}

	friend Color operator*(const Color &col, double val)
	{
		if (val < 0) return Color(0, 0, 0);
		int r = std::min(255, int(col.red*val));
		int g = std::min(255, int(col.green*val));
		int b = std::min(255, int(col.blue*val));
		return Color(r, g, b);
	}

	friend Color operator+(const Color &first, const Color &second)
	{
		int r = std::min(255, first.red + second.red);
		int g = std::min(255, first.green + second.green);
		int b = std::min(255, first.blue + second.blue);
		return Color(r, g, b);
	}
};

struct Point
{
	int x;
	int y;
	Color color;

	Point(int _x, int _y, Color col = Color(1, 1, 1))
		:x(_x), y(_y), color(col)
	{}

	Point(const Point& other)
		: x(other.x), y(other.y), color(other.color)
	{}
};


void changeOrthoSize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 10);
	glMatrixMode(GL_MODELVIEW);
}

void changePerspectiveSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderLine(Point a, Point b)
{
	bool transpose = false;
	if (abs(a.x - b.x) < abs(a.y - b.y))
	{
		a = Point(a.y, a.x, a.color);
		b = Point(b.y, b.x, b.color);
		transpose = true;
	}
	if (a.x > b.x) std::swap(a, b);
	int dx = b.x - a.x;
	int dy = abs(b.y - a.y);
	int dk = dy * 2;
	int k = 0;
	int y = a.y;
	Color col = a.color;
	int dr = (b.color.red - a.color.red) * 2;
	int dg = (b.color.green - a.color.green) * 2;
	int db = (b.color.blue - a.color.blue) * 2;
	int rd = 0, gr = 0, bl = 0;
	for (int x = a.x; x <= b.x; x++)
	{
		glColor3f(col.red / 255.0, col.green / 255.0, col.blue / 255.0);
		if (transpose)
			glVertex2i(y, x);
		else
			glVertex2i(x, y);

		k += dk;
		rd += dr;
		gr += dg;
		bl += db;

		if (k > dx)
		{
			y += b.y > a.y ? 1 : -1;
			k -= dx * 2;
		}

		if (rd > dx)
		{
			col.red += b.color.red > a.color.red ? 1 : -1;
			rd -= dx * 2;
		}

		if (gr > dx)
		{
			col.green += b.color.green > a.color.green ? 1 : -1;
			gr -= dx * 2;
		}

		if (bl > dx)
		{
			col.blue += b.color.blue > a.color.blue ? 1 : -1;
			bl -= dx * 2;
		}
	}
}

void renderTriangle(Point a, Point b, Point c)
{
	if (a.y > b.y) std::swap(a, b);
	if (a.y > c.y) std::swap(a, c);
	if (b.y > c.y) std::swap(b, c);

	int totalH = c.y - a.y;
	for (int y = a.y; y <= c.y; y++)
	{
		bool secondHalf = (y >= b.y) ? true : false;
		int segmentH = (secondHalf ? c.y - b.y : b.y - a.y);
		double k1 = (y - a.y) / double(totalH);
		double k2 = (secondHalf ? y - b.y : y - a.y) / double(segmentH);
		int left = a.x + (c.x - a.x) * k1, right = (secondHalf ? b.x : a.x) + (secondHalf ? c.x - b.x : b.x - a.x)*k2;
		Color l = a.color * (1 - k1) + c.color*k1;
		Color r = (secondHalf ? b.color : a.color) * (1 - k2) + (secondHalf ? c.color : b.color)*k2;
		int dx = right - left;
		for (int x = left; x <= right; x++)
		{
			double k = (x - left) / double(dx);
			Color col = l * (1 - k) + r * k;
			glColor3f(col.red / 255.0, col.green / 255.0, col.blue / 255.0);
			glVertex2i(x, y);
		}
	}
}

void renderScene(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	renderTriangle(Point(-100, -100, Color(255, 0, 0)), Point(100, -50, Color(0, 255, 0)), Point(0, 100, Color(0, 0, 255)));
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2i(-300, -300);
	glColor3f(0, 1, 0);
	glVertex2i(-100, -250);
	glColor3f(0, 0, 1);
	glVertex2i(-200, -100);
	glEnd();

	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	//init glut and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);

	glutCreateWindow("Test");

	//callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeOrthoSize);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
