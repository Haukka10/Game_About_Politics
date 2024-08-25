#pragma once

namespace Renderer
{
	class RenderClass
	{
		public:
			RenderClass() = default;
			void Render();

		private:
			bool OpenMakePolitics = false;
			bool OpenPropaganda = false;

			void RenderMakePolitics();
			void RenderPropagandaWindows();
	};
}