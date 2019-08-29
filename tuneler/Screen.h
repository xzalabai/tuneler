//
// Created by Tibor on 27.10.2018.
//

#ifndef PPGSO_SCREEN_H
#define PPGSO_SCREEN_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "object.h"
class Screen final : public Object {
private:
     std::unique_ptr<ppgso::Mesh> mesh;
     std::unique_ptr<ppgso::Shader> shader;
     std::unique_ptr<ppgso::Texture> texture;

public:
    Screen (int colorOfPowerUp);

    int hits;

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
    void destroy();
};



#endif //PPGSO_SCREEN_H
