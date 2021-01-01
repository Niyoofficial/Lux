#pragma once

namespace Lux
{
	class RenderingContext
	{
	public:
		RenderingContext() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
