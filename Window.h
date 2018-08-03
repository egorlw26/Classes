#pragma once
#include <vector>
#include "SDL.h"

class Window
{
public:
	Window(const char *title, int weight, int height);
	~Window();

	void pollEvents();
	void clear() const;

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	inline bool isClosed() const { return m_closed; };

private:
	bool init();

	bool m_closed = false;
	const char *m_title;
	int m_weight;
	int m_height;
	SDL_Window *m_window = nullptr;
	SDL_Renderer *m_renderer = nullptr;
};
