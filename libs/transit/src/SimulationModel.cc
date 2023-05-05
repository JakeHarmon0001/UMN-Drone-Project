#include "SimulationModel.h"

#include "DragonFactory.h"
#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "NotificationService.h"
#include "Publisher.h"
#include "RobotFactory.h"
#include "SkeletonFactory.h"

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
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  // assign publisher to each entity
  myNewEntity->SetPublisher(publisher);
  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];

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
    if (entities[i]->getType() == "dragon") {
      entities[i]->Update(dt, entities);
    } else {
      entities[i]->Update(dt, scheduler);
    }
    controller.UpdateEntity(*entities[i]);
    if (entities[i]->isDead()) {
      if (entities[i]->getType() == "dragon") {
        // create skeleton JsonArray arr = {9.0, "Hello", 1, JsonArray()};
        JsonObject details = entities[i]->GetDetails();
        details["type"] = "skeleton";
        details["name"] = "Skeleton";
        details["mesh"] = "assets/model/mario_movie_-_dry_bones.glb";
        Vector3 temp = entities[i]->GetPosition();
        JsonArray jdon = {temp.x, temp.y + 42, temp.z};
        details["position"] = jdon;
        JsonArray scale = {0.2, 0.2, 0.2};
        details["scale"] = scale;

        CreateEntity(details);
      }
      controller.RemoveEntity(entities[i]->GetId());
      entities.erase(entities.begin() + i);
      i--;
    }
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
