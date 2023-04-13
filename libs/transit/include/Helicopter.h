#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a helicopter in a physical system.
// Helicopters move using beelines to randomly generated destinations
/**
 * @class Helicopter
 * @brief Represents a helicopter in a physical system. Helicopter move using 
 * beelines to randomly generated destinations
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the helicopter's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Helicopter();

  /**
   * @brief Updates the helicopter's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

   /**
   * @brief Gets the speed of the helicopter
   * @return The speed of the helicopter
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the helicopter
   * @return The position of the helicopter
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the helicopter
   * @return The direction of the helicopter
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the helicopter
   * @return The destination of the helicopter
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the helicopter
   * @return The color of the helicopter
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the helicopter
   * @return The details information of the helicopter
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Sets the position of the helicopter
   * @param pos_ The new position of the helicopter
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the helicopter
   * @param dir_ The new direction of the helicopter
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the helicopter
   * @param des_ The new destination of the helicopter
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the helicopter
   * @param col_ The new color of the helicopter
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the helicopter
   * @param angle The angle by which the helicopter should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that helicopters cannot be copied.
   */
  Helicopter(const Helicopter& helicopter) = delete;
  Helicopter& operator=(const Helicopter& helicopter) = delete;

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
