#include "Skeleton.h"
#include "SkeletonFactory.h"

IEntity* SkeletonFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("skeleton") == 0) {
    std::cout << "Skeleton Created" << std::endl;
    return new Skeleton(entity);
  }
  return nullptr;
}
