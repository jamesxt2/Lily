#pragma once

#include "Lily/Layer.h"

#include "Lily/Events/KeyEvent.h"
#include "Lily/Events/MouseEvent.h"
#include "Lily/Events/ApplicationEvent.h"

namespace Lily {

	class LILY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override; 

		void Begin();
		void End();
	private:
		float m_Time{ 0.0f };
	};
}