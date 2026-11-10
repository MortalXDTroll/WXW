#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <array>

#include "../include/shader.h"
#include "../include/vao.h"
#include "../include/vbo.h"
#include "../include/ebo.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);

int width = 640;
int height = 480;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "WXW", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Shader shader("resources/shaders/vshader.vs", "resources/shaders/fshader.fs");
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    //std::array<float, 9> vertices = {
    //     0.5f, -0.5f, 0.0f,
    //    -0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f
    //};

    //std::array<unsigned int, 6> indices = {
    //    0, 1, 2,
    //    3, 4, 5
    //};


    std::array<float, 24> menuLines = {
        // Horizontal Line
        -0.20f, 0.025f, 0.0f,  
        0.20f, 0.025f, 0.0f, 
        -0.20f, -0.025f, 0.0f,  
        0.20f, -0.025f, 0.0f, 

        // Vertical Line
         -0.025f, 0.20f, 0.0f,
        0.025f, 0.20f, 0.0f,
        -0.025f, -0.20f, 0.0f,
        0.025f, -0.20f, 0.0f
    };

    std::array<unsigned int, 12> linesOrder = {
        // Horizontal Line
        0, 1, 2,
        2, 1, 3,

        // Vertical Line
        4, 5, 6,
        6, 5, 7
    };


    VAO vao;
    vao.bind();

    VBO vbo(menuLines.size() * sizeof(float), menuLines.data(), GL_STATIC_DRAW);
    vbo.bind();

    EBO ebo(linesOrder.size() * sizeof(unsigned int), linesOrder.data(), GL_STATIC_DRAW);
    ebo.bind();

    vao.link(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    shader.use();

    float xLineH = 1.0f;
    float yLineH = 1.0f;

    float xLineV = 1.0f;
    float yLineV = 1.0f;

    float move_speed = 0.2f;
    const float line_limit = -0.95f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 modelH = glm::mat4(1.0f);
        glm::mat4 modelV = glm::mat4(1.0f);

        if (yLineH > line_limit) {
            yLineH -= move_speed * deltaTime;
            if (yLineH < line_limit) {
                yLineH = line_limit;
            }
        }

        if (xLineV > line_limit) {
            xLineV -= move_speed * deltaTime;
            if (xLineV < line_limit) {
                xLineV = line_limit;
            }
        }

        modelH = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, yLineH, 0.0f));
        modelV = glm::translate(glm::mat4(1.0f), glm::vec3(xLineV, 0.0f, 0.0f));
        

        shader.use();
        shader.setVec4f("color", 0.5f, 0.5f, 0.3f, 1.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        vao.bind();

        shader.setMat4("model", modelH);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shader.setMat4("model", modelV);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    if (h == 0) return;
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}