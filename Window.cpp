#include "Window.h"
#include <iostream>

Window::Window(const char *title, int weight, int height)
	: m_title(title), m_weight(weight), m_height(height)
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
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 200, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Window::getRenderer()
{
	return m_renderer;
}

SDL_Window* Window::getWindow()
{
	return m_window;
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
		m_weight,
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
