#ifndef Dragon_H_
#define Dragon_H_

#include "IController.h"
#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Dragon
 * @brief Represents a dragon in a physical system.
 *
 * Subclass of IEntity that represents a dragon. Dragons
 * pursue drones and have hunger implemented.
 */
class Dragon : public IEntity {
 public:
  /**
   * @brief Dragon are created with a JsonObject
   * @param obj JSON object containing the drone's information
   */
  Dragon(JsonObject& obj);

  /**
   * @brief Destroy the Dragon object
   */
  ~Dragon();
  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  void CreateNewDestination();

  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Assigns the controller component of dragon
   * @param controller the controller to be assigned
   */
  void addController(IController* controller);

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief returns type of dragon
   * @return String "dragon"
   */
  std::string getType() const { return "dragon"; }

  /**
   * @brief Set speed of dragon
   * @param speed Speed of dragon
   */
  virtual void setSpeed(float speed) { this->speed = speed; }

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  IStrategy* toDestination = nullptr;
  bool available;
  IEntity* nearestEntity = nullptr;
  IController* controller;
  double hungerLevel;
};

#endif
