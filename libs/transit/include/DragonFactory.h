#ifndef DRAGON_FACTORY_H_
#define DRAGON_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Dragon.h"

/**
 *@brief Dragon Factory to produce Dragon class.
 **/
class DragonFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for DragonFactory class.
   **/
  virtual ~DragonFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
