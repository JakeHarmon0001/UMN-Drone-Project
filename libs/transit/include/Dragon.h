#ifndef DRAGON_H_
#define DRAGON_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a Dragon in a physical system.
// Dragons move using beelines to randomly generated destinations
/**
 * @class Dragon
 * @brief Represents a Dragon in a physical system. Dragon move using 
 * beelines to randomly generated destinations
 */
class Dragon : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the Dragon's information
   */
  Dragon(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Dragon();

  /**
   * @brief Updates the Dragon's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

   /**
   * @brief Gets the speed of the dragon
   * @return The speed of the dragon
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the dragon
   * @return The position of the dragon
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the dragon
   * @return The direction of the dragon
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the dragon
   * @return The destination of the dragon
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the dragon
   * @return The color of the dragon
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the dragon
   * @return The details information of the dragon
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Sets the position of the Dragon
   * @param pos_ The new position of the Dragon
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Dragon
   * @param dir_ The new direction of the Dragon
   */
  void SetDirection(Vector3 dir_) { 
    direction = dir_; 
  }

  /**
   * @brief Sets the destination of the Dragon
   * @param des_ The new destination of the Dragon
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Dragon
   * @param col_ The new color of the Dragon
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the Dragon
   * @param angle The angle by which the Dragon should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Dragons cannot be copied.
   */
  Dragon(const Dragon& Dragon) = delete;
  Dragon& operator=(const Dragon& Dragon) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  Vector3 finalDestination;
  float speed;
  bool available;
  std::string strategyName;
  IStrategy* toFinalDestination = nullptr;
  std::string color;
};

#endif
