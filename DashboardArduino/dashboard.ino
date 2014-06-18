#include <SPI.h>
#include <Ethernet.h>
#include "string.h"
#include "ardui_wrapper.h"

// Some Ethernet shields have a MAC address printed on a sticker on the shield;
// fill in that address here, or choose your own at random:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };



char pubkey[] = "demo";
char subkey[] = "demo";
char channel[] = "button-reply";
char uuid[] = "Arduino";

dashjazz ard;



void do_something(String value){
          Serial.println("in the callback");
          Serial.println(value);
        }

void setup()
{
       
	Serial.begin(9600);
	Serial.println("Serial set up");

	while (!Ethernet.begin(mac)) {
		Serial.println("Ethernet setup error");
		delay(1000);
	}
	Serial.println("Ethernet set up");

        
	ard.dashinit( pubkey, subkey, uuid); 
	Serial.println("PubNub set up");
       
}

void loop()
{      
        String returnmessage;
	Ethernet.maintain();
        
        //Publish
	Serial.println("publishing a message");
        ard.dashsend(channel,"\"Hey There\"");
        

        //Subscribe
	Serial.println("waiting for a message (in the subscribe function subscribe)");
        returnmessage = ard.dashconnect(channel);
        
        // calbback function of sorts, to work with the received message
        do_something(returnmessage);
	Serial.println();
}
