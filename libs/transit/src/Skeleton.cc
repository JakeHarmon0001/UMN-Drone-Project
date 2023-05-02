#define _USE_MATH_DEFINES
#include "Skeleton.h"

#include <cmath>
#include <limits>

// #include "BeelineStrategy.h"

Skeleton::Skeleton(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
//   JsonArray dir(obj["direction"]);
//   direction = {dir[0], dir[1], dir[2]};
}

Skeleton::~Skeleton() {
  // Delete dynamically allocated variables
  delete graph;
}

