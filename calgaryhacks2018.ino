// This #include statement was automatically added by the Particle IDE.
#include <SHT1x.h>
#include "cellular_hal.h"

// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));
//gas
float sensor_value;
double ratio;
//motion
bool motion_active = false;
int pir = D4; //connect the PIR output to pin D0 of the Electron
// temperature+ humidity
double var_temperature = 2.0;
double var_humidity = 3.0;
int data_pin = A5;
int clock_pin = A4;
SHT1x sht1x(data_pin, clock_pin);
// sound
int noise_pin = D2;
int noise_level;


void setup() {
    // Set the keep-alive value for TELUS SIM card
    Particle.keepAlive(30);
    Serial.begin(9600);
    //gas
    Particle.variable("gas", ratio);
    Particle.variable("motion", motion_active);
    Particle.variable("temperature", var_temperature);
    Particle.variable("humidity", var_humidity);
    Particle.variable("noise", noise_level);

    //motion
    pinMode(pir, INPUT_PULLDOWN);

}

void loop() {
    gas();
    motion();
    temperature();
    humidity();
    noise();
}

void gas() {
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS

    int sensor_value = analogRead(A0);
    sensor_volt=(float)sensor_value/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    ratio = RS_gas/0.67; // ratio = RS/R0
    delay(1000);
}

void motion() {
  if (digitalRead(pir) == HIGH) {
    motion_active = true;
    Particle.publish("motion","high",60); //publish an event
    delay(1000);
      while (digitalRead(pir) == HIGH); // wait for the sensor to return back to normal
  }
  motion_active = false;
}

void temperature() {
    var_temperature = sht1x.readTemperatureC();
}

void humidity() {
    var_humidity = sht1x.readHumidity();
}

void noise(){
    delay(10);
    noise_level = analogRead(noise_pin);
    Serial.println(noise_level);
    delay(200);
}