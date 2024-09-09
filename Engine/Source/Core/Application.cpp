#include "Quiet_PCH.h"
#include "Application.h"

#include "Input.h"


namespace Quiet
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		s_Instance = this;
		WindowProps props = {
			"Test",
			1600,
			1200,
		};
		m_Window = std::make_unique<Window>(props);
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	void Application::Run()
	{
		// Application Loop
		while (m_Running)
		{
			// Time step
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Exit
			if (Input::IsKeyPressed(Key::Escape))
			{
				m_Running = false;
			}

			if (!m_Minimized)
			{
				{
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);					
				}
			}

			// Window
			m_Window->SetVSync(true);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return false;
	}
}
