#include "DX12LibPCH.h"

#include <Application.h>
#include "Game.h"
#include "Window.h"

Game::Game(const std::wstring& name, int width, int height, bool vSync)
	: m_Name(name)
	, m_Width(width)
	, m_Height(height)
	, m_vSync(vSync)
{
}

Game::~Game()
{
	assert(!m_pWindow && "Use Game::Destroy() before destruction.");
}

bool Game::Initialize()
{
	//Check if DirectX Math library support.
	if (!DirectX::XMVerifyCPUSupport())
	{
		MessageBoxA(NULL, "Failed to verify DirectX Math library support.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	m_pWindow = Application::Get().CreateRenderWindow(m_Name, m_Width, m_vSync);
	m_pWindow->RegisterCallbacks(shared_from_this());
	m_pWindow->Show();

	return true;
}

void Game::Destroy()
{
	Application::Get().DestroyWindow(m_pWindow);
	m_pWindow.reset();
}
