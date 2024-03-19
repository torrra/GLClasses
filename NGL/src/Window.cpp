#include <iostream>

#include "Window.h"

void ngl::InitContext(int major, int minor)
{
    // Initialize GLFW context (= state)
    glfwInit();

    // Set major OpenGL version for the next glfwCreateWindow call (3.x)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);

    // Set minor openGL version (x.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

    // Set OpenGL profile (core = modern only)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

ngl::Window::Window(int width, int height, const char* title)
{
    // Create window
    m_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Test if generation was successful
    if (!m_ptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }


    // Set current context (window) for this thread
    glfwMakeContextCurrent(m_ptr);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }



    glViewport(0, 0, width, height);

    // Register resize callback
    glfwSetFramebufferSizeCallback(m_ptr, ResizeWindow);
}

void ngl::ResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool ngl::CheckError()
{
    if (glGetError() != GL_NO_ERROR)
        return false;

    return true;
}

void ngl::ClearErrors()
{
    while (glGetError());

    return;
}

void ngl::BreakOnError()
{
    if (!CheckError())
        __debugbreak();
}

bool ngl::Window::ShouldClose() const
{
    return !glfwWindowShouldClose(m_ptr);
}

ngl::Window::operator bool() const
{
    return !glfwWindowShouldClose(m_ptr);
}
