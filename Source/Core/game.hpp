#pragma once

#include <glew/glew.h>
#include "glfw/glfw3.h"
#include <memory>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Graphics/sprite_renderer.hpp"
#include "resource_manager.hpp"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
    private:
        std::unique_ptr<SpriteRenderer> renderer;

    public:
        GameState State;
        std::array<bool, 1024> Keys;
        unsigned int width = 0;
        unsigned int height = 0;
        
        Game(unsigned int w, unsigned int h);
        ~Game();
        
        void init();
       
        void processInput(float dt);
        void update(float dt);
        void render();
};