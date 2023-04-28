#define _USE_MATH_DEFINES
#include "Dragon.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"
#include "HungerDecorator.h"

Dragon::Dragon(JsonObject& obj) : details(obj) {
  std::cout << "new dragon" << std::endl;
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  hungerLevel = 0;
}

Dragon::~Dragon() {
  // Delete dynamically allocated variables
  delete graph;
}

void Dragon::CreateNewDestination() {
  if(toDestination){
    delete toDestination;
  }
  double tempx = Random(-1400, 1500);
  double tempz = Random(-800, 800);
  std::cout << "x: " << tempx << " z: " << tempz << std::endl;
  destination = {tempx, position.y, tempz};
  this->setSpeed(20);
  toDestination = new HungerDecorator(new BeelineStrategy(position, destination));
  std::cout << "setting new toDestination" << std::endl;
}

void Dragon::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Dragon::GetNearestEntity(std::vector<IEntity *> scheduler){
  // std::cout << "dragon getnearestentity" << std::endl;
  float maxRange = 400;
  IEntity* tempnearestEntity = nullptr;
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
        tempnearestEntity = entity;
      }
    }
  }

  if (tempnearestEntity)
  {
    nearestEntity = tempnearestEntity;
    available = false; // dragon unavailable because close entity found
    destination = nearestEntity->GetPosition();
    this->setSpeed(35);
    toDestination = new HungerDecorator(new BeelineStrategy(position, destination));
  }
}

void Dragon::addController(IController* controller){
  this->controller = controller;
}

void Dragon::Update(double dt, std::vector<IEntity*> scheduler) {
  // std::cout << dt << std::endl;
  if(available){ //roaming
  std::cout << "isAvailable" << std::endl;
  // std::cout << "available" << std::endl;
    if(toDestination) {
        if(toDestination->IsCompleted()) {
          std::cout << "getting new destination" << std::endl;
            CreateNewDestination();
        } else { //getnearestentity
            setHungerLevel(getHungerLevel() + dt/2);
            toDestination->Move(this, dt);
            this->GetNearestEntity(scheduler); // scan for drone
        }
    } else {
      std::cout << "newdestination2" << std::endl;
        CreateNewDestination();
    }
  } else { // pursuit
  // std::cout << "not available" << std::endl;
    if(toDestination){
      if(this->position.Distance(nearestEntity->GetPosition()) < 20){
        if(nearestEntity->isPickedUp()) {
          if(nearestEntity->getterNearestEntity()){
            if(nearestEntity->getterNearestEntity()->getType() == "robot"){
              nearestEntity->getterNearestEntity()->setDead(true);
            }
          }
        }
        nearestEntity->SetPosition({Random(-1400, 1500), position.y, Random(-800, 800)}); // move drone to new random location
        // nearestEntity = nullptr;
        nearestEntity->resetEntity();
        std::cout << "close to drone" << std::endl;
        available = true; // dragon now roaming
        std::cout << "newdestination1" << std::endl;
        CreateNewDestination();
        setHungerLevel(0);
        
      } else {
        setHungerLevel(getHungerLevel() + dt);
        destination = nearestEntity->GetPosition();
        delete toDestination;
        toDestination = new HungerDecorator(new BeelineStrategy(position, destination));
        toDestination->Move(this,dt);
      }
      
    }
  }
    
}