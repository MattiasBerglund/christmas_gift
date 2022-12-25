#include <NewPing.h>

#define PIN_SENSOR_0  2  
#define LED_SENSOR_0  3

#define PIN_SENSOR_1  4  
#define LED_SENSOR_1  5

#define PIN_SENSOR_2  6  
#define LED_SENSOR_2  7

#define PIN_SENSOR_3  8  
#define LED_SENSOR_3  9

#define PIN_SENSOR_4  10  
#define LED_SENSOR_4  11


#define MAX_DISTANCE  200
#define SONAR_NUM     5

// User Settings
int min_dist = 2;
int max_dist = 20;
int rounds = 10;
int times[10];
int min_sleep = 0;
int max_sleep = 0;

// Variables
int played_rounds = 1;
int default_sensor = 999;
int active_sensor = default_sensor;
int next_sensor = default_sensor;
int start_time = 0;
int stop_time = 0;
int start_round_time = 0;


NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(PIN_SENSOR_0, PIN_SENSOR_0, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(PIN_SENSOR_1, PIN_SENSOR_1, MAX_DISTANCE), 
  NewPing(PIN_SENSOR_2, PIN_SENSOR_2, MAX_DISTANCE), 
  NewPing(PIN_SENSOR_3, PIN_SENSOR_3, MAX_DISTANCE), 
  NewPing(PIN_SENSOR_4, PIN_SENSOR_4, MAX_DISTANCE), 
};

void setup() {
  pinMode(LED_SENSOR_0, OUTPUT);
  pinMode(LED_SENSOR_1, OUTPUT);
  pinMode(LED_SENSOR_2, OUTPUT);
  pinMode(LED_SENSOR_3, OUTPUT);
  pinMode(LED_SENSOR_4, OUTPUT);

  Serial.begin(115200);
  startSession();
}

void loop() {
  delay(50); // 29ms should be the shortest delay between pings
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (active_sensor == i){
      checkContact(sonar[i].ping_cm(), i);
    }
  }
}

void startSession(){
  played_rounds = 1;
  startLedSensorStart();
  
  while (checkDist(sonar[2].ping_cm()) == false || checkDist(sonar[3].ping_cm()) == false){
  }

  startAllLeds();
  delay(1000);
  turnOffLeds();
  delay(1000);
  startAllLeds();
  delay(1000);
  turnOffLeds();
  delay(1000);
  startAllLeds();
  delay(1000);
  turnOffLeds();
  delay(1000);
  start_time = millis();
  startRandomLed();
}

void stopSession(){
  stop_time = millis();
  startAllLeds();
  delay(3000);

  Serial.println("******* RESULT *******");
  Serial.print("Total Time: ");
  Serial.print(stop_time - start_time);
  Serial.println(" ms");

  for (uint8_t i = 0; i < rounds; i++) {
    Serial.print("Round ");
    Serial.print(i + 1);
    Serial.print(" Time: ");
    Serial.print(times[i]);
    Serial.println(" ms");    
  }

  Serial.println("**********************");



  startSession();
}

bool checkDist(int dist){
  if (dist >= min_dist && dist <= max_dist){
    return true;
  }

  return false;
}
void checkContact(int dist, int sensor){
  if (checkDist(dist)){
    times[played_rounds - 1] = millis() - start_round_time;

    if (played_rounds == rounds){
      stopSession();
    }
    else {
      printDist(dist);
      turnOffLeds();
      delay(random(min_sleep, max_sleep));
      played_rounds = played_rounds + 1;
      startRandomLed();
    }    
  }
}

void startLedSensor0(){
  digitalWrite(LED_SENSOR_0, HIGH);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, LOW);
}

void startLedSensor1(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, HIGH);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, LOW);
}

void startLedSensor2(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, HIGH);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, LOW);
}

void startLedSensor3(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, HIGH);
  digitalWrite(LED_SENSOR_4, LOW);
}

void startLedSensor4(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, HIGH);
}

void startLedSensorStart(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, HIGH);
  digitalWrite(LED_SENSOR_3, HIGH);
  digitalWrite(LED_SENSOR_4, LOW);
}

void startAllLeds(){
  digitalWrite(LED_SENSOR_0, HIGH);
  digitalWrite(LED_SENSOR_1, HIGH);
  digitalWrite(LED_SENSOR_2, HIGH);
  digitalWrite(LED_SENSOR_3, HIGH);
  digitalWrite(LED_SENSOR_4, HIGH);
}

void startRandomLed(){
  while (next_sensor == active_sensor){
    next_sensor = random(SONAR_NUM);
  }
  
  Serial.print("Random number: ");
  Serial.println(next_sensor);
  if (next_sensor == 0){
      startLedSensor0();
    }
  else if (next_sensor == 1){
      startLedSensor1();
    }
  else if (next_sensor == 2){
      startLedSensor2();
    }
  else if (next_sensor == 3){
      startLedSensor3();
    }
  else if (next_sensor == 4){
      startLedSensor4();
    }
  active_sensor = next_sensor;
  start_round_time = millis();
  }

void turnOffLeds(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, LOW);

}

void printDist(int dist){
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");
}

// TODO:
// [] Add mean time
// [] Print which module connects to which time
// [] Look over random function. Start is simliar most of the times...
