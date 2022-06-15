#include <Arduino.h>
const int TRIG_PIN = 12;
const int ECHO_PIN = 13;
float temp_In_C = 20.0;  // Can enter actual air temp here for maximum accuracy
float speed_Of_Sound;          // Calculated speed of sound based on air temp
float distance_Per_uSec;      // Distance sound travels in one microsecond

//===============================================================================
//  Initialization
//===============================================================================
void setup() {
    pinMode(TRIG_PIN,OUTPUT);
    pinMode(ECHO_PIN,INPUT);
    // Formula to calculate speed of sound in meters/sec based on temp
    speed_Of_Sound = 331.1 +(0.606 * temp_In_C);
    // Calculate the distance that sound travels in one microsecond in centimeters
    distance_Per_uSec = speed_Of_Sound / 10000.0;
    Serial.begin(9600);
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
    double duration, distanceCm, distanceIn, distanceFt;

    digitalWrite(TRIG_PIN, HIGH);       // Set trigger pin HIGH
    delayMicroseconds(20);              // Hold pin HIGH for 20 uSec
    digitalWrite(TRIG_PIN, LOW);        // Return trigger pin back to LOW again.
    duration = pulseIn(ECHO_PIN,HIGH);  // Measure time in uSec for echo to come back.

    // convert the time data into a distance in centimeters, inches and feet
    duration = duration / 2.0;  // Divide echo time by 2 to get time in one direction
    distanceCm = duration * distance_Per_uSec;
    distanceIn = distanceCm / 2.54;
    distanceFt = distanceIn / 12.0;

    if (distanceCm <= 0){
        Serial.println("Out of range");
    }
    else {
        Serial.print(duration, 0);
        Serial.print("uSec, ");
        Serial.print(distanceCm, 0);
        Serial.print("cm,  ");
        Serial.print(distanceIn,0);
        Serial.print("in, ");
        Serial.print(distanceFt,1);
        Serial.print("ft, ");
        Serial.println();
    }
    delay(1000);  // Delay between readings
}
