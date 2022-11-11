#include <NewPing.h>

#define LEFT_TRIGGER_PIN  12  
#define LEFT_ECHO_PIN     11  
#define LEFT_LED_PIN      10

#define RIGHT_TRIGGER_PIN  3  
#define RIGHT_ECHO_PIN     4  
#define RIGHT_LED_PIN      2

#define MAX_DISTANCE 200
#define SONAR_NUM 2

int min_dist = 2;
int max_dist = 20;
NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE), 
};

void setup() {
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  delay(50); // 29ms should be the shortest delay between pings.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    checkContact(sonar[i].ping_cm(), i);
  }
}

void checkContact(int dist, int sensor){
  if (dist > min_dist && dist < max_dist){
    Serial.print("Ping: ");
    Serial.print(dist);
    Serial.println("cm");
    if (sensor == 0){
      digitalWrite(LEFT_LED_PIN, HIGH);
      digitalWrite(RIGHT_LED_PIN, LOW);
    }
    else if (sensor == 1){
      digitalWrite(RIGHT_LED_PIN, HIGH);
      digitalWrite(LEFT_LED_PIN, LOW);
    }
  }
}

// TODO
// [X] input from sensor
// [X] make led light
// [x] Toggle led with two sensors
// [] light up one led, turn off with sensor
// [] light up random led, turn off with sensor
// [] light up random led within a random time, turn of with sensor