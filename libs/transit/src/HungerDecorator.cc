#include "HungerDecorator.h"

#include "math/vector3.h"

HungerDecorator::HungerDecorator(IStrategy* strategy) {
  this->strategy = strategy;
  dead = false;
}
HungerDecorator::~HungerDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

bool HungerDecorator::isDead() { return dead; }

bool HungerDecorator::IsCompleted() {
  return isDead() || strategy->IsCompleted();
}

void HungerDecorator::Move(IEntity* entity, double dt) {
  if (!isDead() && entity->getType() == "dragon") {
    if (entity->getHungerLevel() > 50) {
      Vector3 temp = entity->GetPosition();
      if (temp[1] > 230) {
        temp[1] -= 0.6;
        entity->SetPosition(temp);
      } else {
        if (!entity->isDead()) {
          entity->setDead(true);
          dead = true;
          entity->GetPublisher()->setMessage(
              std::string(entity->GetDetails()["name"]) + " has died\n");
          entity->GetPublisher()->notify();
        }
      }
    } else {
      if (!strategy->IsCompleted()) {  // keep moving
        strategy->Move(entity, dt);
      }
    }
  }
}
