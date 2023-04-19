#define _USE_MATH_DEFINES
#include <random>
#include <cmath>
#include <limits>
#include "Dragon.h"
#include "BeelineStrategy.h"

Dragon::Dragon(JsonObject &obj) : details(obj)
{
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
  strategyName = "Beeline";
  int num1 = rand() % (1500 - (-1400) + 1) + (-1400);
  int range2 = 240 - 500 + 1;
  int num2 = rand() % (500 - 240 + 1) + 240;
  int range3 = -800 - 800 + 1;
  int num3 = rand() % (800 - (-800) + 1) + (-800);
  finalDestination = {num1, num2, num3};
  toFinalDestination = new BeelineStrategy(destination, finalDestination); // could potentially causes a problem
}

Dragon::~Dragon()
{
  delete graph;
}

void Dragon::Update(double dt, std::vector<IEntity *> scheduler)
{
  if (toFinalDestination->IsCompleted())
  { // just finished chasing entity
    if (nearestEntity)
    {
      nearestEntity->SetPosition({-999, -999, -999});
    }
    std::cout << "into the iscompleted if statement" << std::endl;
    available = true; // now available
    int num1 = rand() % (1500 - (-1400) + 1) + (-1400);
    int range2 = 240 - 500 + 1;
    int num2 = rand() % (500 - 240 + 1) + 240;
    int range3 = -800 - 800 + 1;
    int num3 = rand() % (800 - (-800) + 1) + (-800);
    destination = finalDestination;
    finalDestination = {num1, 300, num3}; // move randomly
    // GetNearestEntity(scheduler); //is there already an entity in range
    toFinalDestination = new BeelineStrategy(destination, finalDestination); // could potentially cause a problem?
  }
  else
  {
    std::cout << "dragon update - final destination not completed" << std::endl;
    // check nearest entity
    if (available)
    {
      std::cout << "into the available if statement" << std::endl;
      GetNearestEntity(scheduler);
      // if()
      // toFinalDestination = new BeelineStrategy(position, finalDestination); //if entity found
    }
    std::cout << "should be moving rn" << std::endl;
    toFinalDestination->Move(this, dt);
    // Rotate(69.997);
  }
}
// base from drone
void Dragon::GetNearestEntity(std::vector<IEntity *> scheduler)
{
  float minDis = 250; // for now min distance, TEST
  for (auto entity : scheduler)
  {
    float disToEntity = this->position.Distance(entity->GetPosition());
    if (disToEntity <= minDis)
    {
      std::cout << "DINNER DINNER DINNER DINNER DINNER..." << std::endl;
      minDis = disToEntity;
      nearestEntity = entity;
    }
  }

  if (nearestEntity)
  {
    available = false; // dragon unavailable because close entity found
    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination(); // use to track down robot associated with drone

    toFinalDestination = new BeelineStrategy(position, destination);
  }
}

void Dragon::Rotate(double angle)
{
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}