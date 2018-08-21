#pragma once
#include <vector>
#include "SDL2/SDL.h"
#include "../Renderable.h"
#include "../Math/Math.h"
#include "../Light.h"
#include "Camera.h"

class Window
{
public:
	Window(const char *title, int widtt, int height);
	~Window();

	void pollEvents();
	void clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void clear() const;
	void render();
	void rayTracing();

	inline void addObject(Renderable *object) { m_objects.push_back(object); };
	inline void addLight(Light *light) { m_lights.push_back(light); };

	inline SDL_Renderer* getRenderer() const { return m_renderer; };
	inline SDL_Window* getWindow() const { return m_window; };
	inline bool isClosed() const { return m_closed; };

private:
	bool init();

	bool m_closed;
	const char *m_title;
	int m_width;
	int m_height;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	std::vector<Renderable *> m_objects;
	std::vector<Light *> m_lights;

	Camera *m_camera;
};
