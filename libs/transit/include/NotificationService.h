#ifndef NOTIFICATION_SERVICE_H_
#define NOTIFICATION_SERVICE_H_

#include <map>
#include <chrono>
#include "WebServer.h"
#include "routing_api.h"
#include "Subscriber.h"
#include "IController.h"
// using namespace routing;

//Handles receiving messages and relays them from front-end to back-end
class NotificationService : public Subscriber {
 public:
  NotificationService(IController& c);

  void update(std::string newEvent);

  void displayMessage();

 private:
  IController& controller;
};

#endif