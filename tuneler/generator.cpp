#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "powerUp.h"
#include "house.h"
#include "shadow.h"
#include "asteroid.h"

using namespace std;
using namespace glm;
using namespace ppgso;
int i = 0;

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;

  // Add object to scene when time reaches certain level
  if (time > 7.0f) {
    int randomColor = linearRand(1.0f, 4.0f);
    //printf("_%d_", randomColor);
    auto obj = make_unique<PowerUp>(randomColor,i);
    obj->position = position;
    obj->position.x = linearRand(-22.5f, 22.5f);//linearRand(-20.0f, 20.0f);
    obj->position.y = linearRand(-24.5f, 22.5f);//linearRand(-20.0f, 20.0f);
    obj->position.z = -30.0f;
    scene.objects.push_back(move(obj));
    auto shadow = make_unique<Shadow>(2,i);
    scene.objects.push_back(move(shadow));
    i = i + 1;
    time = 0;
  }

  return true;
}

int Generator::createRandomPosition(bool powerUpType, float dt){
  if (powerUpType){
    int x = rand() % 100;
    printf("%d\n", x);
    if ((x % 2) == 0) return 1;
    return 2;
  }
  else {
    float number = rand() % 20;
    float minus = rand() % 2;
    if (minus == 0)
      return number;
    else
      return ((-1) * number);
  }
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}
