#pragma once

#include <SDL.h>

class Screen
{

public:

	static Screen* Instance();

	bool Initialize();
	void ClearScreen() const;
	void Present() const;
	void Shutdown() const;

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	SDL_Window* m_window;
	SDL_GLContext m_context;

};