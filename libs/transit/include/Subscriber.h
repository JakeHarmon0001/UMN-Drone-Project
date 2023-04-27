#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

using namespace routing;

/**
 * @class Subscriber
 * @brief Represents an subscriber in a notification system.
 *
 * An Subscriber object has a 
 */
class Subscriber {
 public:
  /**
   * @brief Updates the current message to be relayed.
   */
  void update(std::string newEvent);

 protected:
  std::string currMessage;
};

#endif