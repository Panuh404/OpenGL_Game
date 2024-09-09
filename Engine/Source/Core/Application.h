#pragma once

#include "Layer.h"
#include "LayerStack.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Camera.h"
#include "Renderer/Window.h"

namespace Quiet
{
	class Application
	{
	public:
		Application(const std::string& name);

		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();
}
