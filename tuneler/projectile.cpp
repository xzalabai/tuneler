
#include <glm/gtc/random.hpp>
#include "scene.h"
#include "player.h"
#include "house.h"
#include "projectile.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;

// shared resources
unique_ptr<Mesh> Projectile::mesh;
unique_ptr<Shader> Projectile::shader;
unique_ptr<Texture> Projectile::texture;
vector<tinyobj::material_t> Projectile::material;
map<std::string, int> Projectile::material_map;

Projectile::Projectile(float directionOfTank, int sizeOfProjectile, int shooterId, int id) {

  uniqueId = id;
  idOfShooter = shooterId;
  // Set default speed
  speed = {0.0f, 3.0f, 0.0f};
  rotMomentum = {0.0f, 0.0f, linearRand(-PI/4.0f, PI/4.0f)};

  // Initialize static resources if needed
  if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("red.bmp"));
  if (!mesh) mesh = make_unique<Mesh>("strela.obj");
    scale.x = sizeOfProjectile;
    scale.z = sizeOfProjectile;
    scale.y = sizeOfProjectile;
  directionOfProjectile = directionOfTank;
    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
}

bool Projectile::update(Scene &scene, float dt) {


//    for ( auto& obj : scene.objects ) {
//
//        if (obj.get() == this)
//            continue;
//
//        auto house = dynamic_cast<House *>(obj.get());
//
//        if (house) continue;
//
//        if (distance(position, house->position) < house->scale.y){
//        }
//    }

    // Increase age
    age += dt;

    float dir = directionOfProjectile;

        if (dir == -PI/3.0f){
            position.x += 28 * dt;
            position.y += 28* dt;
            rotation.y  = -PI/3.0f;
        }
        else if (dir == PI/3.0f){
            position.x -= 28 * dt;
            position.y += 28 * dt;
            rotation.y  = PI/3.0f;
        }
        else if (dir == PI/1.5f){
            position.x -= 28 * dt;
            position.y -= 28 * dt;
            rotation.y  = PI/1.5f;
        }
        else if (dir == -PI/1.5f){
            position.x += 28 * dt;
            position.y -= 28 * dt;
            rotation.y  = -PI/1.5f;
        }
        else if(dir == -PI/2.0f) {
            position.x += 28 * dt;
            // rotation.z = -PI/4.0f;
            rotation.y  = -PI/2.0f;
        } else if(dir == PI/2.0f) {
            position.x -= 28 * dt;
            // rotation.z = PI/4.0f;
            rotation.y  = PI/2.0f;
        }
        else if(dir == PI/1.0f) {
            position.y -= 28 * dt;
            rotation.y  = PI/1.0f;
        }
        else {
            position.y += 28 * dt;
            rotation.y  = 0;
        }

        // Accelerate
        speed += vec3{0.0f, 40.0f, 0.0f} * dt;
        rotation += rotMomentum * dt;
        // Move the projectile
        //position += speed * dt;
        // Die after 5s
        if (age > 1.9f) return false;

        generateModelMatrix();
        return true;
    }

void Projectile::render(Scene &scene) {
    glEnable(GL_DEPTH_TEST);
    vec3 ambient = vec3(material.data()->ambient[0], material.data()->ambient[1], material.data()->ambient[2]);
    vec4 diffuse = vec4(material.data()->diffuse[0], material.data()->diffuse[1], material.data()->diffuse[2], 1.0f);
    vec3 specular = vec3(material.data()->specular[0], material.data()->specular[1], material.data()->specular[2]);
    float shininess = material.data()->shininess * 128;
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

void Projectile::destroy() {
  // This will destroy the projectile on Update
  age = 100.0f;
}
