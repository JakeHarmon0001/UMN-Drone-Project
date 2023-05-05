#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "Subscriber.h"
#include <string>
//using namespace routing;

class Publisher {
 public:
  /**
   * @brief Instantiates new Publisher object
  */
  Publisher();

  /**
   * @brief Assigns new value to subscriber
   * @param s New subscriber value
  */
  void sub(Subscriber* s);

  /**
   * @brief Sends eventMessage to subscriber
  */
  void notify();

  /**
   * @brief Sets eventMessage of publisher
   * @param newEvent New value for eventMessage
  */
  void setMessage(std::string newEvent);

 private:
  Subscriber* subscriber;
  std::string eventMessage;
};

#endif