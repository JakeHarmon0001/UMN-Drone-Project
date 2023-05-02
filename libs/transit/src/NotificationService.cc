#include "NotificationService.h"

//Handles receiving messages and relays them from front-end to back-end

NotificationService::NotificationService(IController& c) : controller(c) {
  currMessage = "NO EVENT";
}

void NotificationService::update(std::string newEvent) {
  currMessage = newEvent;
  displayMessage();
}

void NotificationService::displayMessage() {
  JsonObject notification;
  notification["info"] = currMessage;
  controller.SendEventToView("observe", notification);
}