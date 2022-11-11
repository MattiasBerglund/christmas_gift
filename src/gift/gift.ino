#include <NewPing.h>

#define PIN_SENSOR_0  12  
#define LED_SENSOR_0  10

#define PIN_SENSOR_1  3  
#define LED_SENSOR_1  2

#define MAX_DISTANCE  200
#define SONAR_NUM     2

int min_dist = 2;
int max_dist = 20;
int default_sensor = 999;
int active_sensor = default_sensor;
int next_sensor = default_sensor;
int min_sleep = 2000;
int max_sleep = 5000;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(PIN_SENSOR_0, PIN_SENSOR_0, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(PIN_SENSOR_1, PIN_SENSOR_1, MAX_DISTANCE), 
};

void setup() {
  pinMode(LED_SENSOR_0, OUTPUT);
  pinMode(LED_SENSOR_1, OUTPUT);
  Serial.begin(115200);
  startRandomLed();
}

void loop() {
  delay(50); // 29ms should be the shortest delay between pings

  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (active_sensor == i){
      checkContact(sonar[i].ping_cm(), i);
    }
  }
}

void checkContact(int dist, int sensor){
  if (dist >= min_dist && dist <= max_dist){
    printDist(dist);
    turnOffLeds();
    delay(random(min_sleep, max_sleep));
    startRandomLed();
  }
}

void startLedSensor0(){
  digitalWrite(LED_SENSOR_0, HIGH);
  digitalWrite(LED_SENSOR_1, LOW);
}

void startLedSensor1(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, HIGH);
}

void startRandomLed(){
  next_sensor = random(SONAR_NUM);
  Serial.print("Random number: ");
  Serial.print(next_sensor);
  if (next_sensor == 0){
      startLedSensor0();
    }
  else if (next_sensor == 1){
      startLedSensor1();
    }
  active_sensor = next_sensor;
  next_sensor = default_sensor;
}

void turnOffLeds(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
}

void printDist(int dist){
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");
}

// TODO
// [X] input from sensor
// [X] make led light
// [x] Toggle led with two sensors
// [X] light up one led, turn off with sensor
// [x] light up random led, turn off with sensor
// [x] light up random led within a random time, turn of with sensor