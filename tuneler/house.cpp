#include "house.h"
#include "player.h"
#include "scene.h"
#include "object.h"
#include "powerUp.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;
vector<tinyobj::material_t> House::material;
map<std::string, int> House::material_map;

House::House(int a, float tex,int uniqueId) {

    id = uniqueId;
    // Scale the default model
    scale *= 1.5f;
    scale *= linearRand(1.2f, 1.7f);;
    //scale *= 0.2;
    hits = 20;

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

    if (!mesh) mesh = make_unique<Mesh>("testAhoj.obj");

    ifstream myStream ("testAhoj.mtl", std::ifstream::binary);
    tinyobj::LoadMtl(material_map, material, myStream);
  //  materials = make_unique<tinyobj::MaterialFileReader>("testAhoj.mtl");

    position.z = -4.0f;
}

bool stillMove = true;
float timeS = 0;

bool House::update(Scene &scene, float dt) {

    for ( auto& obj : scene.objects ) {
        // Ignore self in scene
        if (obj.get() == this)
            continue;
        // We only need to collide with asteroids, ignore other objects
        auto projectile = dynamic_cast<Projectile*>(obj.get());

        if (!projectile) continue;
        if (distance(position, projectile->position) < scale.y + 0.5f){ //TODO: really 0.4 ??????
            projectile->destroy();
            hits--;
            this->scale -= 0.275f;
            if (scale.y < 0.8)
                return false;
        }
        }

    generateModelMatrix();
    return true;
}

void House::render(Scene &scene) {
    vec3 ambient = vec3(material.data()->ambient[0], material.data()->ambient[1], material.data()->ambient[2]);
    vec4 diffuse = vec4(material.data()->diffuse[0], material.data()->diffuse[1], material.data()->diffuse[2], 1.0f);
    vec3 specular = vec3(material.data()->specular[0], material.data()->specular[1], material.data()->specular[2]);
    float shininess = material.data()->shininess * 128;

    glEnable(GL_DEPTH_TEST);
    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->use();
    shader->setUniform("LightDirection", scene.lightDirection);
    shader->setUniform("LightColor", scene.lightColor);


    shader->setUniform("LightDirection2", scene.lightDirection2);
    shader->setUniform("LightColor2", scene.lightColor2);

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



    // shader->setUniform("shadowMap", 1);
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

void House::onClick(Scene &scene) {
    cout << "Player has been clicked!" << endl;
}