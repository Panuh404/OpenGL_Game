#include "Quiet_PCH.h"
#include "Application.h"

int main()
{
	Quiet::Log::Init();
	auto m_Application = Quiet::Application("Game");
	m_Application.Run();
	m_Application.Shutdown();
	return 0;
}