#pragma once

#include "Event/Event.h"

namespace Quiet
{
	//-----------------------------------------------------------------------------
	// [EVENT] Window Resize
	//----------------------------------------------------------------------------- 
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

		uint32_t GetWidth()		const { return m_Width; }
		uint32_t GetHeight()	const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	//-----------------------------------------------------------------------------
	// [EVENT] Window Close
	//-----------------------------------------------------------------------------
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//-----------------------------------------------------------------------------
	// [EVENT] App Tick
	//-----------------------------------------------------------------------------
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//-----------------------------------------------------------------------------
	// [EVENT] App Update
	//-----------------------------------------------------------------------------
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//-----------------------------------------------------------------------------
	// [EVENT] App Render
	//-----------------------------------------------------------------------------
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
