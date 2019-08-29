#pragma once
#include <ppgso/ppgso.h>

#include "object.h"

/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Player final : public Object {
private:
  // Static resources (Shared between instances)
  std::unique_ptr<ppgso::Mesh> mesh;
  std::unique_ptr<ppgso::Shader> shader;
  std::unique_ptr<ppgso::Texture> texture;
    static std::vector<tinyobj::material_t> material;
    static std::map<std::string, int> material_map;
  int wins =0 ;

  // Delay fire and fire rate
  float fireDelay{0.0f};
  float fireRate{0.1f};
  glm::vec3 fireOffset{0.7f,0.0f,0.0f};

public:
  /*!
   * Create a new player
   */
  Player(int id);

  int playerId;
  float bulletTime = 0;
  //bool runZooming;

  /*!
   * Update player position considering keyboard inputs
   * @param scene Scene to update
   * @param dt Time delta
   * @return true to delete the object
   */
  bool update(Scene &scene, float dt) override;

  float direction;

  void ahoj(Scene &scene);

  /*!
   * Render player
   * @param scene Scene to render in
   */
  void render(Scene &scene) override;

  void executePowerUpPlayer1(Scene &scene, int typeOfPowerUp, bool stopPowerUp, int playerId);
  void executePowerUpPlayer2(Scene &scene, int typeOfPowerUp, bool stopPowerUp, int playerId);
  /*!
   * Player click event
   * @param scene
   */
  void onClick(Scene &scene) override ;
};

