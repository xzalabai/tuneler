//
// Created by Tibor on 15.11.2018.
//

#ifndef PPGSO_GULICKA_H
#define PPGSO_GULICKA_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "object.h"

class Gulicka final : public Object {
private:
    std::unique_ptr<ppgso::Mesh> mesh;
    //std::unique_ptr<ppgso::Mesh> materials;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
    std::vector<tinyobj::material_t> materials;

public:
    Gulicka(int colorOfPowerUp, float texture);

    int hits;

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
    void destroy();
};

#endif //PPGSO_GULICKA_H
