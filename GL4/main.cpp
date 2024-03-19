#include <cmath>

#include <iostream>

#include "NGL/NGraphics.h"


int main()
{
    ngl::InitContext(4, 5);


    ngl::Window window(800, 600, "Test");


    ngl::Program program1;


    program1.ImportShader("program1.vert", GL_VERTEX_SHADER);
    program1.ImportShader("program1.frag", GL_FRAGMENT_SHADER);


    program1.Link();

    float vertices[] =
    {
        // Position				// Color			// Texture coordinates
         0.5f,  0.5f, 0.0f,		1.f, 0.f, 0.f,		1.f, 1.f,
         0.5f, -0.5f, 0.0f,		0.f, 1.f, 0.f,		1.f, 0.f,
        -0.5f, -0.5f, 0.0f,		0.f, 0.f, 1.f,		0.f, 0.f,
        -0.5f,  0.5f, 0.0f,		0.f, 0.5f, 1.f,		0.f, 1.f
    };


    unsigned int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };



    unsigned int positionID = 0, colorID = 1, texID = 2;

    // Create VAO
    ngl::VAO vao;

    // Create and fill VBO
    ngl::VBO vbo(sizeof(vertices), vertices);


    // Create and fill EBO
    ngl::EBO ebo(sizeof(indices), indices);

    // Equivalent to glVertexAttribPointer, set attribute 0 (pos) position
    vao.SetAttribute(positionID, 3, 0, 0);


    // Set attribute 1 (color) position
    vao.SetAttribute(colorID, 3, 3 * sizeof(float), 0);

    // Set attribute 2 (texture coords) position
    vao.SetAttribute(texID, 2, 6 * sizeof(float), 0);

    // Bind VBO to VAO
    vao.BindVBO(vbo, 0, 0, 8 * sizeof(float));

    // Bind EBO to VAO
    vao.BindEBO(ebo);

    ngl::Sampler sampler;

    ngl::Texture texture1("peak.png");
    ngl::Texture texture2("hi.png");

    texture1.BindToUnit(0, sampler);
    texture2.BindToUnit(1, sampler);

    ngl::BreakOnError();

    while (window)
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program1.Use();

        ngl::BreakOnError();

        float time = static_cast<float>(glfwGetTime());
        float opacity = sinf(time) * 0.5f + 0.5f;

        program1.SetUniform("texture1", 0);
        program1.SetUniform("texture2", 1);

        program1.SetUniform("alpha", opacity);

        ngl::BreakOnError();

        vao.Draw(GL_TRIANGLES, 6);

        glfwSwapBuffers(window.m_ptr);
        glfwPollEvents();
    }

    vbo.Delete();
    ebo.Delete();
    vao.Delete();

    program1.Delete();

    ngl::BreakOnError();

    glfwTerminate();



    return 0;
}
