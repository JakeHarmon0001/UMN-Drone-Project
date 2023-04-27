#define _USE_MATH_DEFINES
#include "Dragon.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

Dragon::Dragon(JsonObject& obj) : details(obj) {
  std::cout << "new dragon" << std::endl;
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
}

Dragon::~Dragon() {
  // Delete dynamically allocated variables
  delete graph;
}

void Dragon::CreateNewDestination() {
    destination = {Random(-1400, 1500), position.y, Random(-800, 800)};
    toDestination = new BeelineStrategy(position, destination);
}

void Dragon::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Dragon::GetNearestEntity(std::vector<IEntity *> scheduler){
  // std::cout << "dragon getnearestentity" << std::endl;
  float maxRange = 999999;
  for (auto entity : scheduler)
  {
    // std::string val = entity->GetDetails()["type"];
    //if(entity->GetDetails()["type"] == "drone"){}
    // std::cout << entity->getType() << std::endl;
    std::cout << "checking entity" << std::endl;
    if(entity->getType() == "drone"){
      std::cout << "found drone" << std::endl;
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= maxRange){
        maxRange = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity)
  {
    available = false; // dragon unavailable because close entity found
    destination = nearestEntity->GetPosition();
    toDestination = new BeelineStrategy(position, destination);
  }
}

void Dragon::addController(IController* controller){
  this->controller = controller;
}

void Dragon::Update(double dt, std::vector<IEntity*> scheduler) {
  if(available){ //roaming
    if(toDestination) {
        if(toDestination->IsCompleted()) {
            CreateNewDestination();
        } else { //getnearestentity
             this->GetNearestEntity(scheduler); // scan for drone
            toDestination->Move(this, dt);
        }
    } else {
        CreateNewDestination();
    }
  } else { // pursuit
    if(toDestination){
      if(this->position.Distance(nearestEntity->GetPosition()) < 10){
        nearestEntity->SetPosition({Random(-1400, 1500), position.y, Random(-800, 800)}); // move drone to new random location
        available = true; // dragon now roaming
       CreateNewDestination();
      } else {
        destination = nearestEntity->GetPosition();
        delete toDestination;
        toDestination = new BeelineStrategy(position, destination);
        toDestination->Move(this,dt);
      }
      
    }
    
  }
    
}