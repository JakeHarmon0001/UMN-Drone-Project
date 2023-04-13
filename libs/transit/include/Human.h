#ifndef HUMAN_H_
#define HUMAN_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a human in a physical system.
// Human move using astar to randomly generated destinations
/**
 * @class Human
 * @brief Represents a Human in a physical system. Human move using 
 * beelines to randomly generated destinations
 */
class Human : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the Human's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Human();

  /**
   * @brief Updates the Human's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

   /**
   * @brief Gets the speed of the human
   * @return The speed of the human
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the human
   * @return The position of the human
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the human
   * @return The direction of the human
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the human
   * @return The destination of the human
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the human
   * @return The color of the human
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the human
   * @return The details information of the human
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Sets the position of the Human
   * @param pos_ The new position of the Human
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Human
   * @param dir_ The new direction of the Human
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Human
   * @param des_ The new destination of the Human
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Human
   * @param col_ The new color of the Human
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the Human
   * @param angle The angle by which the Human should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Humans cannot be copied.
   */
  Human(const Human& Human) = delete;
  Human& operator=(const Human& Human) = delete;

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