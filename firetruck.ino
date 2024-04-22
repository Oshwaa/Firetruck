#include <Servo.h> // Include Servo library for servo motor control

// Define pins connected to L298N motor driver
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

// Flame sensors pin
#define LEFT_FS_PIN 6
#define FRONT_FS_PIN 7
#define RIGHT_FS_PIN 8

// Pump relay pin
#define PUMP_PIN 9

// Servo motor pin
#define SERVO_PIN 10

// Create a servo object
Servo myservo;
bool fire;

void setup() {
  // Set control pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Flame sensor Control
  pinMode(LEFT_FS_PIN, INPUT);
  pinMode(FRONT_FS_PIN, INPUT);
  pinMode(RIGHT_FS_PIN, INPUT);

  // Set pump relay pin as output
  pinMode(PUMP_PIN, OUTPUT);

  //HIGH IS ON - LOW IS OFF
  digitalWrite(PUMP_PIN, HIGH);  
  fire = false;
  myservo.attach(SERVO_PIN);
  sweep();
}

void loop() {
  //sweep();
  Extinguish();
  if (digitalRead(FRONT_FS_PIN) == LOW) {
    Stop();
    delay(500);
    if(fire){
      Forward();
    }
    delay(250);
    Stop();
    fire = true;
  } 
  else if (digitalRead(LEFT_FS_PIN) == LOW) {
    Left();
  }
  else if (digitalRead(RIGHT_FS_PIN) == LOW) {
    Right();
  }
  else if (digitalRead(FRONT_FS_PIN) == HIGH) {
    fire = false;   
  }
}

void Forward() {
  //left wheel
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //right wheel
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Adjust delay as needed
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Right() {
  // r wheel forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // l wheel backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Left() {
  // l wheel forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // r wheel backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void Extinguish() {
  if(fire){
    digitalWrite(PUMP_PIN, LOW);
    delay(1000);
    digitalWrite(PUMP_PIN, HIGH);
  }
  
}

void sweep(){
  for (int pos = 0; pos <= 130; pos += 1) {
      myservo.write(pos); 
    }
    for (int pos = 130; pos >= 0; pos -= 1) {
      myservo.write(pos);          
    }
}
