#ifndef Skeleton_FACTORY_H_
#define Skeleton_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Skeleton.h"

/**
 *@brief skeleton Factory to produce Skeleton class.
 **/
class SkeletonFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for SkeletonFactory class.
   **/
  virtual ~SkeletonFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
