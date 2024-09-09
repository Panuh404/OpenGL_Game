#include "Quiet_PCH.h"
#include "Application.h"

int main()
{
	Quiet::Log::Init();

	// Application Startup
	auto m_Application = Quiet::Application("Game");

	// Runtime Application
	m_Application.Run();


	return 0;
}