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
  if(toDestination) {
    delete toDestination;
  }
  double tempx = Random(-1400, 1500);
  double tempz = Random(-800, 800);
  destination = {tempx, position.y, tempz};
  this->setSpeed(20);
  toDestination = new HungerDecorator(new BeelineStrategy(position, destination));
}

void Dragon::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Dragon::GetNearestEntity(std::vector<IEntity *> scheduler) {
  float maxRange = 400; //range to search
  IEntity* tempnearestEntity = nullptr;
  for (auto entity : scheduler) 
  {
    if(entity->getType() == "drone"){ //only look for drones
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= maxRange){ //if drone is in range
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
    this->setSpeed(35); //update dragon speed
    toDestination = new HungerDecorator(new BeelineStrategy(position, destination)); //set dragon to beeline to its new entity
  }
}

void Dragon::addController(IController* controller){
  this->controller = controller;
}

void Dragon::Update(double dt, std::vector<IEntity*> scheduler) {
  if(available) { //Dragon roaming
    if(toDestination) {
        if(toDestination->IsCompleted()) {
          CreateNewDestination();
        } else { //getnearestentity
          setHungerLevel(getHungerLevel() + dt/2); //update hunger level
          toDestination->Move(this, dt);
          this->GetNearestEntity(scheduler); // scan for drone
      }
    } else {
        CreateNewDestination();
    }
  } else { //Dragon in pursuit
    if(toDestination){
      if(this->position.Distance(nearestEntity->GetPosition()) < 20){ //if dragon is close enough 
        if(nearestEntity->isPickedUp()) { //if nearest entity pickedUp == true
          if(nearestEntity->getterNearestEntity()){ 
            if(nearestEntity->getterNearestEntity()->getType() == "robot"){ //checking for type
              nearestEntity->getterNearestEntity()->setDead(true); //set robot to dead to be deleted later
            }
          }
        }
        nearestEntity->SetPosition({Random(-1400, 1500), position.y, Random(-800, 800)}); // move drone to new random location
        publisher->setMessage(std::string(details["name"]) + ": Killed " + std::string(nearestEntity->GetDetails()["name"]) + "\n");
        publisher->notify();
        nearestEntity->resetEntity();
        available = true; // dragon now roaming
        CreateNewDestination();
        setHungerLevel(0); // reset dragon hunger meter
        
      } else {
        setHungerLevel(getHungerLevel() + dt); //update hunger level based on time spent roaming
        destination = nearestEntity->GetPosition();
        delete toDestination;
        toDestination = new HungerDecorator(new BeelineStrategy(position, destination));
        toDestination->Move(this,dt);
      }
    }
  }
}

//void Dragon::changeMesh(string newMesh) {
//  details["mesh"] = "assets/model/dragon_head.glb";
//
//}