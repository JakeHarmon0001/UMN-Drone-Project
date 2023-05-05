# Team-001-27-homework4

## What is the project about (overview of the whole project, not just the hw4)?
This project consists of an uber-like drone system where there are drones which transport robots around the map as scheduled using various movement patterns, while dragons can be introduced to hunt these drones. In this project, there are five types of entities: drones, robots, humans, dragons, and skeletons. The drones are responsible for taking the robots on trips by picking them up and dropping them off via the specified pattern. The robots are entities which are created in the scheduler and get picked up and dropped off by drones. They also specify by which pattern they want to travel. The humans are entities which are completely unrelated to the trip system and randomly run around the map. When introduced, the dragons roam the map randomly and will beeline to a drone in order to eat it when one comes within range, and have a hunger attribute. When the dragons become too hungry, they will die. Thus the skeletons will spawn on the map where the dragons die, in order to show where the dragons have died.

## How to run the simulation (overview of the whole project, not just the hw4)?
The simulation is run via two container-hosted pages: one simulation page which displays the map where drones are to pick up and drop off robots, one scheduler page which allows the user to schedule trips and add entities as wanted. On the simulation page, one can navigate the map by choosing which entity they want to follow and can also specify simulation speed. There is also a notification center on the left side of the screen where it is tinted gray. This notification center will alert the user to events happening in the simulation. On the scheduler, one can schedule a trip for a robot and specify which movement strategy the drone will take. One can also add dragons and humans as they desire via buttons on the page.

## What does the simulation do specifically (individual features i.e. movement of entities etc) (overview of the whole project, not just the hw4)?
Specifically in the simulation, drones will be idle until a trip is requested for a robot. If the drone is the closest to the requested robot, it will beeline for the robot to pick it up and then take the requested movement pattern to drop the robot off. The drone will then remain idle until it is needed again. The robots will only be spawned when a trip is requested. They will be picked up by a drone and dropped off at their destination, where they will remain in place. The dragons, upon introduction, will fly randomly until they come upon a drone which they will pursue and then eat. When a drone is eaten, the dragon will lose hunger thus sustaining their life longer. Upon being eaten, a drone will “die” and respawn randomly on the map, in order to keep two drones active at all times. If the drone was in progress heading to pick up a robot, that robot will be unfortunately stranded and won’t be picked up. If the drone was in progress delivering a robot, both the robot and drone will unfortunately die. The dragons continue flying randomly and pursuing drones until they become too hungry, which will cause them to fall and die. Upon death, a skeleton will take their place in order to represent the dead dragon. The skeletons will simply stand in the place of a dead dragon for the remainder of the simulation. 

# New Feature

## What does it do?
There are two new features: the dragons that roam the skies and the notifications on the left side of the screen on the simulation. The dragons are spawned by pressing a button on the scheduler page. They will roam by randomly selecting a point and flying straight to it, and repeating. However, whenever the dragon comes within a certain radius of a drone, it will begin to fly directly at the drone, and will continue to do so until it reaches the drone. The dragon also increases its speed when it is pursuing. Once the dragon reaches the drone the drone is “killed”, where it is reset to its default state and sent to a random point on the map. The dragon returns to its roaming state. If the drone was carrying a robot, the robot is deleted. While all of this is happening, a “hunger” attribute of Dragon is increasing in correspondence with its speed. If hunger reaches a certain level, the dragon “dies”, where it falls to the ground and is replaced with a different model upon landing. It is no longer of interest at this point. Whenever a dragon eats a drone, its hunger is reset back to 0, keeping it alive longer. Anytime a dragon eats a drone or dies, or a drone starts a route, picks up a robot, or finishes a route, a notification is sent to the notification bar on the simulation page. The notification is labeled according to the name of the entity.

## Why is it significantly interesting?
The dragon addition is interesting because it adds a sense of life and autonomy to the simulation. Everytime you run the simulation, it has a sense of randomness and interest as you don’t know exactly what is going to happen. Will your robot get to its destination or will it perish to the dragon? You don’t know which makes the simulation more fun to use. The notifications are a welcome addition because it gives the user more clarity on what has happened, and they no longer have to always be looking to know what happened. And when there are many moving entities it can be unclear what has happened, so the notifications alleviate that.

## How does it add to the existing work? 
It adds a sort-of unpredictable nature to the simulation. Now, instead of just drones picking up and dropping off robots as normal, the drones can be killed and trips will be canceled. The drones have to get lucky to avoid the dragons roaming the map, which definitely makes the simulation more interesting to watch. Also, the dragons eating the drones is necessary for the dragons to survive longer. So, it adds this element of a predator which tries its best to eat the drones for its own survival, which definitely makes the system more unpredictable and entertaining to observe. The notifications will keep the user up-to-date on those dragons: how often they get a kill and when they eventually die. Also, the notifications will let the user know the progress of each scheduled trip. Thus, the notifications add readability/trackability to allow the user to keep better track of what’s going on and the dragons add unpredictability & entertainment in order to create a more fantastical and fun simulation.

## Which design pattern did you choose to implement it and why?
For the dragons, we used the decorator design pattern and for the notifications, we used the observer pattern. We implemented the decorator pattern by decorating the dragon's movement to handle it falling to the ground when it dies. Everytime the dragon is assigned a new movement strategy, it is wrapped in HungerDecorator(). Within HungerDecorator, the dragon's hunger is checked before moving. If it is past the death threshold, instead of moving as normal, it is lowered to the ground. We figured the decorator pattern would work well here because the death movement is just another simple feature that is independent of the normal movement. That way, the decorator can just do a simple check and either do the standard movement, or it can do the additional feature. The notifications were implemented with Publisher and NotificationService classes. NotificationService is a subclass of Subscriber, and it handles passing the received messages to the front end. Both classes are instantiated in SimulationModel and the Publisher is given to every entity upon its creation. This allows entities to pass notifications to the NotificationService, where they can be handled. This pattern works well as it provides a link between individual entities and the main source of operations. The only main difference between how we implemented it and a standard implementation is that instead of one publisher and many subscribers, there are many publishers (although it is actually the same instance) and only one subscriber. It works well though and is a rather lightweight feature to add.

## Instruction to use this new feature (if the new feature is not user interactable, please mention this as well)
First, in order to utilize the dragons, one must click the “Add Dragon” button on the scheduler page to add a dragon into the simulation. They are allowed to add as many dragons as they’d like, however adding too many dragons will create a messy and most likely laggy simulation. After that, all the user has to do is observe. Second, the notifications are already built into the simulation. So this feature is not user-interactable.

## Sprint retrospective
As a team we had a setup where our sprints consisted of many spread out, multiple-hour-long sessions where we would all work together to add our features to the project. Although maybe a bit unconventional, we really never worked on actual implementation of code alone. We always got together as a group where at least two people would be working together to code. Our sessions were extremely productive and we would end them all exhausted with tired eyes and brains. For example, a few days ago we all hopped on discord for about five hours in order to implement the skeletons for when the dragons died. We all found comfort in working together as a team, and found it to be more efficient often having four sets of eyes on the code. We definitely spent more time on our dragon feature sprint than our notification feature sprint, but we still thought doing sprints for each was a good setup.

![uml](https://gdurl.com/zFYL)

# Links

## Youtube Video:
[Youtube video](https://youtu.be/vL4VMHbMucA)

## Dockerhub Repo:
LINK LINK LINK
