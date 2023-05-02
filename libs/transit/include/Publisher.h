#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "Subscriber.h"
#include <string>
//using namespace routing;

class Publisher {
 public:
  Publisher();

  void sub(Subscriber* s);

  void notify();

  void setMessage(std::string newEvent);

 private:
  Subscriber* subscriber;
  std::string eventMessage;
};

#endif