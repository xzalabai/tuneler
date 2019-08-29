//
// Created by Tibor on 15.11.2018.
//

#include "gulicka.h"
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

Gulicka::Gulicka(int a, float tex) {

    // Scale the default model
    scale *= 45.5f;
   // scale *= linearRand(1.2f, 1.7f);;
   // hits = 20;

    int usedTexture = tex;
    // printf("%d", usedTexture);
    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);

    if (usedTexture == 0)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("blue.bmp"));

    if (usedTexture == 1)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("green.bmp"));

    if (usedTexture == 2)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("grey.bmp"));

    if (usedTexture == 3)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("red.bmp"));

    if (!mesh) mesh = make_unique<Mesh>("pokus4.obj");
    //  materials = make_unique<tinyobj::MaterialFileReader>("testAhoj.mtl");
}

bool Gulicka::update(Scene &scene, float dt) {
    position.z += 0.21f;
   // printf("%f", position.z);
    return true;
}

void Gulicka::render(Scene &scene) {
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
    shader->setUniform("Texture", *texture);
    mesh->render();

    glDepthMask(GL_TRUE);

    /* shader->use();
 shader->setUniform("Transparency", 0.1f);
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

void Gulicka::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}