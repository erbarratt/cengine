#include "Window.hpp"

#include <iostream>
#include <sstream>

namespace MM {
	Window::Window()
		:mWidth(800), mHeight(600), mFrameCount(0), mLastTime(glfwGetTime()), mCurrentTime(0)
	{}

	bool Window::Init()
	{

		std::cout << glGetString(GL_VERSION) << std::endl;

		//Initialize GLFW
			if (!glfwInit()) {
				return false;
			}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//get monitor res
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		std::cout << "Fullscreen Resolution: " << mode->width << "x" << mode->height << std::endl;

		GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Red Rocket Rage",  monitor, nullptr);
		if (!window) {
			glfwTerminate();
			std::cout << "GLFW Window Failed to Create." << std::endl;
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		mWindow = window;
		mWidth = mode->width;
		mHeight = mode->height;

		return true;

	}

	bool Window::shouldWindowlose() const
	{
		return glfwWindowShouldClose(mWindow);
	}

	void Window::SetWindowTitle(const char* title) const
	{
		glfwSetWindowTitle(mWindow, title);
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(mWindow);
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

	void Window::UpdateFrameRate()
	{
		// Measure time and update FPS counter
		mCurrentTime = glfwGetTime();
		mFrameCount++;

		if (mCurrentTime - mLastTime >= 1) { // 1 second has passed
			std::ostringstream title;
			title << "OpenGL Window - FPS: " << mFrameCount;
			SetWindowTitle(title.str().c_str());
			mFrameCount = 0;
			mLastTime = mCurrentTime;
		}
	}
} // MM