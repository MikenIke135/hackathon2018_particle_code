#include "cellular_hal.h"

// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));
float sensorValue;
String gasVal; 

void setup() {
    // Set the keep-alive value for TELUS SIM card
    Particle.keepAlive(30);
    Serial.begin(9600);
    Particle.variable("gas", gasVal);
    Particle.variable("test", 1);
}   

void loop() {
     float sensor_volt;
     float RS_air; // Get the value of RS via in a clear air
     float R0; // Get the value of R0 via in H2
   
    /*--- Get a average data by testing 100 times ---*/
     for(int x = 0 ; x < 100 ; x++) {
        sensorValue = sensorValue + analogRead(A0);
     }
     sensorValue = sensorValue/100.0;
     gasVal = String::format("%f", sensorValue);
    /*-----------------------------------------------*/
     sensor_volt = sensorValue/1024*5.0;
     RS_air = (5.0-sensor_volt)/sensor_volt; // omit *RL
     R0 = RS_air/10.0; // The ratio of RS/R0 is 10 in a clear air
     Serial.print("sensor_volt = ");
     Serial.print(sensor_volt);
     Serial.println("V");
     Serial.print("R0 = ");
     delay(100);
}
