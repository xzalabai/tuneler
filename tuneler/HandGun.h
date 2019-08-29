//
// Created by Tibor on 27.10.2018.
//

#ifndef PPGSO_HANDGUN_H
#define PPGSO_HANDGUN_H
#pragma once
#include <ppgso/ppgso.h>
using namespace glm;
#include <memory>
#include "scene.h"
#include "object.h"

struct Keyframe {
    vec3 keyframePosition = {0, 0, 0};
    vec3 keyframeRotation = {0, 0, 0};
    vec3 keyframeScale = {1, 1, 1};
    float duration = 100;
};

class HandGun final : public Object {
private:
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;

public:
    Keyframe keyframeAnimation[5];
    int keyframeCount = 4;
    float keyframeDuration = 0;
    int processedKeyframes = 0;
    HandGun(int colorOfPowerUp, vec3 pos);

    int hits;

    vec3 linearInterpolation(vec3 a, vec3 b, float t);

    void render(Scene &scene) override;

    void onClick(Scene &scene) override ;

    bool update(Scene &scene, float dt) override;
    void destroy();
};


#endif //PPGSO_HANDGUN_H
