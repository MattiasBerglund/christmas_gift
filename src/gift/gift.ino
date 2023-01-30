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

#define NR_OF_SENSOR  5

// User Settings
#define MAXIMUM_ROUNDS   10
#define MINIMUM_ROUNDS   10
#define MAXIMUM_DISTANCE 20    // cm 
#define MINIMUM_DISTANCE 2     // cm
#define MAXIMUM_OFF_TIME 0     // ms
#define MINIMUM_OFF_TIME 0     // ms
#define USE_MY_ORDER     false
int my_order[MAXIMUM_ROUNDS] = {1,5}; // Choose between sensor nr 1-5. e.g. {1,2,3,4,5,5,4,3,2,1} 

// Variables
int played_rounds = 1;
int active_sensor = 999;
int next_sensor = 999;
int start_time = 0;
int start_round_time = 0;
int times[MAXIMUM_ROUNDS];
int sensors[MAXIMUM_ROUNDS];
int rounds = 0;


NewPing sonar[NR_OF_SENSOR] = {
  NewPing(PIN_SENSOR_0, PIN_SENSOR_0, MAXIMUM_DISTANCE * 10), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(PIN_SENSOR_1, PIN_SENSOR_1, MAXIMUM_DISTANCE * 10), 
  NewPing(PIN_SENSOR_2, PIN_SENSOR_2, MAXIMUM_DISTANCE * 10), 
  NewPing(PIN_SENSOR_3, PIN_SENSOR_3, MAXIMUM_DISTANCE * 10), 
  NewPing(PIN_SENSOR_4, PIN_SENSOR_4, MAXIMUM_DISTANCE * 10), 
};

void setup() {
  pinMode(LED_SENSOR_0, OUTPUT);
  pinMode(LED_SENSOR_1, OUTPUT);
  pinMode(LED_SENSOR_2, OUTPUT);
  pinMode(LED_SENSOR_3, OUTPUT);
  pinMode(LED_SENSOR_4, OUTPUT);

  Serial.begin(115200);
  randomSeed(analogRead(A1));
  startSession();
}

void loop() {
  delay(50);
  for (uint8_t i = 0; i < NR_OF_SENSOR; i++) {
    if (active_sensor == i){
      checkContact(sonar[i].ping_cm(), i);
    }
  }
}

void checkContact(int dist, int sensor){
  if (checkDist(dist)){
    times[played_rounds - 1] = millis() - start_round_time;
    sensors[played_rounds - 1] = active_sensor + 1;

    if (played_rounds == rounds){
      stopSession();
    }
    else {
      turnOffLeds();
      delay(random(MINIMUM_OFF_TIME, MAXIMUM_OFF_TIME));
      played_rounds = played_rounds + 1;
      startNextLed();
    }    
  }
}

void startSession(){
  played_rounds = 1;
  rounds = random(MINIMUM_ROUNDS, MAXIMUM_ROUNDS + 1);
  Serial.print(rounds);
  startLedSensorStart();
  waitForStart();
  startLight();
  start_time = millis();
  startNextLed();
}

void waitForStart(){
  while (checkDist(sonar[2].ping_cm()) == false || checkDist(sonar[3].ping_cm()) == false){
  }
}

void startLight(){
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
}

void stopSession(){
  int total_time = millis() - start_time;
  startAllLeds();
  delay(3000);
  printResult(total_time);
  startSession();
}

bool checkDist(int dist){
  if (dist >= MINIMUM_DISTANCE && dist <= MAXIMUM_DISTANCE){
    return true;
  }

  return false;
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

void startNextLed(){
  if (USE_MY_ORDER){
      startNextInOrder();
    }
  else{
      startRandomLed();
    }
  active_sensor = next_sensor;
  start_round_time = millis();
}

void startRandomLed(){
  while (next_sensor == active_sensor){
    next_sensor = random(NR_OF_SENSOR);
  }
  startLedSensor(next_sensor);
}

void startNextInOrder(){
  next_sensor = my_order[played_rounds - 1] - 1;
  startLedSensor(next_sensor);
}

void startLedSensor(int led){
  if (led == 0){
      startLedSensor0();
  }
  else if (led == 1){
      startLedSensor1();
  }
  else if (led == 2){
      startLedSensor2();
  }
  else if (led == 3){
      startLedSensor3();
  }
  else if (led == 4){
      startLedSensor4();
  }
}

void turnOffLeds(){
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  digitalWrite(LED_SENSOR_2, LOW);
  digitalWrite(LED_SENSOR_3, LOW);
  digitalWrite(LED_SENSOR_4, LOW);
}

void printResult(int total_time){
  Serial.println("******* RESULT *******");
  printTotalTime(total_time);
  printMeanTime(total_time);
  printRoundTimes();
  Serial.println("**********************");
}

void printDist(int dist){
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");
}

void printRoundTimes(){
  for (uint8_t i = 0; i < rounds; i++) {
    Serial.print("Round ");
    Serial.print(i + 1);
    Serial.print(" Time: ");
    Serial.print(times[i]);
    Serial.print(" ms");
    Serial.print(" on sensor nr: ");
    Serial.println(sensors[i]);
  }
}

void printTotalTime(int total_time){
  Serial.print("Total Time: ");
  Serial.print(total_time);
  Serial.println(" ms");
}

void printMeanTime(int total_time){
  Serial.print("Mean Time: ");
  Serial.print(total_time / rounds);
  Serial.println(" ms");
}
