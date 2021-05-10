#include "StatePlay.h"

//include Libgfx
#include "ResourceGFX.h" 
#include "Resources/Scene.h"
#include "Resources/LightManager.h"
#include "GameManager.h"
#pragma warning(push)
#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include "App.h"
#include "GameManager.h"

StatePlay::StatePlay()
{
											/*Init Lights*/
	//----------------------------------------------------------------------------------------------
	LowRenderer::LightManager::DirectionalLight({ -0.2f, -1.f, -0.3f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 0.2f, 0.2f, 0.2f });
	//----------------------------------------------------------------------------------------------
}

StatePlay::~StatePlay()
{
	if (m_sound != nullptr)
	{
		m_sound->drop();
	}
}

void StatePlay::OnBegin(GLFWwindow* window)
{
	m_currentState = GameState::PLAY;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//---------------------InitSounds------------------------//
	m_sound = App::GetGameManager().MutateSound().Play2D("resources/Sounds/game.ogg", true);
	App::GetGameManager().MutateSound().Volume(m_sound, m_gameMusicVolume);

	Core::Maths::vec3 enemypos = App::GetGameManager().MutateWorld().m_zombie->GetPosition();
	App::GetGameManager().MutateWorld().m_zombie->m_sound = App::GetGameManager().MutateSound().Play3D("resources/Sounds/zombie.ogg", enemypos, true);
	App::GetGameManager().MutateSound().SetDistance(App::GetGameManager().MutateWorld().m_zombie->m_sound, 4.f);
	App::GetGameManager().MutateSound().Volume(App::GetGameManager().MutateWorld().m_zombie->m_sound, m_volumeEnemies);

}

GameState StatePlay::OnUpdate(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime)
{
	if (App::GetGameManager().GetIsPauseUI())
	{
		App::GetGameManager().MutateInventoryManager().ClearCraft(App::GetGameManager().MutateWorld().m_player.GetMutateInventory());
		App::GetGameManager().SetInInventory(false);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		PauseGame(window, windowWidth, windowHeight);

	}
	else if(App::GetGameManager().GetWorld().m_player.GetHealth() <= 0.f)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		DisplayDeathScreen((float)windowWidth, (float)windowHeight);
	}
	else
	{
		if (App::GetGameManager().GetInInventory())
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			DisplayInventory((float)windowWidth, (float)windowHeight);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			GameUI((float)windowWidth, (float)windowHeight);
		}

		/*Draw Wireframe*/
		WireFrameGFX(App::GetGameManager().m_cameraSettings.m_wireframe);

		/*Update*/
		App::GetGameManager().MutateWorld().m_player.Update(deltaTime);
		App::GetGameManager().MutateWorld().m_zombie->Update(deltaTime);
		App::GetGameManager().MutateScene().UpdateScene(deltaTime);
		App::GetGameManager().MutateWorld().Render();

		/*Update PositionSound*/
		App::GetGameManager().MutateSound().SetListenerPosition(App::GetGameManager().MutateWorld().m_scene->m_camera);
		if (App::GetGameManager().MutateWorld().m_zombie->MutateLifeComponent().isDead())
		{
			App::GetGameManager().MutateWorld().m_zombie->m_sound->stop();
		}

		/*Set Material*/
		//----------------------------------------------------------------------------------------------
		//http://devernay.free.fr/cours/opengl/materials.html /*READ...:)*/
		App::GetGameManager().MutateScene().m_shader.SetVec3({ 1.f, 1.f, 1.f }, "material.ambient", App::GetGameManager().MutateScene().m_shader.GetID());

		App::GetGameManager().MutateScene().m_shader.SetVec3({ 1.0f, 0.5f, 0.31f }, "material.diffuse", App::GetGameManager().MutateScene().m_shader.GetID());

		App::GetGameManager().MutateScene().m_shader.SetVec3({ 0.2f, 0.2f, 0.2f }, "material.specular", App::GetGameManager().MutateScene().m_shader.GetID());

		App::GetGameManager().MutateScene().m_shader.SetFloat(1000.f, "material.shininess", App::GetGameManager().MutateScene().m_shader.GetID());
		//----------------------------------------------------------------------------------------------


		/*Update light values in Shader*/
		LowRenderer::LightManager::UpdateShader(App::GetGameManager().MutateScene().m_shader.GetID());
	}
	return m_currentState;
}

void StatePlay::OnEnd()
{
	App::GetGameManager().MutateSound().StopAllMusics();
	App::GetGameManager().MutateWorld().Clear();
}

//-------------------------Game UI Functions-------------------------------//
void StatePlay::GameUI(const float width, const float height)
{
	/*Check Player Water*/
	if (App::GetGameManager().MutateWorld().m_player.isInWater())
	{
		WaterUI(width, height);
	}

	ConfigWindowGameUI(width, height);
	//--- UI CrossHair ---//
	DisplayCrossHair(width, height, "resources/Images/Game/csgo.png");
	//--- UI Life Player ---//
	DisplayLifePlayer(width, height, "resources/Images/Game/playerLife.png");
	//--- UI Inventory ---//
	DisplayHotBar(width, height);

	ImGui::End();
}

