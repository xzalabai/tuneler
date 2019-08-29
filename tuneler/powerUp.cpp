#include "powerUp.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "asteroid.h"
#include "house.h"
#include "projectile.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;
vector<tinyobj::material_t> PowerUp::material;
map<std::string, int> PowerUp::material_map;
// shared resources

PowerUp::PowerUp(int color, int id) {

    scale *= 2.0f;
    uniqueId = id;

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (color == 1){
        if (!texture) texture = make_unique<Texture>(image::loadBMP("red.bmp"));
        colorOfPowerUp = color;
    }
    else if (color == 2){
        if (!texture) texture = make_unique<Texture>(image::loadBMP("blue.bmp"));
        colorOfPowerUp = color;
    }
    else if (color == 3){
        if (!texture) texture = make_unique<Texture>(image::loadBMP("green.bmp"));
        colorOfPowerUp = color;
    }
    if (!mesh) mesh = make_unique<Mesh>("pokus4.obj");
    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);

}
void PowerUp::gravity(Scene &scene, float dt, float floor){
    if (!iamDown && position.z <= floor){
        gravityDown += dt*16;
        position.z += 0.02*gravityDown;
        if (position.z >= 0){
            iamDown = true;
            gravityUp = gravityDown/1.3;
        }
    }
    else if (iamDown){
        position.z -= gravityUp*0.015;
        gravityUp -=dt*21;
        if (gravityUp < floor + 0.03){
            iamDown = false;
            gravityDown = 0;
        }
    }
}

bool PowerUp::update(Scene &scene, float dt) {

    //printf("%.2f %.2f %.2f\n", position.x, position.y, position.z);
    age += dt;
    gravity(scene, dt, 0);
    for ( auto& obj : scene.objects ) {
        // Ignore self in scene
        if (obj.get() == this)
            continue;
        // We only need to collide with asteroids, ignore other objects
        auto projectile = dynamic_cast<Projectile*>(obj.get());
        if (!projectile) continue;

        if (projectile){
            if (distance(position, projectile->position) < scale.y) {
                projectile->destroy();
                destroy();
            }
        }

    }

    //if the powerup is on scene without contact more than 10 seconds, it will destroy itself
    if (age > 10.0f) return false;

    generateModelMatrix();
    return true;
}

void PowerUp::render(Scene &scene) {
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


void PowerUp::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}

void PowerUp::destroy() {
    // This will destroy the projectile on Update
    age = 100.0f;
}