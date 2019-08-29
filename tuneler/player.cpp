#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "desk.h"
#include "camera.h"
#include "shadow.h"
#include "projectile.h"
#include "generator.h"
#include "explosion.h"
#include "house.h"
#include "torus.h"
#include "gulicka.h"
#include "powerUp.h"
#include "Screen.h"
#include "house.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <windows.h>
#include <chrono>
#include <ctime>

using namespace std;
using namespace glm;
using namespace ppgso;
vector<tinyobj::material_t> Player::material;
map<std::string, int> Player::material_map;

int ProjectileId = 0;
static bool runZooming = false;

Player::Player(int id) {
  // Scale the default model
  scale *= 1.0f;
  rotation.z = -PI/2;
  playerId = id;


  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (id == 1)
      if (!texture) texture = make_unique<Texture>(image::loadBMP("grey.bmp"));
  if (id == 2)
      if (!texture) texture = make_unique<Texture>(image::loadBMP("green.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("tank_4.obj");

    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
}
int colorOfRunningPowerUp;
float ageOfPowerUp;
bool powerUpIsRunning = false;
int sizeOfProjectilePlayer1 = 2;
int sizeOfProjectilePlayer2 = 2;
float WinnerPlayerId = 0;
float speedOfPlayer1 = 10.0f;
float speedOfPlayer2 = 10.0f;
bool lock = false;
bool powerUpRunningPlayer1 = false;
bool powerUpRunningPlayer2 = false;
string directionOfPlayer = "";
bool lockCount = false;

bool Player::update(Scene &scene, float dt) {

    if (runZooming && WinnerPlayerId != 0 && this->playerId == WinnerPlayerId){
        int whoWon;
        scene.camera->position.x = this->position.x ;
        scene.camera->position.y = this->position.y - 20.0f;
        scene.camera->position.z += 0.05f;
        if (scene.camera->position.z > -25.0f){
            runZooming = false;
            scene.newRound = true;
            whoWon = this->playerId;
            if (scene.winsOfPlayer1 == 3)
                whoWon += 2;
            else if (scene.winsOfPlayer2 == 3)
                whoWon += 2;
            auto  sc = make_unique<Screen>(whoWon);
            sc->position.x = position.x;
            sc->position.y = position.y;
            sc->scale /= 2;
            sc->position.z = -8;
            scene.objects.push_back(move(sc));
        }
    }


    if (scene.keyboard[GLFW_KEY_KP_7] && scene.keyboard[GLFW_KEY_K]){
        scene.lightDirection.x -= 0.02;
    }
    else if (scene.keyboard[GLFW_KEY_KP_4]&& scene.keyboard[GLFW_KEY_K]){
        scene.lightDirection.y -= 0.02;
    }
    else if (scene.keyboard[GLFW_KEY_KP_1]&& scene.keyboard[GLFW_KEY_K]){
        scene.lightDirection.z -= 0.02;
    }
    else if (scene.keyboard[GLFW_KEY_KP_7]){
    scene.lightDirection.x += 0.02;
    }
    else if (scene.keyboard[GLFW_KEY_KP_4]){
        scene.lightDirection.y += 0.02;
    }
    else if (scene.keyboard[GLFW_KEY_KP_1]){
        scene.lightDirection.z += 0.02;
    }

    if (scene.keyboard[GLFW_KEY_KP_3] && scene.keyboard[GLFW_KEY_K]){
        scene.camera->position.x -= 0.01f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_6]&& scene.keyboard[GLFW_KEY_K]){
        scene.camera->position.y -= 0.04f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_9]&& scene.keyboard[GLFW_KEY_K]){
        scene.camera->position.z -= 0.04f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_5]&& scene.keyboard[GLFW_KEY_K]){
        scene.camera->back.y -= 0.01f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_8]&& scene.keyboard[GLFW_KEY_K]){
        scene.camera->back.z -= 0.01f;
    }

    else if (scene.keyboard[GLFW_KEY_KP_3]){
        scene.camera->position.x += 0.01f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_6]){
        scene.camera->position.y += 0.04f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_9]){
        scene.camera->position.z += 0.04f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_5]){
        scene.camera->back.y += 0.01f;
    }
    else if (scene.keyboard[GLFW_KEY_KP_8]){
        scene.camera->back.z += 0.01f;
    }

    if (scene.keyboard[GLFW_KEY_R]){
        colorOfRunningPowerUp;
        ageOfPowerUp;
        powerUpIsRunning = false;
        sizeOfProjectilePlayer1 = 2;
        sizeOfProjectilePlayer2 = 2;
        WinnerPlayerId = 0;
        speedOfPlayer1 = 10.0f;
        speedOfPlayer2 = 10.0f;
        lock = false;
        powerUpRunningPlayer1 = false;
        powerUpRunningPlayer2 = false;
        directionOfPlayer = "";
        lockCount = false;
    }

    fireDelay += dt;
    bulletTime += dt;
    ageOfPowerUp += dt;
    bool collisionDetected = false;
    auto temp_position = this->position;

    //stop the power up after 8seconds
    if (powerUpRunningPlayer1 /*&& powerUpIsRunning */&& ageOfPowerUp > 10.0f){
        executePowerUpPlayer1(scene,colorOfRunningPowerUp,true, this->playerId);
        //powerUpIsRunning = false;
        powerUpRunningPlayer1 = false;
    }


    //stop the power up after 8 seconds
    if (powerUpRunningPlayer2 /*&& powerUpIsRunning */&& ageOfPowerUp > 10.0f){
        executePowerUpPlayer2(scene,colorOfRunningPowerUp,true, this->playerId);
        powerUpIsRunning = false;
        powerUpRunningPlayer2 = false;
    }

    //Player 2
    if (this->playerId== 2 && scene.keyboard[GLFW_KEY_W] && scene.keyboard[GLFW_KEY_A]) {
        temp_position.x += speedOfPlayer2 * dt;
        temp_position.y += speedOfPlayer2* dt;
        rotation.y = -PI / 3.0f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_W] && scene.keyboard[GLFW_KEY_D]) {
        temp_position.x -= speedOfPlayer2 * dt;
        temp_position.y += 10 * dt;
        rotation.y =  PI / 3.0f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_S] && scene.keyboard[GLFW_KEY_D]) {
        temp_position.x -= speedOfPlayer2 * dt;
        temp_position.y -= speedOfPlayer2 * dt;
        rotation.y = PI / 1.5f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_S] && scene.keyboard[GLFW_KEY_A]) {
        temp_position.x += speedOfPlayer2 * dt;
        temp_position.y -= speedOfPlayer2 * dt;
        rotation.y = -PI / 1.5f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_A] ) {
        temp_position.x += speedOfPlayer2 * dt;
        rotation.y = -PI / 2.0f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_D] ) {
        temp_position.x -= speedOfPlayer2 * dt;
        rotation.y = PI / 2.0f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_S]) {
        temp_position.y -= speedOfPlayer2 * dt;
        rotation.y = PI / 1.0f;
    } else if (this->playerId == 2 && scene.keyboard[GLFW_KEY_W] ) {
        temp_position.y += speedOfPlayer2 * dt;
        rotation.y = 0;
    } else {
        rotation.z = 0;

    }
    // Firing projectiles
    if (this->playerId == 2 && scene.keyboard[GLFW_KEY_LEFT_SHIFT] && fireDelay > fireRate) {
        if (bulletTime > 0.2f) {
            fireDelay = 0;
            auto projectile = make_unique<Projectile>(rotation.y, sizeOfProjectilePlayer2, 2, ProjectileId);
            projectile->position = position + glm::vec3(0.0f, 0.0f, -0.7f);// + fireOffset;
            scene.objects.push_back(move(projectile));
            auto shad = make_unique<Shadow>(4,ProjectileId);
            scene.objects.push_back(move(shad));
            ProjectileId++;
            bulletTime = 0;
        }
    }

    //Player 1
    if (this->playerId== 1 && scene.keyboard[GLFW_KEY_UP] && scene.keyboard[GLFW_KEY_LEFT] ) {
      temp_position.x += speedOfPlayer1 * dt;
      temp_position.y += speedOfPlayer1* dt;
      rotation.y = -PI / 3.0f;
    }
    else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_UP] && scene.keyboard[GLFW_KEY_RIGHT]) {
      temp_position.x -= speedOfPlayer1 * dt;
      temp_position.y += speedOfPlayer1 * dt;
        rotation.y =  PI / 3.0f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_DOWN] && scene.keyboard[GLFW_KEY_RIGHT]) {
      temp_position.x -= speedOfPlayer1 * dt;
      temp_position.y -= speedOfPlayer1* dt;
      rotation.y = PI / 1.5f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_DOWN] && scene.keyboard[GLFW_KEY_LEFT]) {
      temp_position.x += speedOfPlayer1 * dt;
      temp_position.y -= speedOfPlayer1 * dt;
        rotation.y = -PI / 1.5f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_LEFT] ) {
      temp_position.x += speedOfPlayer1 * dt;
      // rotation.z = -PI/4.0f;
      rotation.y = -PI / 2.0f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_RIGHT] ) {
      temp_position.x -= speedOfPlayer1 * dt;
      rotation.y = PI / 2.0f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_DOWN]) {
      temp_position.y -= speedOfPlayer1* dt;
      rotation.y = PI / 1.0f;
    } else if (this->playerId == 1 && scene.keyboard[GLFW_KEY_UP] ) {
      temp_position.y += speedOfPlayer1* dt;
      rotation.y = 0;
    }
    else {
      rotation.z = 0;
    }
    // Firing projectiles
    if (this->playerId == 1 && scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
        fireDelay = 0;
        fireOffset = -fireOffset;
       // printf("%f ", bulletTime);
        if (bulletTime > 0.2f){
            auto projectile = make_unique<Projectile>(rotation.y, sizeOfProjectilePlayer1, 1, ProjectileId);
            auto shad = make_unique<Shadow>(4,ProjectileId);
            ProjectileId++;
            projectile->position = position + glm::vec3(0, 0.0f, -0.7);
            scene.objects.push_back(move(projectile));
            scene.objects.push_back(move(shad));
            bulletTime = 0;
        }
    }

    //ak > -24.62y
    //ak > -23.5x
    //ak > 25.41y
    //ak > 24.19
    //Collisions

    if (temp_position.y < -23.80 || temp_position.x < -23.70 || temp_position.y > 24.90f || temp_position.x > 24.18)
        collisionDetected = true;
    for ( auto& obj : scene.objects ) {

        if (obj.get() == this)
            continue;

        auto projectile = dynamic_cast<Projectile *>(obj.get());
        auto powerUp = dynamic_cast<PowerUp *>(obj.get());
        auto enemy = dynamic_cast<Player *>(obj.get());
        auto house = dynamic_cast<House *>(obj.get());
        auto torus = dynamic_cast<Torus *>(obj.get());

        if (!projectile && !powerUp && !enemy && !house && !torus) continue;

        if (projectile) {
            if (projectile->idOfShooter != this->playerId && distance(position, projectile->position) < scale.y * 2) {
                WinnerPlayerId = this->playerId == 1 ? 2 : 1;
                runZooming = true;
                if (WinnerPlayerId == 1)
                    scene.winsOfPlayer1++;
                if (WinnerPlayerId == 2)
                    scene.winsOfPlayer2++;

                auto explosion = make_unique<Explosion>();
                explosion->position = position;
                explosion->scale = scale * 3.0f;
                scene.objects.push_back(move(explosion));

                return false; }}

        if (powerUp) {
            if (distance(position, powerUp->position) < powerUp->scale.y) {
                colorOfRunningPowerUp = powerUp->colorOfPowerUp;
               // powerUpIsRunning = true;
                ageOfPowerUp = 0;
                if (this->playerId == 1){
                    executePowerUpPlayer1(scene, powerUp->colorOfPowerUp, false, this->playerId);
                    powerUpRunningPlayer1 = true;
                }
                else{
                    executePowerUpPlayer2(scene, powerUp->colorOfPowerUp, false, this->playerId);
                    powerUpRunningPlayer2 = true;
                }
                powerUp->destroy();


            }

        }

        if (enemy) {
            if (distance(temp_position, enemy->position) < enemy->scale.y * 3.1) {
                collisionDetected = true; }}

        if (house) {
            if (distance(temp_position, house->position) - 1.8f < house->scale.y) {
                collisionDetected = true; }}

        if (torus){
            if (torus->playerId == this->playerId){
//                torus->position.x = this->position.x;
//                torus->position.y = this->position.y;//- 1.0f;
//                torus->position.z = this->position.z;
//
            }
        }
    }


    //If we didnt find collision with object
    if (!collisionDetected) {
        position = temp_position;
    }

    generateModelMatrix();
    return true;
}


