#include "SimulationModel.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "DragonFactory.h"
#include "SkeletonFactory.h"
#include "NotificationService.h"
#include "Publisher.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new DragonFactory());
  AddFactory(new SkeletonFactory());
  
  notifier = new NotificationService(controller);
  publisher = new Publisher();
  publisher->sub(notifier);
  
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
  delete publisher;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::cout << "creating entity" << std::endl;
  // std::cout << "type: ";
  // std::cout << entity["type"] << std::endl;
  // std::cout << "name: ";
  // std::cout << entity["name"] << std::endl;
  std::cout << "position: ";
  std::cout << entity["position"] << std::endl;
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;
  
  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  //assign publisher to each entity
  myNewEntity->SetPublisher(publisher);
  // Call AddEntity to add it to the view
  std::cout << "Controller adding entity" << std::endl;
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    if(entities[i]->getType() == "dragon"){
      entities[i]->Update(dt, entities);
    } else {
      entities[i]->Update(dt, scheduler);
    }
    controller.UpdateEntity(*entities[i]);
    if(entities[i]->isDead()){
      std::cout << "something is dead" << std::endl;
      if(entities[i]->getType() == "dragon") {
        
        std::cout << entities[i]->GetId() << std::endl;
        std::cout << "identified dead entity as dragon" << std::endl;
        //create skeleton JsonArray arr = {9.0, "Hello", 1, JsonArray()};
        JsonObject details = entities[i]->GetDetails();
        details["type"] = "skeleton";
        details["name"] = "Skeleton";
        details["mesh"] = "assets/model/squid_game_red_circle.glb"; 
        Vector3 temp = entities[i]->GetPosition();
        JsonArray jdon = {temp.x, temp.y, temp.z};
        details["position"] = jdon;

        CreateEntity(details);
      }
      controller.RemoveEntity(entities[i]->GetId());
      entities.erase(entities.begin()+i);
      i--;
    }
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
