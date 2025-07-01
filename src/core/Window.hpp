#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "GLFW/glfw3.h"

namespace MM {

class Window {
	public:
		Window();
		bool Init();
		GLFWwindow * mWindow{};
		unsigned int mWidth{}, mHeight{};

		[[nodiscard]] bool shouldWindowlose() const;
		void SetWindowTitle(const char* title) const;
		void SwapBuffers() const;
		void PollEvents() const;
		void UpdateFrameRate();
	private:
		int mFrameCount;
		double mLastTime, mCurrentTime;
};

} // MM

#endif //WINDOW_HPP
