#include <deque>
#include <iostream>
#include <memory>
#include <vector>

#include "gl.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include <SDL.h>

#include "Camera.h"
#include "Cube.h"
#include "Grid.h"
#include "Input.h"
#include "Light.h"
#include "Model.h"
#include "Quad.h"
#include "Screen.h"
#include "Shader.h"
#include "Utility.h"

auto isLit = false;
auto isAppRunning = true;

const auto SCREEN_WIDTH = 1920;
const auto SCREEN_HEIGHT = 1080;
const auto CONSOLE_WINDOW_HEIGHT = 250;
const auto PROPERTIES_WINDOW_WIDTH = 400;

std::deque<std::string> messages;
std::vector<std::unique_ptr<Object>> objects;

void RenderConsoleWindow()
{
	ImGui::Begin("Output console", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
	
	auto windowPos = ImVec2(0, SCREEN_HEIGHT - CONSOLE_WINDOW_HEIGHT - 25);
	auto windowSize = ImVec2(SCREEN_WIDTH - PROPERTIES_WINDOW_WIDTH, CONSOLE_WINDOW_HEIGHT);

	ImGui::SetWindowPos("Output console", windowPos);
	ImGui::SetWindowSize("Output console", windowSize);

	auto message = Utility::ReadMessage();
	
	if (!message.empty())
	{
		messages.push_front(message);
	}

	for (const auto& message : messages)
	{
		ImGui::Text(message.c_str());
	}

	ImGui::End();
}

void RenderPropertiesWindow()
{
	ImGui::Begin("Properties", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	auto windowPos = ImVec2(SCREEN_WIDTH - PROPERTIES_WINDOW_WIDTH, 0);
	auto windowSize = ImVec2(PROPERTIES_WINDOW_WIDTH, SCREEN_HEIGHT);

	ImGui::SetWindowPos("Properties", windowPos);
	ImGui::SetWindowSize("Properties", windowSize);

	auto position = objects[0]->GetTransform().GetPosition();
	ImGui::SliderFloat3("Position", &position.x, -10.0f, 10.0f, "%.2f");
	objects[0]->GetTransform().SetPosition(position.x, position.y, position.z);

	auto rotation = objects[0]->GetTransform().GetRotation();
	ImGui::SliderFloat3("Rotation", &rotation.x, -360.0f, 360.0f, "%.2f");
	objects[0]->GetTransform().SetRotation(rotation.x, rotation.y, rotation.z);

	auto scale = objects[0]->GetTransform().GetScale();
	ImGui::SliderFloat3("Scale", &scale.x, 0.001f, 10.0f, "%.2f");
	objects[0]->GetTransform().SetScale(scale.x, scale.y, scale.z);

	ImGui::Separator();

	ImGui::Button("Crate 1 texture");
	ImGui::Button("Crate 2 texture");
	
	ImGui::Separator();

	auto isTextured = objects[0]->IsTextured();
	ImGui::Checkbox("Textured", &isTextured);
	objects[0]->IsTextured(isTextured);
	
	ImGui::Checkbox("Light the scene", &isLit);

	ImGui::Separator();

	auto color = objects[0]->GetColor();
	ImGui::ColorEdit4("Color", &color.r);
	objects[0]->SetColor(color);

	ImGui::Separator();
	ImGui::End();
}

int main(int argc, char* argv[])
{
	if (!Screen::Instance()->Initialize())
	{
		return 0;
	}
	
	if (!Shader::Initialize())
	{
		return 0;
	}

	Shader defaultShader;
	defaultShader.Create("Shaders/Default.vert", "Shaders/Default.frag");

	Shader lightShader;
	lightShader.Create("Shaders/Light.vert", "Shaders/Light.frag");

	//================================================================

	Grid grid;
	
	//objects.push_back(std::make_unique<Quad>("Floor.jpg", &grid));
	objects.push_back(std::make_unique<Cube>("Crate_1.png", &grid));
	//objects.push_back(std::make_unique<Cube>("Crate_2.png", &grid));
	//objects.push_back(std::make_unique<Model>("Models/Armchair.obj", &grid));
	
	Camera camera;
	camera.Set3DView();
	camera.SetSpeed(0.5f);
	camera.SetViewport(0,
			           CONSOLE_WINDOW_HEIGHT,
			           SCREEN_WIDTH - PROPERTIES_WINDOW_WIDTH,
			           SCREEN_HEIGHT - CONSOLE_WINDOW_HEIGHT);
		
	Light light;
	light.SetSpeed(0.5f);

	ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/Arial.ttf", 16.0f);
	ImGui::GetIO().Fonts->Build();

	SDL_Rect mouseCollider = { 0 };
	SDL_Rect sceneCollider = { 0,
							   0,
							   SCREEN_WIDTH - PROPERTIES_WINDOW_WIDTH,
							   SCREEN_HEIGHT - CONSOLE_WINDOW_HEIGHT };

	//================================================================

	while (isAppRunning)
	{
		Screen::Instance()->ClearScreen();
		Input::Instance()->Update();

		mouseCollider = { static_cast<int>(Input::Instance()->GetMousePosition().x),
						  static_cast<int>(Input::Instance()->GetMousePosition().y),
						  1,
						  1 };

		bool isMouseColliding = SDL_HasIntersection(&mouseCollider, &sceneCollider);

		if (Input::Instance()->GetMouseWheel() > 0)
		{
			camera.MoveForward();
		}

		else if (Input::Instance()->GetMouseWheel() < 0)
		{
			camera.MoveBackward();
		}

		//==================================================================

		if (Input::Instance()->GetKeyDown() == 'w')
		{
			light.MoveForward();
		}

		else if (Input::Instance()->GetKeyDown() == 's')
		{
			light.MoveBackward();
		}

		else if (Input::Instance()->GetKeyDown() == 'a')
		{
			light.MoveLeft();
		}

		else if (Input::Instance()->GetKeyDown() == 'd')
		{
			light.MoveRight();
		}

		else if (Input::Instance()->GetKeyDown() == 'q')
		{
			light.MoveUp();
		}

		else if (Input::Instance()->GetKeyDown() == 'e')
		{
			light.MoveDown();
		}

		//==================================================================
		
		if (isMouseColliding && Input::Instance()->IsLeftButtonClicked())
		{
			auto rotation = grid.GetTransform().GetRotation();
			rotation.x += Input::Instance()->GetMouseMotion().x;
			rotation.y += Input::Instance()->GetMouseMotion().y;
			grid.GetTransform().SetRotation(rotation.x, rotation.y, rotation.z);
		}

		isAppRunning = !Input::Instance()->IsXClicked();

		defaultShader.Use();
		camera.SendToShader(defaultShader);
		
		grid.Render(defaultShader);
		light.Render(defaultShader);
		
		for (auto& object : objects)
		{
			if (isLit)
			{
				lightShader.Use();
				light.SendToShader(lightShader);
				camera.SendToShader(lightShader);
				object->Render(lightShader);
			}

			else
			{
				defaultShader.Use();
				camera.SendToShader(defaultShader);
				object->Render(defaultShader);
			}
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		RenderConsoleWindow();
		RenderPropertiesWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		Screen::Instance()->Present();
	}

	lightShader.Destroy();	
	defaultShader.Destroy();	

	Shader::Shutdown();
	Screen::Instance()->Shutdown();	
	
	return 0;
}