#include "GLWindow.hpp"
#include <iostream>
namespace graf
{
    void GLWindow::statickeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer(window);

         pWindow->m_keyboardFunction(key,scancode,action);
    }
    void GLWindow::setKeyboardFunction(KeyboardFunction keyboardFunction)
    {
        m_keyboardFunction = keyboardFunction;
    }
    int GLWindow::create(unsigned int width,unsigned int height)
    {
        if(!glfwInit())
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
       
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, "My Title", NULL, NULL);

        if (!m_window )
        {
            // Window or OpenGL context creation failed
        }
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }  
        glEnable(GL_DEPTH_TEST); 
        glfwSetWindowUserPointer(m_window,this);
        glfwSetKeyCallback(m_window,statickeyboardFunction);
        return 1;
    }
    void GLWindow::setRenderFunction(RenderFunction render)
    {
        m_renderFunction = render;
    }
    void GLWindow::render()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            m_renderFunction();
            
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

}