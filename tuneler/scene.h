#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"

/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
  public:
    int winsOfPlayer1 = 0;
    int winsOfPlayer2 = 0;
    int levelNumber = 1;
    bool newGame = false;
    bool newRound = false;
    /*!
     * Update all objects in the scene
     * @param time
     */
    glm::vec3 lightDirection{0.92f, -0.36f, -0.37f};
    glm::vec3 lightDirection2{-0.92f, 0.36f, -0.37f};
    glm::vec3 lightColor = glm::vec3(1,1,1);
    glm::vec3 lightColor2 = glm::vec3(0,1,0);
    glm::vec3 ambientLightColor = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 RotateColor(glm::vec3& inColor , float H);
    float t = 0;

    void update(float time);

    /*!
     * Render all objects in the scene
     */
    void render();

    /*!
     * Pick objects using a ray
     * @param position - Position in the scene to pick object from
     * @param direction - Direction to pick objects from
     * @return Objects - Vector of pointers to intersected objects
     */
    std::vector<Object*> intersect(const glm::vec3 &position, const glm::vec3 &direction);

    // Camera object
    std::unique_ptr<Camera> camera;

    // All objects to be rendered in scene
    std::list< std::unique_ptr<Object> > objects;

    // Keyboard state
    std::map< int, int > keyboard;

    // Lights, in this case using only simple directional diffuse lighting
   // glm::vec3 lightDirection{-1.0f, -1.0f, -1.0f};

    // Store cursor state
    struct {
      double x, y;
      bool left, right;
    } cursor;
};

#endif // _PPGSO_SCENE_H
