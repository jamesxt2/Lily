#include "llpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lily {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}