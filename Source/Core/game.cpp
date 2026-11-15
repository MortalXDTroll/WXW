#include "game.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <direct.h>
#include <iostream>


Game::Game(unsigned int w, unsigned int h)
    : State(GAME_ACTIVE), Keys(), width(w), height(h)
{

}

void Game::init()
{
    //char cwd[1024];
    //if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
    //    std::cerr << "Current Working Dir: " << cwd << '\n';
    //}

    Shader& spriteShader = ResourceManager::loadShader(
        "Source/Shaders/vshader.vert",
        "Source/Shaders/fshader.frag",
        nullptr,
        "sprite"
    );

    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(width),
        static_cast<float>(height), 0.0f,
        -1.0f, 1.0f
    );

    spriteShader.use();
    spriteShader.setInt("image", 0);
    spriteShader.setMat4("projection", projection);

    Shader& shapeShader = ResourceManager::loadShader(
        "Source/Shaders/shape.vert",
        "Source/Shaders/shape.frag",
        nullptr,
        "shape"
    );
    shapeShader.use();
    shapeShader.setMat4("projection", projection);

    spriteRenderer = std::make_unique<SpriteRenderer>(spriteShader);
    shapeRenderer = std::make_unique<ShapeRenderer>(shapeShader);
    ResourceManager::loadTexture("Source/Assets/Textures/wx.png", "player");
}

void Game::update(float dt)
{

}
void Game::processInput(float dt)
{
    player.velocityX = 0.0f;
    if (Keys[GLFW_KEY_A]) {
        player.velocityX = -260.0f;
    }
    if (Keys[GLFW_KEY_D]) {
        player.velocityX = 260.0f;
    }

    if (Keys[GLFW_KEY_E] && !KeysProcessed[GLFW_KEY_E]) {
        player.clawsExtended = !player.clawsExtended;
        KeysProcessed[GLFW_KEY_E] = true;
    }
    else if (!Keys[GLFW_KEY_E]) {
        KeysProcessed[GLFW_KEY_E] = false;
    }

    if (Keys[GLFW_KEY_SPACE] && !player.isSpinning) {
        player.isSpinning = true;
        player.velocityY = -600.0f;
        player.clawsExtended = true;
    }

    player.update(dt);
}
void Game::render()
{
    //spriteRenderer->drawSprite(
    //    ResourceManager::getTexture("player"),
    //    glm::vec2(200.0f, 200.0f),
    //    glm::vec2(300.0f, 400.0f),
    //    45.0f,
    //    glm::vec3(0.0f, 1.0f, 0.0f)
    //);

    //shapeRenderer->drawQuad(
    //    glm::vec2(400.0f, 560.0f),
    //    glm::vec2(800.0f, 80.0f),
    //    0.0f,
    //    glm::vec4(0.18f, 0.20f, 0.24f, 1.0f)
    //);
    //shapeRenderer->drawCircle(
    //    glm::vec2(200.0f, 300.0f),
    //    glm::vec2(50.0f, 50.0f),
    //    0.0f,
    //    glm::vec4(0.95f, 0.78f, 0.20f, 1.0f)
    //);
    //shapeRenderer->drawTriangle(
    //    glm::vec2(200.0f, 250.0f),
    //    glm::vec2(40.0f, 35.0f),
    //    0.0f,
    //    glm::vec4(0.12f, 0.14f, 0.20f, 1.0f)
    //);

    shapeRenderer->drawQuad(glm::vec2(400.0f, 560.0f), glm::vec2(800.0f, 80.0f), 0.0f, glm::vec4(0.18f, 0.20f, 0.24f, 1.0f));
    player.draw(*shapeRenderer);

}

Game::~Game()
{

}