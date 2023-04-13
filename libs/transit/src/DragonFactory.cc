#include "DragonFactory.h"

IEntity* DragonFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("dragon") == 0) {
    std::cout << "Dragon Created" << std::endl;
    return new Dragon(entity);
  }
  return nullptr;
}
