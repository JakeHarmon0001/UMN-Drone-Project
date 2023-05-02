#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include <string>
//using namespace routing;

/**
 * @class Subscriber
 * @brief Represents an subscriber in a notification system.
 *
 * An Subscriber object has a 
 */
class Subscriber {
 public:

 Subscriber() : currMessage("NO EVENT") {};
  /**
   * @brief Updates the current message to be relayed.
   */
  virtual void update(std::string newEvent);

 protected:
  std::string currMessage;
};

#endif