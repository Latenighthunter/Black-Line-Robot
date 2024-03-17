#include <Arduino.h>

#define MOTOR_SPEED 60

int motor1 = 9;
int motor2 = 6;
int motor3 = 5;
int motor4 = 3;
int left = 13;
int right = 12;
int Left= 0;
int Right = 0;
// put function declarations here:
void T_left();
void T_right();
void stop();
void forward();

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  while (true)
  {
    Left = digitalRead(left);//Read left ir sensor
    Right = digitalRead(right);//Read right ir sensor
    // Checks if right ir sensor detect light and turns the car left
    if (Left==0&&Right==1)
    {
      T_left();
    }
    // Checks if left ir sensor detect light and turns the car right
    else if (Left==1&&Right==0)
    {
      T_right();
    }
    // Stops car if both sesors detect light
    if (Left==1&&Right==1)
    {
      stop();
    }
    
  }
  
}

// Move Motor Forward
void forward(){
  analogWrite(motor1, MOTOR_SPEED);
  analogWrite(motor2, 0);
  analogWrite(motor3, MOTOR_SPEED);
  analogWrite(motor4, 0);
}

// Turn Motor Left
void T_left(){
  analogWrite(motor3, 0);
  analogWrite(motor4, 30);
  while (Left == 0)//loops while right sensor does not detect light
  {
    Left = digitalRead(left);
    Right = digitalRead(right);
    if (Right == 0)
    {
      int lprev = Left;
      int rprev = Right;
      stop();
      while ((lprev==Left)&&(rprev==Right))
      {
        Left = digitalRead(left);
        Right = digitalRead(right);
      }
      
    }
    analogWrite(motor1, MOTOR_SPEED);
    analogWrite(motor2, 0);
  }
  analogWrite(motor3, MOTOR_SPEED);
  analogWrite(motor4, 0);
}

// Turn Motor Right
void T_right(){
  analogWrite(motor1, 0);
  analogWrite(motor2, 30);
  while (Right ==0)
  {
    Left = digitalRead(left);
    Right = digitalRead(right);
    if (Left == 0)
    {
      int lprev = Left;
      int rprev = Right;
      stop();
      while ((lprev==Left)&&(rprev==Right))
      {
        Left = digitalRead(left);
        Right = digitalRead(right);
      }
      
    }
    analogWrite(motor3, MOTOR_SPEED);
    analogWrite(motor4, 0);
  }
  analogWrite(motor1, MOTOR_SPEED);
  analogWrite(motor2, 0);
}

// Stop Motor
void stop(){
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
  analogWrite(motor3, 0);
  analogWrite(motor4, 0);
}