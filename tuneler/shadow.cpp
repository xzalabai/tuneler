
#include "shadow.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "house.h"
#include "asteroid.h"
#include "powerUp.h"
#include "torus.h"
#include "desk.h"
#include "projectile.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>


using namespace std;
using namespace glm;
using namespace ppgso;

Shadow::Shadow(int typeOfObj, int id) {

    // Scale the default model
    scale.x *= 1.0f;
    scale.y *= 1.0f;
    scale.z *= 0;
    position.z = 10;
    hits = 20;
    uniqueId = id;
    type = typeOfObj;

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("misko.bmp"));
    if (typeOfObj == 1)
    if (!mesh) mesh = make_unique<Mesh>("tank_final_2.obj");
    if (typeOfObj == 2)
        if (!mesh) mesh = make_unique<Mesh>("pokus4.obj");
    if (typeOfObj == 3)
        if (!mesh) mesh = make_unique<Mesh>("testAhoj.obj");
    if (typeOfObj == 4)
        if (!mesh) mesh = make_unique<Mesh>("strela.obj");
    if (typeOfObj == 5)
        if (!mesh) mesh = make_unique<Mesh>("torus_final_final.obj");
}

bool Shadow::update(Scene &scene, float dt) {

    position.x = (-1)*scene.lightDirection.x ;
    position.y = (-1)*scene.lightDirection.y ;
    position.z = 0.8f ;
    //printf("%f %f %f\n", scene.lightDirection.x,scene.lightDirection.y,scene.lightDirection.z);
    //TODO: set scale (bigger shadow)
/*
    scale.x = scene.lightDirection.x;
    scale.y = scene.lightDirection.y;
    scale = abs(scale);
    scale = adjustScale(scale);
*/
    //scale.y = adjustScale(abs(scene.lightDirection.y));

    for ( auto& obj : scene.objects ) {
        iHaveMyObject = false;
        // Ignore self in scene
        if (obj.get() == this)
            continue;
        // We only need to collide with asteroids, ignore other objects
        auto  player = dynamic_cast<Player *>(obj.get());
        auto  powerUp = dynamic_cast<PowerUp*>(obj.get());
        auto  house = dynamic_cast<House*>(obj.get());
        auto  ast = dynamic_cast<Asteroid*>(obj.get());
        auto  projectile = dynamic_cast<Projectile*>(obj.get());
        auto  torus = dynamic_cast<Torus*>(obj.get());
        //auto  house = dynamic_cast<House *>(obj.get());

        if (!player && !powerUp && !house && !ast && !projectile && !torus) continue;

        if (player){
            if (player->playerId == uniqueId && type == 1){
                iHaveMyObject = true;
                modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*player->modelMatrix *  glm::orientate4(rotation);
            }
        }

        if (powerUp){
            if (powerUp->uniqueId == uniqueId && type == 2){
                iHaveMyObject = true;
                modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*powerUp->modelMatrix *  glm::orientate4(rotation);
            }
        }
        if (house){
            if (house->id == uniqueId && type == 3){
                iHaveMyObject = true;
                modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*house->modelMatrix *  glm::orientate4(rotation);
                position.z = 0;
            }
        }
        if (projectile){
            if (type == 4 && uniqueId == projectile->uniqueId){
                modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*projectile->modelMatrix *  glm::orientate4(rotation);
            }
        }
        if (torus){
            if (type == 5 && uniqueId == torus->playerId){
                modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*torus->modelMatrix *  glm::orientate4(rotation);
            }
        }
        if (ast){
            //position.z = 10;
            modelMatrix = glm::translate(mat4(1.0f), position)*glm::scale(mat4(1.0f), scale)*ast->modelMatrix *  glm::orientate4(rotation);
        }
    }

    return true;
}


void Shadow::render(Scene &scene) {
 /*   glEnable(GL_DEPTH_TEST);
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
*/
   // glDepthMask(GL_TRUE);




     shader->use();

     // Set up light
    // shader->setUniform("LightDirection", scene.lightDirection);

     // use camera
     shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
     shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

     // render mesh
     shader->setUniform("ModelMatrix", modelMatrix);
     shader->setUniform("Texture", *texture);
     mesh->render();
}

vec3 Shadow::adjustScale(vec3 a){
    if (a.x < 1) a.x = 1;
    if (a.y < 1) a.y = 1;
    if (a.x > 2) a.x = 2;
    if (a.y > 2) a.y = 2;

    return a;
}

void Shadow::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}