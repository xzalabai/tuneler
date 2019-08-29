//
// Created by Tibor on 03.11.2018.
//

#ifndef PPGSO_SHADOW_H
#define PPGSO_SHADOW_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "player.h"
#include "object.h"

class Shadow final : public Object {
private:
     std::unique_ptr<ppgso::Mesh> mesh;
     std::unique_ptr<ppgso::Shader> shader;
     std::unique_ptr<ppgso::Texture> texture;

public:
    Shadow(int typeOfObj, int id);

    glm::vec3 adjustScale(glm::vec3 x);

    int direction = 0;

    int uniqueId;
    int type;
    bool iHaveMyObject = false;

    int hits;
    glm::vec3 startingPosition;
    bool collisionDetected = false;

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
    void destroy();
};

#endif //PPGSO_SHADOW_H
