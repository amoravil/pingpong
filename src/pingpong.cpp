/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "cellular_hal.h"

const pin_t MY_LED = D7;
const String MY_PLAYER = "SBH9905";
const String PLAYER_2 = "8FLJ829";
bool published;


// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Set ellular credentials
STARTUP(cellular_credentials_set("hologram", "", "", NULL));

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// Set let D7 on/off
int ledToggle(String command)
{
    if (command.equals("on"))
    {
        digitalWrite(MY_LED, HIGH);
        Log.info("MY_LED = ON");
        return 1;
    }
    else if (command.equals("off"))
    {
        digitalWrite(MY_LED, LOW);
        Log.info("MY_LED = OFF");
        return 0;
    }
    else
    {
        Log.info("UNKNOWN OPTION");
        return -1;
    }
}

// Function called when the cloud tells us that an event is published.
void myHandler(const char *event, const char *data)
{
    if (strcmp(data, MY_PLAYER) == 0)
    {
        published = false;
        while (!published)
        {
            ledToggle("on");
            Log.info("Playing %s", (const char*)MY_PLAYER);
            delay( 5 * 1000 );
            Log.info("Sending ball to %s", (const char*)PLAYER_2);
            published = Particle.publish("ballStatus", PLAYER_2);
            if (!published) 
            {
                Log.info("Fail publishing message to %s", (const char*)PLAYER_2);           
            }
        }
        ledToggle("off");
        Log.info("Should be playing %s", (const char*)PLAYER_2);
    }
    else if (strcmp(data, PLAYER_2) == 0)
    {
        Log.info("Playing %s", (const char*)PLAYER_2);
    }
    else
    {
        Log.info("UNKNOWN OPTION in event");
    }
}

int getBall(String command)
{
    bool play = false;
    play = Particle.publish("ballStatus", MY_PLAYER);
    if (!play)
    {
        return -1;
    }
    return 1;
}

// setup() runs once, when the device is first turned on
void setup() {
    pinMode(MY_LED, OUTPUT);
    Particle.function("led", ledToggle);
    Particle.function("ball", getBall);
    Particle.subscribe("ballStatus", myHandler);
}
//review how to use a state machine here
// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  
  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
   //Log.info("Sending Hello World to the cloud!");
   //Particle.publish("Hello world!");
   //delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
