#ifndef HUNGER_DECORATORH
#define HUNGER_DECORATORH

#include "IStrategy.h"
#include "math/vector3.h"

class HungerDecorator: public IStrategy {

 public:
  HungerDecorator(IStrategy* strategy);

  ~HungerDecorator();

  bool isDead();

  void Move(IEntity* entity, double dt);

  bool IsCompleted();

 protected:
  IStrategy* strategy;
  bool dead;
};

#endif