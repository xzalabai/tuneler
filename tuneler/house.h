#ifndef PPGSO_HOUSE_H
#define PPGSO_HOUSE_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "object.h"

class House final : public Object {
private:
    std::unique_ptr<ppgso::Mesh> mesh;
    //std::unique_ptr<ppgso::Mesh> materials;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
    std::vector<tinyobj::material_t> materials;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;

public:
    House(int colorOfPowerUp, float texture, int uniqueId);

    int hits;

    int id;

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
    void destroy();
};


#endif //PPGSO_HOUSE_H
