#include "Window.h"
#include "../Render/2D/Segment/Segment.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Window::Window(const char *title, int width, int height)
	:m_closed(false),
	m_title(title),
	m_width(width),
	m_height(height),
	m_window(nullptr),
	m_renderer(nullptr),
	m_camera(new Camera(Vec3<float>(width/2, height/2, 5), Vec3<float>(width / 2, height / 2, 0)))
{
	if (!init())
	{
		m_closed = true;
	}
}

Window::~Window()
{
	delete m_camera;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void Window::pollEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_closed = true;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_closed = true;
				break;
			}
		default:
			break;
		}
	}
}

void Window::clear() const
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
}

void Window::clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}

void drawLine(int x1, int y1, int x2, int y2, const Color &color)
{

}

void Window::render()
{
	Matrix4x4<float> proj = Matrix4x4<float>::perspective(70, 1.0, 0.01, 1000.0);
	Matrix4x4<float> view = m_camera->getView();
	Matrix4x4<float> mvp = proj * view;
	for (auto seg : m_objects)
	{
		Segment *s = dynamic_cast<Segment *>(seg);
		Vec4<float> newA = (mvp * s->getA().toVec4(1));
		Vec4<float> newB = (mvp * s->getB().toVec4(1));

		Vec3<float> a3 = newA.toVec3();
		Vec3<float> b3 = newB.toVec3();

		Vec2<float> a2(a3.x / a3.z, a3.y / a3.z);
		Vec2<float> b2(b3.x / b3.z, b3.y / b3.z);

		Vec2<int> A(newA.x, newA.y), B(newB.x + 0.9, newB.y + 0.9);
		if (A > B) std::swap(A, B);
		//drawLine(A.x, A.y, B.x, B.y, s->getColor());
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(m_renderer, A.x, A.y, B.x, B.y);
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
		SDL_RenderDrawLine(m_renderer, 40, 30, 400, 300);
	}
	SDL_RenderPresent(m_renderer);
}

void Window::rayTracing()
{
	//SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//SDL_RenderDrawLine(m_renderer, 10, 0, 410, 300);
	Vec3<float> eyePosition(m_width / 2, m_height / 2, 10);
	Vec3<float> intersection;
	for (int j = 0; j < m_height; ++j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			Ray ray(eyePosition, Vec3<float>(i, j, 0) - eyePosition);
			for (Renderable *obj : m_objects)
			{
				if (obj->intersectWithRay(ray, intersection))
				{
					Color resColor = obj->getColor(); //* (eyePosition.distance(intersection) / 10);

					SDL_SetRenderDrawColor(m_renderer, resColor.red, resColor.green, resColor.blue, 255);
					SDL_RenderDrawPoint(m_renderer, i, j);
				}
			}
		}
	}

	SDL_RenderPresent(m_renderer);
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Something went wrong: " << SDL_GetError << "\n";
		return 0;
	}
	m_window = SDL_CreateWindow(
		m_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_width,
		m_height,
		0
	);

	if (m_window == nullptr)
	{
		std::cerr << "Failed to create window: " << SDL_GetError << "\n";
		return 0;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer: " << SDL_GetError << "\n";
		return 0;
	}

	return true;
}
