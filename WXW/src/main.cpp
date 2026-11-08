#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/shader.h"
#include "../include/vao.h"
#include "../include/vbo.h"
#include "../include/ebo.h"
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "WXW", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Shader shader("resources/shaders/vshader.vs", "resources/shaders/fshader.fs");

    float vertices[] = {
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    VAO vao;
    vao.bind();

    VBO vbo(sizeof(vertices), vertices, GL_STATIC_DRAW);
    vbo.bind();

    EBO ebo(sizeof(indices), indices, GL_STATIC_DRAW);
    ebo.bind();

    vao.link(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    shader.use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setVec4("color", 0.5f, 0.5f, 0.3f, 1.0f);

        vao.bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
