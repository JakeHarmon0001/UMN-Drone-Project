#ifndef HUNGER_DECORATORH
#define HUNGER_DECORATORH

#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief this class inhertis from the IStrategy class and is represents
 * a hunger decorator where the entity will die according to it.
 */
class HungerDecorator : public IStrategy {
 public:
  /**
   * @brief Construct a new HungerDecorator
   * @param strategy the strategy to decorate onto
   */
  HungerDecorator(IStrategy* strategy);

  /**
   * @brief HungerDecorator destructor
   */
  ~HungerDecorator();

  /**
   * @brief Returns true if entity is dead
   * @return Bool representing whether the entity is dead
   */
  bool isDead();

  /**
   * @brief Moves the entity
   * @param entity Entity to be moved
   * @param dt Delta time
   */
  void Move(IEntity* entity, double dt);

  /**
   * @brief returns true if movement is complete
   * @return Bool whether movement is complete
   */
  bool IsCompleted();

 protected:
  IStrategy* strategy;
  bool dead;
};

#endif
