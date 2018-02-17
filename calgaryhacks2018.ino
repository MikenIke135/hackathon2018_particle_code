#include "cellular_hal.h"

// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));
float sensorValue;
double ratio;

void setup() {
    // Set the keep-alive value for TELUS SIM card
    Particle.keepAlive(30);
    Serial.begin(9600);
    Particle.variable("gas", ratio);
    Particle.variable("test", 1);
}

void loop() {
    gas();
}

void gas() {
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/0.67; // ratio = RS/R0
    /*-----------------------------------------------------------------------*/
    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
    Serial.print("\n\n");
    delay(1000);
}
