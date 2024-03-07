#include <iostream>
#include "imgui/imgui_impl_sdl.h"
#include "Input.h"

Input* Input::Instance()
{
	static Input* inputObject = new Input();
	return inputObject;
}

Input::Input()
{
	m_keyUp = 0;
	m_keyDown = 0;
	m_mouseWheel = 0;

	m_isXClicked = false;
	m_isKeyPressed = false;

	m_isLeftButtonClicked = false;
	m_isRightButtonClicked = false;
	m_isMiddleButtonClicked = false;

	m_mouseMotion = glm::vec2(0.0f);
	m_mousePosition = glm::vec2(0.0f);
}

bool Input::IsXClicked() const
{
	return m_isXClicked;
}

bool Input::IsKeyPressed() const
{
	return m_isKeyPressed;
}

char Input::GetKeyUp() const
{
	return m_keyUp;
}

char Input::GetKeyDown() const
{
	return m_keyDown;
}

bool Input::IsLeftButtonClicked() const
{
	return m_isLeftButtonClicked;
}

bool Input::IsRightButtonClicked() const
{
	return m_isRightButtonClicked;
}

bool Input::IsMiddleButtonClicked() const
{
	return m_isMiddleButtonClicked;
}

const glm::vec2& Input::GetMouseMotion() const
{
	return m_mouseMotion;
}

const glm::vec2& Input::GetMousePosition() const
{
	return m_mousePosition;
}

int Input::GetMouseWheel() const
{
	return m_mouseWheel;
}

void Input::Update()
{
	SDL_Event events;

	m_mouseWheel = 0;
	m_mouseMotion = glm::vec2(0.0f);
	m_mousePosition = glm::vec2(0.0f);

	m_keyDown = ' ';

	while (SDL_PollEvent(&events))
	{
		ImGui_ImplSDL2_ProcessEvent(&events);

		switch (events.type)
		{
			case SDL_QUIT:
			{
				m_isXClicked = true;
				break;
			}

			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				m_keyDown = events.key.keysym.sym;
				break;
			}

			case SDL_KEYUP:
			{
				m_isKeyPressed = false;
				m_keyUp = events.key.keysym.sym;
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_isLeftButtonClicked = true;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_isRightButtonClicked = true;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_isMiddleButtonClicked = true;
						break;
					}
				}

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_isLeftButtonClicked = false;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_isRightButtonClicked = false;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_isMiddleButtonClicked = false;
						break;
					}
				}

				break;
			}

			case SDL_MOUSEMOTION:
			{
				m_mouseMotion.y = static_cast<float>(events.motion.xrel);
				m_mouseMotion.x = static_cast<float>(events.motion.yrel);
				
				m_mousePosition.x = static_cast<float>(events.motion.x);
				m_mousePosition.y = static_cast<float>(events.motion.y);
				break;
			}

			case SDL_MOUSEWHEEL:
			{
				m_mouseWheel = events.wheel.y;
				break;
			}
		}
	}
}