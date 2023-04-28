// #include "Subscriber.h"
// #define MAX_SUBS = 1;

// using namespace routing;

// class Publisher {
//  public:
//   void sub(Subscriber s) {
// 	subscribers[subs] = s;
// 	subs++;
//   }

//   void unsub(Subscriber s) {
// 	subscribers[0] = nullptr;
// 	subs--;
//   }

//   void notify() {
// 	for(int i = 0; i < MAX_SUBS; i++){
// 		subscribers[i].update(eventMessage);
// 	}
//   }

//   void setMessage(std::string newEvent) {
// 	eventMessage = newEvent;
//   }

//  private:
//   Subscriber subscribers[MAX_SUBS];
//   std::string eventMessage;
//   int subs = 0;
// };