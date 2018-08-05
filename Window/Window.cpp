#include "Window.h"
#include <iostream>

Window::Window(const char *title, int width, int height)
	:m_closed(false),
	m_title(title),
	m_width(width),
	m_height(height),
	m_window(nullptr),
	m_renderer(nullptr)
{
	if (!init())
	{
		m_closed = true;
	}
}

Window::~Window()
{
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

void Window::render()
{
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			if (i != j) continue;
			SDL_SetRenderDrawColor(m_renderer, i % 255, j % 255, (i + j) % 255, 255);
			SDL_RenderDrawPoint(m_renderer, i, j);
		}
	}
	SDL_RenderPresent(m_renderer);
}

void Window::rayTracing()
{
	Vec3<float> eyePosition(m_width / 2, m_height / 2, 10.1);
	Vec3<float> intersection;
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			Ray ray(eyePosition, Vec3<float>(i, j, 0) - eyePosition);
			for (Renderable *obj : m_objects)
			{
				if (obj->intersectWithRay(ray, intersection))
				{
					Color resColor = obj->getColor(); //* (eyePosition.distance(intersection) / 10);
					for (Light *light : m_lights)
					{

					}
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
