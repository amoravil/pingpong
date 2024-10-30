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

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);
STARTUP(cellular_credentials_set("hologram", "", "", NULL));

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// This function is called when the Particle.function is called
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
        // Unknown option
        Log.info("UNKNOWN OPTION");
        return -1;
    }
}



// setup() runs once, when the device is first turned on
void setup() {
    // In order to set a pin, you must tell Device OS that the
    // pin is an OUTPUT pin.
    // This is often done from setup() since you only need to
    // do it once.
    pinMode(MY_LED, OUTPUT);

    // This registers a function call. When the function "led"
    // is called from the cloud, the ledToggle() function above
    // will be called.
    Particle.function("led", ledToggle);
  // Put initialization like pinMode and begin functions here
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  
  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
   //Log.info("Sending Hello World to the cloud!");
   //Particle.publish("Hello world!");
   //delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
