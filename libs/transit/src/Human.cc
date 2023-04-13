#define _USE_MATH_DEFINES
#include <random>
#include <cmath>
#include <limits>
#include "Human.h"
#include "AstarStrategy.h"



Human::Human(JsonObject& obj) : details(obj) {

  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
  strategyName = "Beeline";
  int num1 = rand() % (1500 - (-1400) + 1) + (-1400);
  int range2 = 240 - 500 + 1;
  int num2 = rand() % (500 - 240 +1) + 240;
  int range3 = -800 - 800 + 1;
  int num3 = rand()  % (800 - (-800) + 1) + (-800);
  finalDestination = {num1, num2, num3};
}

Human::~Human() {
    delete graph;
}

void Human::Update(double dt, std::vector<IEntity*> scheduler) {
  if(graph != nullptr){
    if(toFinalDestination != nullptr){
      if(toFinalDestination->IsCompleted()) {
        int num1 = rand() % (1500 - (-1400) +1) + (-1400);
        int range2 = 240 - 500 + 1;
        int num2 = rand() % (500 - 240 +1) + 240;
        int range3 = -800 - 800 + 1;
        int num3 = rand()  % (800 - (-800) + 1) + (-800);
        destination = finalDestination;
        finalDestination = {num1, 300, num3};
        toFinalDestination = new AstarStrategy(destination, finalDestination, graph); // could potentially causes a problem
        
      } else {
        toFinalDestination->Move(this, dt);
        
      }
    } else {
      toFinalDestination = new AstarStrategy(position, finalDestination, graph); //using position, not destination
    }
    
    
  }
    
}

void Human::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
