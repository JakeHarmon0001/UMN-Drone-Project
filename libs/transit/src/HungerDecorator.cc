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
    if(!isDead() && entity->getType() == "dragon"){ //
        if(entity->getHungerLevel() > 10){ 
            Vector3 temp = entity->GetPosition();
            if(temp[1] > 220){
                std::cout << "falling" << std::endl;
                temp[1] -= 0.6;
                entity->SetPosition(temp);
            } else {
                std::cout << "dead" << std::endl;
                if(!entity->isDead()){
                    entity->setDead(true);
                    dead = true;
                    entity->GetPublisher()->setMessage("Dragon has died\n");
                    entity->GetPublisher()->notify();
                    //entity->GetDetails()["mesh"] = new path
                }
                
                //entity->SetColor("RED");
            }
        } else {
            if(!strategy->IsCompleted()){ //keep moving
                std::cout << "normal move" << std::endl;
                strategy->Move(entity, dt);
            }
            
        }
    }   
}