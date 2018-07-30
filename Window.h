#pragma once

class Window
{
public:
	Window();
	Window(int &argc, char **argv, int width, int height, const char *title);
	void init();

	void clean();
	void render();

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

	void reshape();



private:
	int m_Width;
	int m_Height;
	const char *m_Title;
};
