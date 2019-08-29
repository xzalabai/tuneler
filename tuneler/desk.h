//
// Created by Tibor on 23.10.2018.
//

#ifndef PPGSO_DESK_H
#define PPGSO_DESK_H

#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "object.h"

class Desk final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;

public:
    Desk();

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
};




#endif //PPGSO_DESK_H
