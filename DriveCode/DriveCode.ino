#include <ESP32Servo.h>
Servo myservo;

#define m1PWM 14  //PWM
#define m1Dir 25

#define m2PWM 27  //PWM
#define m2Dir 33

#define trigPin 13  // Ultrasonic Sensor
#define echoPin 34

#define servoPin 32   // Servo

long duration;
float distance;

int pos = 0;    // variable to store the servo position

float distArray[180];
int objectLeftAngle;
int objectRightAngle;

float thresh = 10.0;
int sweepAngle = 30;  // Angle to execute the sweep in
int speed = 100; 


void setup() {
  Serial.begin(115200);

  pinMode(m1PWM, OUTPUT);
  pinMode(m1Dir, OUTPUT);
  pinMode(m2PWM, OUTPUT);
  pinMode(m2Dir, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000); // attaches the servo

  stop();
  delay(1000);
}

void loop() {
  /*// Sweep right
  right();
  setSpeed(speed);
  for (int i = 0; i < sweepAngle; i++){
    distArray[i] = pulse();
    if (i>0){
      if (distArray[i-1] - thresh > distArray[i] && distArray[i] < 150){  // Rising Edge
        objectLeftAngle = i;
      }
      if (distArray[i-1] - thresh < distArray[i] && distArray[i-1] < 150){  // Falling Edge
        objectRightAngle = i-1;
      }
    }
    setSpeed(speed);
    delay(50);  // 50ms * sweepAngle = time for robot to 30deg angle
    stop();
  }
  stop();
  delay(1000);
  
  // Return to object location
  left();
  for (int i = 0; i < sweepAngle - ((objectLeftAngle - objectRightAngle)/2) + objectLeftAngle; i++){   // Return to the center object angle
    pulse();
    setSpeed(speed);
    delay(50);
    stop();
  }
  stop();
  delay(1000);

  // Drive forward until Cod
  forward();
  setSpeed(speed);
  while (pulse() > 5 ){
    //Do nothing
    delay(50);
  }

  stop();
  delay(1000);*/
  forward();
  delay(200);
  stop();


  // Lift repeatedly
  while (true){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	  }
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		  myservo.write(pos);    // tell servo to go to position in variable 'pos'
		  delay(15);             // waits 15ms for the servo to reach the position
	  }
  }
}

//============ FUNCTIONS =============

void setSpeed(int speed){
  // Speed is the PWM value between 0 and 255
  analogWrite(m1PWM, speed);
  analogWrite(m2PWM, speed);
}

void stop(){
  // Speed is the PWM value between 0 and 255
  analogWrite(m1PWM, 0);
  analogWrite(m2PWM, 0);
}

void forward(){
  digitalWrite(m1Dir, HIGH);
  digitalWrite(m2Dir, LOW);
  Serial.println("forward");
}

void backward(){
  digitalWrite(m1Dir, LOW);
  digitalWrite(m2Dir, HIGH);
  Serial.println("backward");
}

void left(){
  digitalWrite(m1Dir, HIGH);
  digitalWrite(m2Dir, HIGH);
  Serial.println("left");
}

void right(){
  digitalWrite(m1Dir, LOW);
  digitalWrite(m2Dir, LOW);
  Serial.println("right");
}

float pulse(){
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout of 30ms (30000us)

  // Calculate distance in centimeters (speed of sound = 343 m/s)
  distance = duration * 0.034 / 2; // 0.034 cm/us is the speed of sound in air
  
  // Check for out-of-range readings
  if (duration == 0) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }
  return 0;
}