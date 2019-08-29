// Example gl_scene
// - Introduces the concept of a dynamic scene of objects
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "gulicka.h"
#include "generator.h"
#include "torus.h"
#include "HandGun.h"
#include "asteroid.h"
#include "desk.h"
#include "player.h"
#include "space.h"
#include "shadow.h"
#include "powerUp.h"
#include "Screen.h"
#include "house.h"

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 1024;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public Window {
private:
  Scene scene;
  bool animate = true;

  /*!
   * Reset and initialize the game scene
   * Creating unique smart pointers to objects that are stored in the scene object list
   */
  void initScene() {

    scene.objects.clear();

      // Create a camera
      auto camera = make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
      camera->position.z = -50.0f;
      scene.camera = move(camera);

      scene.objects.push_back(make_unique<Space>());
    // Add space background
    //scene.objects.push_back(make_unique<Space>());
    vec3 pos;
    for (int i = 0; i < scene.winsOfPlayer1; i++) {
        if (i == 0) pos = {-9, -29, 0};
        if (i == 1) pos = {-13, -29, 0};
        if (i == 2) pos = {-17, -29, 0};
        auto handgun = make_unique<HandGun>(1, pos);
        //handgun->rotation.y = PI / 3.0f;
        scene.objects.push_back(move(handgun));
    }

    for (int i = 0; i < scene.winsOfPlayer2; i++){
        if (i == 0) pos = {11,-29,0};
        if (i == 1) pos = {15,-29,0};
        if (i == 2) pos = {19,-29,0};
        auto handgun = make_unique<HandGun>(2,pos);
        scene.objects.push_back(move(handgun));
    }


    auto generator = make_unique<Generator>();
    generator->position.y = 10.0f;
    scene.objects.push_back(move(generator));

      auto ast = make_unique<Asteroid>();
      ast->position = {200,0,0};
      scene.objects.push_back(move(ast));

    // Add player to the scene
    auto player = make_unique<Player>(1);
    player->position.x = -20.26f;             //-13, -19
    player->position.y = -22.5f;
    player->position.z = 0.50f;
    scene.objects.push_back(move(player));

    auto player2 = make_unique<Player>(2);
      player2->position.x = 20.40f;             //12, 11
      player2->position.y = 22.30f;
      player2->position.z = 0.50f;
      scene.objects.push_back(move(player2));


    auto shadow1 = make_unique<Shadow>(1,1);
    scene.objects.push_back(move(shadow1));

    auto shadow2 = make_unique<Shadow>(1,2);
    scene.objects.push_back(move(shadow2));

      //house = make_unique<House>(25);

      //TODO: undo comments
    for (int i = 0; i < 35; i ++){
      float texture = linearRand(0.0f, 4.0f);
      float x = linearRand(-20.5f, 22.5f);
      float y = linearRand(-22.5f, 22.5f);
        if ((x > 17 && y > 18) || (x < -17 && y < -18)){
        }
      else {
        auto house = make_unique<House>(25, texture, i);
        house->position = {x, y, 0.0f};
        scene.objects.push_back(move(house));
        auto sh = make_unique<Shadow>(3,i);
        scene.objects.push_back(move(sh));
      }

    }

   auto desk = make_unique<Desk>();
    desk->position = {0.0f, 3.2f, 0.0f};
   scene.objects.push_back(move(desk));
   // scene.objects.push_back(move(gulicka));



/*
    auto shad2 = make_unique<Shadow>(2);
    shad2->position = {0.0f, 0, 0.0f};
    shad2->startingPosition = shad2->position;
    scene.objects.push_back(move(shad2));
*/
   //TODO: create obj with player 1 win (white)
    if (scene.winsOfPlayer2 == 3 || scene.winsOfPlayer1 == 3){
      scene.newGame = true;
      }


  }

public:
  /*!
   * Construct custom game window
   */
  SceneWindow() : Window{"tuneler", SIZE, SIZE} {
    //hideCursor();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    initScene();
  }

  /*!
   * Handles pressed key when the window is focused
   * @param key Key code of the key being pressed/released
   * @param scanCode Scan code of the key being pressed/released
   * @param action Action indicating the key state change
   * @param mods Additional modifiers to consider
   */
  void onKey(int key, int scanCode, int action, int mods) override {
    scene.keyboard[key] = action;
    // Reset
    //printf("DEBUGGGG");
    //just a newRound, in player.cpp, when enemy got killed, and zooming stops, newRound will be true
    if (scene.newRound){
      scene.levelNumber += 1;
      scene.newRound = false;
      initScene();
    }

    if (key == GLFW_KEY_U&& action == GLFW_PRESS){
      scene.camera->position.x =-0.08;
      scene.camera->position.y  = -6.199;
      scene.camera->position.z  = -61.199;

      scene.camera->back.y =-0.390002;
      scene.camera->back.z = -5.100025;
    }
    if (key == GLFW_KEY_I&& action == GLFW_PRESS){
      scene.camera->position = { 0.000000, -39.000000, -50.000000}; //TODO: predtym 0.0.0
      scene.camera->back = {0,-2.950000 , -3.900000};
    }
    // Pause
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      animate = !animate;
    }

    //if there is end, player press the R and whole scene gets reset
    if (scene.keyboard[GLFW_KEY_R] && scene.newGame){
      scene.winsOfPlayer1 = 0;
      scene.winsOfPlayer2 = 0;
      scene.newGame = false;
      initScene();
    }

  }

  /*!
   * Handle cursor position changes
   * @param cursorX Mouse horizontal position in window coordinates
   * @param cursorY Mouse vertical position in window coordinates
   */
  void onCursorPos(double cursorX, double cursorY) override {
    scene.cursor.x = cursorX;
    scene.cursor.y = cursorY;
  }

  /*!
   * Handle cursor buttons
   * @param button Mouse button being manipulated
   * @param action Mouse bu
   * @param mods
   */
  void onMouseButton(int button, int action, int mods) override {

    if(button == GLFW_MOUSE_BUTTON_LEFT) {
      scene.cursor.left = action == GLFW_PRESS;

      if (scene.cursor.left) {
        // Convert pixel coordinates to Screen coordinates
        float u = (scene.cursor.x / width - 0.5f) * 2.0f;
        float v = - (scene.cursor.y / height - 0.5f) * 2.0f;

        // Get mouse pick vector in world coordinates
        auto direction = scene.camera->cast(u, v);
        auto position = scene.camera->position;

        // Get all objects in scene intersected by ray
        auto picked = scene.intersect(position, direction);

        // Go through all objects that have been picked
        for (auto &obj: picked) {
          // Pass on the click event
          obj->onClick(scene);
        }
      }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT) {
      scene.cursor.right = action == GLFW_PRESS;
    }
  }

  /*!
   * Window update implementation that will be called automatically from pollEvents
   */
  void onIdle() override {
    // Track time
    static auto time = (float) glfwGetTime();

    // Compute time delta
    float dt = animate ? (float) glfwGetTime() - time : 0;

    time = (float) glfwGetTime();

    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();
  }
};

int main() {
  // Initialize our window
  SceneWindow window;
  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}
