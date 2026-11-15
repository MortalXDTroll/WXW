#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shape_renderer.hpp"

struct Wolverine {
    glm::vec2 position{ 200.0f, 455.0f };
    float groundY = 455.0f;
    float facing = 1.0f;

    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float runTime = 0.0f;

    bool clawsExtended = true;
    float clawExtend = 1.0f;

    bool isSpinning = false;
    float spinAngle = 0.0f;

    void update(float dt);
    void draw(const ShapeRenderer& renderer) const;
};