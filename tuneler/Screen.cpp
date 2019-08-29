//
// Created by Tibor on 27.10.2018.
//

#include "Screen.h"
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


Screen::Screen(int a) {

    // Scale the default model
    scale *= 4.5f;
    hits = 20;
    //printf("%d ",a);
    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (a == 3)
        if (!mesh) mesh = make_unique<Mesh>("white_won_battle.obj");
    if (a == 4)
        if (!mesh) mesh = make_unique<Mesh>("green_won_battle.obj");
    if (a == 2)
        if (!mesh) mesh = make_unique<Mesh>("green_player_won_round.obj");
    if (a == 1) //TODO: white player won
        if (!mesh) mesh = make_unique<Mesh>("whitePlayerWon_test.obj");
    if (!texture) texture = make_unique<Texture>(image::loadBMP("red.bmp"));
}

bool Screen::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Screen::render(Scene &scene) {
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
}

void Screen::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}