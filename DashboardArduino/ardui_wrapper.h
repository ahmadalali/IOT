#include "PubNub.h"
#include <SPI.h>
#include <Ethernet.h>


class dashjazz{
  public:
  
  const char *publish_key;
  const char *subscribe_key;
  const char *uuid;
  const char *channel;
  const char *message;
  
  bool dashinit(const char *publish_key, const char *subscribe_key, const char *uuid);
  bool dashsend(const char *channel, const char *message);
  String dashconnect(const char *channel);
  
  
  
};
  

bool dashjazz::dashinit(const char *publish_key, const char *subscribe_key, const char *uuid){
  
  PubNub.begin(publish_key,subscribe_key);
  PubNub.set_uuid(uuid);
  Serial.println("initialized the variables");
}

bool dashjazz::dashsend(const char *channel, const char *message){
  EthernetClient *client;
  client = PubNub.publish(channel,message);
  return client;
}

String dashjazz::dashconnect(const char *channel){
  
  String message = "";
  int i = 0;
  PubSubClient *pclient = PubNub.subscribe(channel);
	if (!pclient) {
		return 0;
	}
  while (pclient->wait_for_data()) {
		char c = pclient->read();
		//Serial.print(c);
                message += c;
	}


	pclient->stop();
	Serial.println();
  return message;
  
}
  
