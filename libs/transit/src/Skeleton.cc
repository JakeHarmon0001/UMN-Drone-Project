#define _USE_MATH_DEFINES
#include "Skeleton.h"

#include <cmath>
#include <limits>

Skeleton::Skeleton(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
}

Skeleton::~Skeleton() {
  // Delete dynamically allocated variables
  delete graph;
}
