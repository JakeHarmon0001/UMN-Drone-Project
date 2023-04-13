#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 position, Vector3 destination)
  : position(position), destination(destination) {}

void BeelineStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted())
    return;

  Vector3 dir = (destination - position).Unit();

  position = position + dir * entity->GetSpeed() * dt;

  // dir.x = dir.x * std::cos(70) - dir.z * std::sin(70);
  // dir.z = dir.x * std::sin(70) + dir.z * std::cos(70);
  entity->SetPosition(position);
  entity->SetDirection(dir);
}

bool BeelineStrategy::IsCompleted() {
  return position.Distance(destination) < 1.0;
}
