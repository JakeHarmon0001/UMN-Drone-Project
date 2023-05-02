#include "Publisher.h"

Publisher::Publisher() {
  eventMessage = "NO EVENT";
}

void Publisher::sub(Subscriber* s) {
  subscriber = s;
}

void Publisher::notify() {
  subscriber->update(eventMessage);
}

void Publisher::setMessage(std::string newEvent) {
  eventMessage = newEvent;
}