#ifndef PPGSO_POWERUP_H
#define PPGSO_POWERUP_H
#pragma once
#include <ppgso/ppgso.h>
#include <memory>
#include "scene.h"
#include "object.h"

class PowerUp final : public Object {

private:
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;

public:
    float age{0.0f};
    bool iamDown = false;
    float gravityDown;
    float gravityUp;
    int uniqueId;

    PowerUp(int colorOfPowerUp, int id);

    int colorOfPowerUp = 1;

    void render(Scene &scene) override;
    void gravity(Scene &scene, float dt, float floor);

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;

    void destroy();
};


#endif //PPGSO_HOUSE_H
