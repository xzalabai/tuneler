//
// Created by Tibor on 21.10.2018.
//

#ifndef PPGSO_TORUS_H
#define PPGSO_TORUS_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "player.h"
#include "object.h"


class Torus final : public Object {
public:
    Torus(int pId, int pCol);

    float age{0.0f};

    int playerId;

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;

private:
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;
};


#endif //PPGSO_TORUS_H
