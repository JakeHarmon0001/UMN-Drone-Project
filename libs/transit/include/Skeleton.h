#ifndef Skeleton_H_
#define Skeleton_H_

#include "IEntity.h"
#include "IStrategy.h"

class Skeleton : public IEntity {
 public:
  /**
   * @brief Skeleton are created with a name
   * @param obj JSON object containing the skeletons's information
   */
  Skeleton(JsonObject& obj);

  /**
   * @brief Destroy the Skeleton object
   */
  ~Skeleton();

  std::string getType() const {return "skeleton";}

  /**
   * @brief Gets the skeleton's position
   * @return The skeleton's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the skeleton's direction
   * @return The skeleton's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the skeleton's destination
   * @return The skeleton's destination
   */
  Vector3 GetDestination() const { return {0,0,0}; }

  /**
   * @brief Gets the skeleton's availability
   * @return The skeleton's availability
   */
  bool GetAvailability() const { return false; }

  /**
   * @brief Gets the skeleton's details
   * @return The skeleton's details
   */
  JsonObject GetDetails() const override { return details; }

  /**
   * @brief Gets the skeleton's speed
   * @return The skeleton's speed
   */
  float GetSpeed() const { return 0; }

  /**
   * @brief Sets the skeleton's position
   * @param pos_ The new position of the skeleton
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  

  private:
  JsonObject details;
  Vector3 direction;
  Vector3 position;
};

#endif