#ifndef GLWindow_hpp
#define GLWindow_hpp

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "functiontypes.hpp"

namespace graf
{
    class GLWindow
    {
    public:
        int create(unsigned int width,unsigned int height);
        void render();
        void setRenderFunction (RenderFunction function);
        void setKeyboardFunction(KeyboardFunction keyboardFunction);
    private:
        static void statickeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);
        GLFWwindow*         m_window;
        RenderFunction      m_renderFunction;
        KeyboardFunction    m_keyboardFunction;
    };
}


#endif