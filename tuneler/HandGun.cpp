//
// Created by Tibor on 27.10.2018.
//

#include "HandGun.h"

#include "house.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
//unique_ptr<Mesh> HandGun::mesh;
//unique_ptr<Texture> HandGun::texture;
//unique_ptr<Shader> HandGun::shader;
vector<tinyobj::material_t> HandGun::material;
map<std::string, int> HandGun::material_map;

HandGun::HandGun(int a, vec3 pos) {

    // Scale the default model
    scale *= 2.5f;
    hits = 20;

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (a == 1)
    if (!texture) texture = make_unique<Texture>(image::loadBMP("handgun_texture.bmp"));
    if (a == 2)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("handgun_texture_green.bmp"));

    if (!mesh) mesh = make_unique<Mesh>("handgun.obj");
    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
    position = pos;

    keyframeAnimation[0].duration = 100;
    keyframeAnimation[0].keyframePosition = {position.x, position.y, position.z};
    // First keyframe
    keyframeAnimation[1].duration = 100;
    keyframeAnimation[1].keyframeRotation = {2, 1, 2};
    keyframeAnimation[1].keyframeScale = {scale.x, scale.y, scale.z};
    keyframeAnimation[1].keyframePosition = {position.x, position.y, position.z - 0.2f};
    // Second keyframe
    keyframeAnimation[2].duration = 100;
    keyframeAnimation[2].keyframeRotation = {6, 6, 5};
    keyframeAnimation[2].keyframeScale = {scale.x, scale.y, scale.z};
    keyframeAnimation[2].keyframePosition = {position.x, position.y, position.z - 0.4f};
    // Third keyframe
    keyframeAnimation[3].duration = 100;
    keyframeAnimation[3].keyframeRotation = {5, 2, 3};
    keyframeAnimation[3].keyframeScale = {scale.x, scale.y, scale.z};
    keyframeAnimation[3].keyframePosition = {position.x, position.y, position.z - 0.2f};


}

bool HandGun::update(Scene &scene, float dt) {

    Keyframe current = keyframeAnimation[processedKeyframes];
    Keyframe next = keyframeAnimation[(processedKeyframes + 1) % keyframeCount];
    float t = keyframeDuration / current.duration;
    position = linearInterpolation(current.keyframePosition, next.keyframePosition, t);
    scale = linearInterpolation(current.keyframeScale, next.keyframeScale, t);
    rotation = linearInterpolation(current.keyframeRotation, next.keyframeRotation, t);
    keyframeDuration++;
    if (keyframeDuration >= current.duration) {
        keyframeDuration = 0;
        processedKeyframes = (processedKeyframes + 1) % keyframeCount;
    }


    generateModelMatrix();
    return true;
}

void HandGun::render(Scene &scene) {
    vec3 ambient = vec3(material.data()->ambient[0], material.data()->ambient[1], material.data()->ambient[2]);
    vec4 diffuse = vec4(material.data()->diffuse[0], material.data()->diffuse[1], material.data()->diffuse[2], 1.0f);
    vec3 specular = vec3(material.data()->specular[0], material.data()->specular[1], material.data()->specular[2]);
    float shininess = material.data()->shininess * 128;
    glEnable(GL_DEPTH_TEST);
    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->use();
    shader->setUniform("LightDirection", scene.lightDirection);
    shader->setUniform("LightColor", scene.lightColor);
    shader->setUniform("AmbientLightColor", scene.ambientLightColor);
    shader->setUniform("CameraPosition", scene.camera->position);
    // Pass UV mapping offset to the shader

    // Render mesh, not using any projections, we just render in 2D
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("MaterialAmbient", {ambient.x, ambient.y, ambient.z});
    shader->setUniform("MaterialDiffuse", {diffuse.x, diffuse.y, diffuse.z, 1.0f});
    shader->setUniform("MaterialSpecular", {specular.x, specular.y, specular.z});
    shader->setUniform("MaterialShininess", shininess);
    shader->setUniform("Texture", *texture);
    mesh->render();

    glDepthMask(GL_TRUE);
   /* shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();*/
}

vec3 HandGun::linearInterpolation(vec3 a, vec3 b, float t){
    vec3 result = (1 - t) * a + t * b;
    return result;
}

void HandGun::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}
