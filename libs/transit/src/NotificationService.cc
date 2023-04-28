#include <map>
#include <chrono>
#include "WebServer.h"
#include "SimulationModel.h"
#include "routing_api.h"
#include "Subscriber.h"
using namespace routing;

//Handles receiving messages and relays them from front-end to back-end
class NotificationService : public Subscriber {
 public:

  void update(std::string newEvent) {
    currMessage = newEvent;
    displayMessage();
  }

  void displayMessage() {
    JsonObject notification;
    notification["event"] = "observe";
    notification["details"] = currMessage;
    // sendMessage(notification.ToString()); 
  }

};