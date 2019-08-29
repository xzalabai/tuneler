#include "torus.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "asteroid.h"
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

// shared resources
//unique_ptr<Mesh> Torus::meplash;
//unique_ptr<Texture> Torus::texture;
//unique_ptr<Shader> Torus::shader;
vector<tinyobj::material_t> Torus::material;
map<std::string, int> Torus::material_map;

Torus::Torus(int pId, int pCol) {
    printf("%d ", pId);
    pId = playerId;
    // Scale the default model
    scale *= 3.5f;

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (pCol == 1)
       if (!texture) texture = make_unique<Texture>(image::loadBMP("grey.bmp"));
    if (pCol == 2)
        if (!texture) texture = make_unique<Texture>(image::loadBMP("green.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("torus_final_final.obj");
    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
}
vec3 tmpPos;
bool Torus::update(Scene &scene, float dt) {

    age += dt;

    if (age < 3.5f)
        rotation.y += 0.01;
    else if (age > 3.5f && age < 6.0f)
        rotation.y += 0.029f;
    else if (age > 6.0f)
        rotation.y += 0.04f;
//printf("%f %f %f\n", tmpPos.x, tmpPos.y, tmpPos.z);
    for ( auto& obj : scene.objects ) {
        if (obj.get() == this)
            continue;
        auto projectile = dynamic_cast<Projectile*>(obj.get());
        auto player = dynamic_cast<Player*>(obj.get());
        if (!projectile && !player) continue;

        if (player){
            if (player->playerId == this->playerId){
                modelMatrix = player->modelMatrix * glm::translate(mat4(1.0f), position)
                                     * glm::orientate4(rotation)
                                     * glm::scale(mat4(1.0f), scale);
            }
            tmpPos = player->position;

        }
        if (projectile){
          //  printf("dis %f\n", distance(position, projectile->position));
            if (projectile->idOfShooter != this->playerId && distance(tmpPos, projectile->position) < scale.y){
                projectile->destroy();
            }
        }

    }

    //torus dissapear after 8sec
    if (age > 8.0f) return false;
    //generateModelMatrix();
    return true;
}

void Torus::render(Scene &scene) {
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

void Torus::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}