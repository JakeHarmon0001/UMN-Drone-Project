#include "HungerDecorator.h"
#include "math/vector3.h"

HungerDecorator::HungerDecorator(IStrategy* strategy) {
    this->strategy = strategy;
    dead = false;
}
HungerDecorator::~HungerDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

bool HungerDecorator::isDead() {
    return dead;
}

bool HungerDecorator::IsCompleted(){
    return isDead() || strategy->IsCompleted();
}

void HungerDecorator::Move(IEntity* entity, double dt){
    if(!isDead() && entity->getType() == "dragon"){
        if(entity->getHungerLevel() > 30){ 
            Vector3 temp = entity->GetPosition();
            if(temp[1] > 220){
                temp[1] -= 0.6;
                entity->SetPosition(temp);
            } else {
                dead = true;
            }
            
            
        } else {
            if(!strategy->IsCompleted()){
                std::cout << "beeline move" << std::endl;
                strategy->Move(entity, dt);
            }
            
        }
    }
    
}