void Player::render(Scene &scene) {
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

 /*shader->use();

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

void Player::executePowerUpPlayer2(Scene &scene, int typeOfPowerUp, bool stopPowerUp, int playerId) {
    if (typeOfPowerUp == 1 && !stopPowerUp){
        sizeOfProjectilePlayer2 = 9; }
    else if (typeOfPowerUp == 1 && stopPowerUp)
        sizeOfProjectilePlayer2 = 2;
    else if (typeOfPowerUp == 2 && !stopPowerUp)
        speedOfPlayer2 = 16;
    else if (typeOfPowerUp == 2 && stopPowerUp){
        speedOfPlayer2 = 10;
    }
    else if (typeOfPowerUp == 3 && !stopPowerUp){
        auto torus1 = make_unique<Torus>(2, playerId);
        torus1->playerId = 2;
        scene.objects.push_back(move(torus1));
        auto shadow = make_unique<Shadow>(5, 2);
        scene.objects.push_back(move(shadow));
    }
    else if (typeOfPowerUp == 3 && stopPowerUp){
        //described in torus.cpp - after 5sec
    }

}

void Player::executePowerUpPlayer1(Scene &scene, int typeOfPowerUp, bool stopPowerUp, int playerId) {
    if (typeOfPowerUp == 1 && !stopPowerUp){
        sizeOfProjectilePlayer1 = 9; }
    else if (typeOfPowerUp == 1 && stopPowerUp)
        sizeOfProjectilePlayer1 = 2;
    else if (typeOfPowerUp == 2 && !stopPowerUp)
        speedOfPlayer1 = 16;
            else if (typeOfPowerUp == 2 && stopPowerUp){
        speedOfPlayer1 = 10;
    }
    else if (typeOfPowerUp == 3 && !stopPowerUp){
        auto torus1 = make_unique<Torus>(1, playerId);
        torus1->playerId = 1;
        scene.objects.push_back(move(torus1));
        auto shadow = make_unique<Shadow>(5, 1);
        scene.objects.push_back(move(shadow));
    }
    else if (typeOfPowerUp == 3 && stopPowerUp){
        //described in torus.cpp - after 5sec
    }
}

void Player:: onClick(Scene &scene) {
  cout << "Player has been clicked!" << endl;
}