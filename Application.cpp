#include <GL\glew.h>

#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>  // to read file
#include <string>   // To use getline func
#include <sstream>
#include <math.h>


#include "Renderer.h"


#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



int main(void)
{
    /* GLFW BASIC STUFF */
        GLFWwindow* window;

        /* Initialize the GLFW library */
        if (!glfwInit())
            return -1;


        /* setting version 3.3 and core profile (i.e mordern opengl) */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;

        }
        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);    /* controls FPS or intervel between buffer(frames) */

    /*  END BASIC GLFW   */


    /* Intitialize GLEW */
        if (glewInit() != GLEW_OK) {
            std::cout << "Error!" << std::endl;
        }
    /* END */

    std::cout << glGetString(GL_VERSION) << std::endl;  /* prints the version of opengl using */



    /* ------------- Generating Data to be used to display in the window ------------- */
        
        /* ------------- Vertex Info (like position, color, texture, smoothness, normal,etc) ------------- */
    {
        // 4 positions of vertices of sqaure
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,   // 0
             0.5f, -0.5f, 1.0f, 0.0f,   // 1
             0.5f,  0.5f, 1.0f, 1.0f,   // 2
            -0.5f,  0.5f, 0.0f, 1.0f    // 3
        };

        // Index data -----> position in which vertices is to be rendered to form a square
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        shader.SetUniformsMat4f("u_MVP", proj);

        Texture texture("res/textures/CrossHair.png");
        texture.Bind();
        shader.Bind();
        shader.SetUniforms1i("u_Texture", 0);
        
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;


        /* ----------- Animation Variable ----------- */
        float r = 0.0f;
        float increment = 0.05f;



        /* WHILE Loop to keep the window active till window is closed */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */

            renderer.Clear();
            
            shader.Bind();
            shader.SetUniforms4f("u_Color", r, 0.2f, 0.5f, 1.0f);

            renderer.Draw(va, ib, shader);


            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

