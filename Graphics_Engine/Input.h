#pragma once

#include <glm.hpp>
#include <SDL.h>

class Input
{

public:

	static Input* Instance();

	bool IsXClicked() const;
	bool IsKeyPressed() const;

	char GetKeyUp() const;
	char GetKeyDown() const;
	int GetMouseWheel() const;

	bool IsLeftButtonClicked() const;
	bool IsRightButtonClicked() const;
	bool IsMiddleButtonClicked() const;

	const glm::vec2& GetMouseMotion() const;
	const glm::vec2& GetMousePosition() const;
	
	void Update();	

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

	char m_keyUp;
	char m_keyDown;

	int m_mouseWheel;
	bool m_isXClicked;
	bool m_isKeyPressed;

	bool m_isLeftButtonClicked;
	bool m_isRightButtonClicked;
	bool m_isMiddleButtonClicked;

	glm::vec2 m_mouseMotion;
	glm::vec2 m_mousePosition;

};