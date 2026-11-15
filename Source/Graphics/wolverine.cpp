#include "wolverine.hpp"
#include <cmath>
#include <algorithm>

namespace {
    glm::mat4 makeLimb(const glm::mat4& parent, glm::vec2 pivot, float angle, glm::vec2 offset, glm::vec2 size) {
        glm::mat4 m = glm::translate(parent, glm::vec3(pivot, 0.0f));
        m = glm::rotate(m, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::translate(m, glm::vec3(offset, 0.0f));
        return glm::scale(m, glm::vec3(size, 1.0f));
    }
}

void Wolverine::update(float dt) {
    position.x += velocityX * dt;

    if (velocityX != 0.0f) {
        facing = (velocityX > 0.0f) ? 1.0f : -1.0f;
        if (!isSpinning) {
            runTime += dt * 12.0f;
        }
    }
    else if (!isSpinning) {
        runTime = 0.0f;
    }

    float targetClaw = clawsExtended ? 1.0f : 0.0f;
    clawExtend += glm::clamp(targetClaw - clawExtend, -6.0f * dt, 6.0f * dt);

    if (isSpinning) {
        velocityY += 1400.0f * dt;
        position.y += velocityY * dt;
        spinAngle += 720.0f * dt;

        if (position.y >= groundY) {
            position.y = groundY;
            velocityY = 0.0f;
            isSpinning = false;
            spinAngle = 0.0f;
        }
    }
}

void Wolverine::draw(const ShapeRenderer& renderer) const {
    const glm::vec4 yellow(0.95f, 0.78f, 0.12f, 1.0f);
    const glm::vec4 blue(0.10f, 0.28f, 0.68f, 1.0f);
    const glm::vec4 black(0.08f, 0.09f, 0.14f, 1.0f);
    const glm::vec4 skin(0.88f, 0.68f, 0.54f, 1.0f);
    const glm::vec4 gray(0.65f, 0.68f, 0.72f, 1.0f);

    float bobY = (!isSpinning && velocityX != 0.0f) ? -std::abs(std::sin(runTime)) * 5.0f : 0.0f;
    float legSwing = isSpinning ? 35.0f : (velocityX != 0.0f ? std::sin(runTime) * 42.0f : 0.0f);
    float armSwing = isSpinning ? -55.0f : (velocityX != 0.0f ? -std::sin(runTime) * 45.0f : 10.0f);

    glm::mat4 root = glm::mat4(1.0f);
    root = glm::translate(root, glm::vec3(position.x, position.y + bobY, 0.0f));
    root = glm::rotate(root, spinAngle * facing, glm::vec3(0.0f, 0.0f, 1.0f));
    root = glm::scale(root, glm::vec3(facing, 1.0f, 1.0f));

    renderer.drawQuad(makeLimb(root, glm::vec2(0.0f, 22.0f), -legSwing, glm::vec2(0.0f, 20.0f), glm::vec2(12.0f, 40.0f)), blue);
    renderer.drawQuad(makeLimb(root, glm::vec2(0.0f, -16.0f), -armSwing, glm::vec2(0.0f, 16.0f), glm::vec2(10.0f, 32.0f)), skin);

    renderer.drawQuad(makeLimb(root, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(28.0f, 46.0f)), yellow);
    renderer.drawCircle(makeLimb(root, glm::vec2(0.0f, -36.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(24.0f, 24.0f)), skin);
    renderer.drawTriangle(makeLimb(root, glm::vec2(-8.0f, -42.0f), -25.0f, glm::vec2(0.0f, -8.0f), glm::vec2(10.0f, 20.0f)), black);
    renderer.drawTriangle(makeLimb(root, glm::vec2(8.0f, -42.0f), 25.0f, glm::vec2(0.0f, -8.0f), glm::vec2(10.0f, 20.0f)), black);

    renderer.drawQuad(makeLimb(root, glm::vec2(0.0f, 22.0f), legSwing, glm::vec2(0.0f, 20.0f), glm::vec2(13.0f, 40.0f)), blue);

    glm::mat4 frontArmJoint = glm::translate(root, glm::vec3(0.0f, -16.0f, 0.0f));
    frontArmJoint = glm::rotate(frontArmJoint, armSwing, glm::vec3(0.0f, 0.0f, 1.0f));
    renderer.drawQuad(makeLimb(frontArmJoint, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 16.0f), glm::vec2(11.0f, 34.0f)), skin);

    if (clawExtend > 0.01f) {
        float clawLen = 24.0f * clawExtend;
        for (int i = -1; i <= 1; ++i) {
            glm::mat4 claw = makeLimb(
                frontArmJoint,
                glm::vec2(3.0f, 28.0f + i * 3.5f),
                90.0f + i * 3.0f,
                glm::vec2(0.0f, -clawLen * 0.5f),
                glm::vec2(3.0f, clawLen)
            );
            renderer.drawTriangle(claw, gray);
        }
    }
}