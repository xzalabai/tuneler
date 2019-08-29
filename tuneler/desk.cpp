//
// Created by Tibor on 23.10.2018.
//
#include "house.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"
#include "desk.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> Desk::mesh;
unique_ptr<Texture> Desk::texture;
unique_ptr<Shader> Desk::shader;
vector<tinyobj::material_t> Desk::material;
map<std::string, int> Desk::material_map;

Desk::Desk() {

    // Scale the default model
    scale *= 7.8f;
    scale.x /= 1.4;
    scale.y /= 1.2;

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("tableBMP.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("table_test.obj");
    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
}

bool Desk::update(Scene &scene, float dt) {
    position.z = 2.4f;
    generateModelMatrix();
    return true;
}

void Desk::render(Scene &scene) {
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

void Desk::onClick(Scene &scene) {

    cout << "Player has been clicked!" << endl;
}

