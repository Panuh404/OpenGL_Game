#include "Quiet_PCH.h"
#include "Application.h"
#include "Game.h"

int main()
{
	Quiet::Log::Init();

	// Application Startup
	auto m_Application = Quiet::Application("Game");
	m_Application.PushLayer(new Quiet::Game());

	// Runtime Application
	m_Application.Run();


	return 0;
}
