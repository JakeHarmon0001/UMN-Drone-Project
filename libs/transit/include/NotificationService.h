#ifndef NOTIFICATION_SERVICE_H_
#define NOTIFICATION_SERVICE_H_

#include <map>
#include <chrono>
#include "WebServer.h"
#include "routing_api.h"
#include "Subscriber.h"
#include "IController.h"
// using namespace routing;


/**
 * @brief Handles receiving messages and relays them from front-end to back-end
*/
class NotificationService : public Subscriber {
 public:
 /**
  * @brief Instatiates new NotificationService Option
  * @param c IController reference for controller
 */
  NotificationService(IController& c);

  /**
   * @brief Updates the notifiers currMessage
   * @param newEvent new value for currMessage
  */
  void update(std::string newEvent);

  /**
   * @brief Sends new message to the notification bar
  */
  void displayMessage();

 private:
  IController& controller;
};

#endif