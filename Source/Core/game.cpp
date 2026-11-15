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
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cerr << "Current Working Dir: " << cwd << '\n';
    }

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

    renderer = std::make_unique<SpriteRenderer>(spriteShader);
    ResourceManager::loadTexture("Source/Assets/Textures/wx.png", "player");
}

void Game::update(float dt)
{

}
void Game::processInput(float dt)
{

}
void Game::render()
{
    renderer->drawSprite(
        ResourceManager::getTexture("player"),
        glm::vec2(200.0f, 200.0f),
        glm::vec2(300.0f, 400.0f),
        45.0f,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

Game::~Game()
{

}