void StatePlay::ConfigWindowGameUI(const float width, const float height)
{
	bool gameUI = true;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize({ width, height });
	ImGui::Begin("MENU", &gameUI, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
}

void StatePlay::DisplayCrossHair(const float width, const float height, const char* path)
{
	/*the last parameter of the sound function is the width/height of the Crosshair
			the value are multiplied by the window width/window Height*/
	App::GetGameManager().MutateUI().Crosshair(width, height, path, 0.08f, 0.125f);
}

void StatePlay::DisplayLifePlayer(const float width, const float height, const char* path)
{
	App::GetGameManager().MutateUI().DisplayLifePlayer(width, height, path);
}

void StatePlay::DisplayHotBar(const float width, const float height)
{
	auto inventory = App::GetGameManager().MutateWorld().m_player.GetInventory().GetObjectList();
	App::GetGameManager().MutateUI().HotBar(width, height, inventory);
}
//--------------------------------------------------------------------------//

void StatePlay::DisplayInventory(const float width, const float height)
{
	/*Render World*/
	App::GetGameManager().MutateWorld().Render();
	App::GetGameManager().MutateUI().Inventory(width, height, App::GetGameManager().MutateWorld().m_player.GetMutateInventory());
}

//----------------------------------Pause UI Functions------------------------------------------------//
void StatePlay::PauseGame(GLFWwindow* window, const int windowWidth, const int windowHeight)
{
	App::GetGameManager().MutateUI().m_countPush = 0;

	float width = (float)windowWidth;
	float height = (float)windowHeight;

	if (App::GetGameManager().GetIsSettingsUI())
	{
		App::GetGameManager().SetIsSettingsUI(App::GetGameManager().MutateSettings().Run((float)windowWidth, (float)windowHeight, window));
	}
	else
	{
		/*Render World*/
		App::GetGameManager().MutateWorld().Render();

		//Create Window ImGUI
		ConfigWindowPause(width, height);
		ButtonResume(width, height);
		ButtonOptions(width, height);
		ButtonMenu(width, height);
		ButtonSaveAndQuit(width,height);

		ImGui::PopStyleColor(App::GetGameManager().MutateUI().m_countPush);
		ImGui::End();
	}
}

void StatePlay::ConfigWindowPause(const float width, const float height)
{
	m_pause = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::SetNextWindowBgAlpha(0.002f);//---------------->Set alpha window
	ImGui::Begin("Settings", &m_pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
}

void StatePlay::ButtonResume(float width, float height)
{
	//----- Buttton "RESUME" ------//
	if (App::GetGameManager().MutateUI().Button(width * 0.4546f, height * 0.4f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button.jpg","Back to Game"))
	{
		m_currentState = GameState::PLAY;
		App::GetGameManager().SetIsPauseUI(false);
	}
}

void StatePlay::ButtonOptions(float width, float height)
{
	//----- Buttton "Settings" ------//
	if (App::GetGameManager().MutateUI().Button(width * 0.4546f, height * 0.5f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button2.jpg", "SETTINGS"))
	{
		App::GetGameManager().SetIsSettingsUI(true);
	}
}

void StatePlay::ButtonMenu(float width, float height)
{
	//----- Buttton "Menu" ------//
	if (App::GetGameManager().MutateUI().Button(width * 0.4546f, height * 0.6f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button3.jpg", "Back to Menu"))
	{
		m_currentState = GameState::MENU;
		App::GetGameManager().SetIsPauseUI(false);
	}
}

void StatePlay::ButtonSaveAndQuit(const float width, const float height)
{
	if (App::GetGameManager().MutateUI().Button(width * 0.4546f, height * 0.7f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button6.jpg", "Save and Back to Menu"))
	{
		App::GetGameManager().SaveGame();
		m_currentState = GameState::MENU;
		App::GetGameManager().SetIsPauseUI(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------//

//---------------------------Death Screen------------------------------------//
void StatePlay::ConfigWindowDeath(const float width, const float height)
{
	bool windowDead = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::SetNextWindowBgAlpha(0.005f);//---------------->Set alpha window
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.005f));
	App::GetGameManager().MutateUI().m_countPush += 1;
	ImGui::Begin("wallpaper", &windowDead, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
}

void StatePlay::DisplayDeathScreen(const float width, const float height)
{
	App::GetGameManager().MutateUI().m_countPush = 0;

	ConfigWindowDeath(width, height);

	App::GetGameManager().MutateUI().Text({ width * 0.45f, height * 0.2f }, App::GetGameManager().MutateUI().m_bigFont, "You Die");

	if (App::GetGameManager().MutateUI().Button(width * 0.454f, height * 0.6143f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button3.jpg", "Back to Menu"))
	{
		m_currentState = GameState::MENU;
		App::GetGameManager().SetIsPauseUI(false);
	}
	if (App::GetGameManager().MutateUI().Button(width * 0.454f, height * 0.5f, width * 0.1364f, height * 0.0357f, "resources/Images/Menu/Button.jpg", "Respawn"))
	{
		m_currentState = GameState::PLAY;
		App::GetGameManager().MutateWorld().m_player.SetHealth(100);
	}

	ImGui::PopStyleColor(App::GetGameManager().MutateUI().m_countPush);
	ImGui::End();
}

void StatePlay::WaterUI(const float width, const float height)
{
	bool water = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::SetNextWindowBgAlpha(0.3f);//---------------->Set alpha window
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 1.0f, 0.01f));
	App::GetGameManager().MutateUI().m_countPush += 1;
	ImGui::Begin("water", &water, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PopStyleColor();
	ImGui::End();
}

