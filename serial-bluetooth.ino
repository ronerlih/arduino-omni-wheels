#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(0, 10); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

int bluetoothData;

class Motor {
  private:
    int ena;
    int in1;
    int in2;
  public:
    Motor(int ena, int in1, int in2);
    void setup();
    void moveForward();
    void moveBackward();
    void setSpeed(int speed);
    void stop();
};
Motor::Motor(int ena, int in1, int in2) {
  this->ena = ena;
  this->in1 = in1;
  this->in2 = in2;

}
void Motor::moveForward() {
  digitalWrite(this->in1, LOW);
  digitalWrite(this->in2, HIGH);
};
void Motor::moveBackward() {
  digitalWrite(this->in1, HIGH);
  digitalWrite(this->in2, LOW);
};
void Motor::setSpeed(int speed) {
  analogWrite(this->ena, speed);
};
void Motor::stop() {
  digitalWrite(this->in1, HIGH);
  digitalWrite(this->in2, HIGH);
};
void Motor::setup() {
  pinMode(this->ena, OUTPUT);
  pinMode(this->in1, OUTPUT);
  pinMode(this->in2, OUTPUT);
  digitalWrite(this->in1, LOW);
  digitalWrite(this->in2, HIGH);
  this->setSpeed(100);
};

Motor bottomLeft(6, 5, 7);
Motor bottomRight(3, 2, 4);
Motor topRight(11, 13, 12);
Motor topLeft(9, 10, 8);

void setup()
{
  pinMode(13, OUTPUT); // debugging led pin

  bottomLeft.setup();
  bottomRight.setup();
  topLeft.setup();
  topRight.setup();

// no softwareSerial lib  
//  Serial.begin(9600);

  Serial.begin(9600);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  
  // Turn off motors - Initial state
  stopAll();
}
void recieveBluetooth() {
   if (Bluetooth.available() > 0) {
    int dataIn = Bluetooth.read();  // Read the data
    if (dataIn == 0) {
      bluetoothData = 0;
    }
    if (dataIn == 1) {
      bluetoothData = 1;
    }
    if (dataIn == 2) {
      bluetoothData = 2;
    }
    if (dataIn == 3) {
      bluetoothData = 3;
    }
    if (dataIn == 4) {
      bluetoothData = 4;
    }
    if (dataIn == 5) {
      bluetoothData = 5;
    }
    if (dataIn == 6) {
      bluetoothData = 6;
    }
    if (dataIn == 7) {
      bluetoothData = 7;
    }
    if (dataIn == 8) {
      bluetoothData = 8;
    }
    if (dataIn == 9) {
      bluetoothData = 9;
    }
    if (dataIn == 10) {
      bluetoothData = 10;
    }
    if (dataIn == 11) {
      bluetoothData = 11;
    }
    if (dataIn == 12) {
      bluetoothData = 12;
    }
    if (dataIn == 14) {
      bluetoothData = 14;
    }
    // Set speed
    if (dataIn >= 16) {
      setCarSpeed(dataIn * 10);
    }
 
  if (bluetoothData == 4) {
    left();
  }
  if (bluetoothData == 5) {
    right();
  }
  if (bluetoothData == 2) {
    forward();
  }
  if (bluetoothData == 7) {
    backward();
  }
  if (bluetoothData == 3) {
    diagonalRight();
  }
  if (bluetoothData == 1) {
    prototypeRoutine();
//    moveLeftForward();
  }
  if (bluetoothData == 8) {
//    moveRightBackward();
  }
  if (bluetoothData == 6) {
//    moveLeftBackward();
  }
  if (bluetoothData == 9) {
    turnInPositionLeft();
  }
  if (bluetoothData == 10) {
    turnInPositionRight();
  }
  if (bluetoothData == 0) {
    stopCar();
  }
  Bluetooth.println(dataIn);
  // If button "SAVE" is pressed
  if (bluetoothData == 12) {
//    if (index == 0) {
//      LeftBackWheel.setCurrentPosition(0);
//      LeftFrontWheel.setCurrentPosition(0);
//      RightBackWheel.setCurrentPosition(0);
//      RightFrontWheel.setCurrentPosition(0);
//    }
//    lbw[index] = LeftBackWheel.currentPosition();  // save position into the array
//    lfw[index] = LeftFrontWheel.currentPosition();
//    rbw[index] = RightBackWheel.currentPosition();
//    rfw[index] = RightFrontWheel.currentPosition();
//    index++;                        // Increase the array index
//    bluetoothData = 0;
  }
  if (bluetoothData == 11) {
    prototypeRoutine();
    
  }
  
//  // Monitor the battery voltage
//  int sensorValue = analogRead(A0);
//  float voltage = sensorValue * (5.0 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
//  //Serial.println(voltage);
//  // If voltage is below 11V turn on the LED
//  if (voltage < 11) {
//    digitalWrite(led, HIGH);
//  }
//  else {
//    digitalWrite(led, LOW);
//  }
}
}
void stopCar(){
  bottomLeft.stop();
  bottomRight.stop();
  topLeft.stop();
  topRight.stop();
}
void setCarSpeed(int speed){
  bottomLeft.setSpeed(speed);
  bottomRight.setSpeed(speed);
  topLeft.setSpeed(speed);
  topRight.setSpeed(speed);
}
void loop(){
  recieveBluetooth();
// forward();
// ascendDescendSpeed();

//prototypeRoutine();
}
void prototypeRoutine(){
//  nice routine
 turnInPositionRight();
 ascendDescendSpeed();
  turnInPositionLeft();

  ascendDescendSpeed();

 right();
  ascendDescendSpeed();

 left();
  ascendDescendSpeed();

  turnRear();
 ascendDescendSpeed();
 turnBottomLeft();
 ascendDescendSpeed();
}
void fullRoutine(){
   forward();
  ascendDescendSpeed();
  backward();
  ascendDescendSpeed();
  right();
  ascendDescendSpeed();
  left();
  ascendDescendSpeed();
  
  turnInPositionLeft();
  ascendDescendSpeed();
  turnRear();
  ascendDescendSpeed();
  turnBottomLeft();
  ascendDescendSpeed();
  diagonalRight();
  ascendDescendSpeed();
  diagonalLeft();
  ascendDescendSpeed();
}
void stopAll()
{
  bottomLeft.stop();
  bottomRight.stop();
  topLeft.stop();
//  topLeft.stop();
}
//
//void zeroSpeed()
//{
//   digitalWrite(bottomLeftEN, 0);
//   digitalWrite(bottomRightEN, 0);
//   digitalWrite(topLeftEN, 0);
//   digitalWrite(topRightEN, 0);
//}



// This function lets you control speed of the motors
void forward()
{
  bottomLeft.moveForward();
  bottomRight.moveForward();
  topLeft.moveForward();
  topRight.moveForward();
}
void backward()
{
  bottomLeft.moveBackward();
  bottomRight.moveBackward();
  topLeft.moveBackward();
  topRight.moveBackward();
}
void right()
{
  bottomLeft.moveBackward();
  bottomRight.moveForward();
  topLeft.moveForward();
  topRight.moveBackward();
}
void left()
{
  bottomLeft.moveForward();
  bottomRight.moveBackward();
  topLeft.moveBackward();
  topRight.moveForward();
}

void diagonalRight()
{
  
  topLeft.moveForward();
  topRight.stop();
  bottomLeft.stop();
  bottomRight.moveForward();
}
void diagonalLeft()
{
  
  topLeft.stop();
  topRight.moveForward();
  bottomLeft.moveForward();
  bottomRight.stop();
}
void turnInPositionRight(){
  topLeft.moveForward();
  topRight.moveBackward();
  bottomLeft.moveForward();
  bottomRight.moveBackward();
}
void turnInPositionLeft(){
  topLeft.moveBackward();
  topRight.moveForward();
  bottomLeft.moveBackward();
  bottomRight.moveForward();
}
void turnRear(){
  topLeft.moveForward();
  topRight.moveBackward();
  bottomLeft.stop();
  bottomRight.stop();
}
void turnBottomLeft() {
  topLeft.moveForward();
  topRight.stop();
  bottomLeft.moveForward();
  bottomRight.stop();
}
void ascendDescendSpeed(){
   // Accelerate from zero to maximum speed
   for (int i = 0; i < 110; i++)
  {
    bottomLeft.setSpeed(i);
    bottomRight.setSpeed(i);
    topLeft.setSpeed(i);
    topRight.setSpeed(i);
    delay(30);
  }
      delay(3000);

 for (int i = 110; i > 0; i--)

  {
    bottomLeft.setSpeed(i);
    bottomRight.setSpeed(i);
    topLeft.setSpeed(i);
    topRight.setSpeed(i);
    delay(30);
  }
  
}
// This function lets you control spinning direction of motors
void directionControl()
{
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  //   analogWrite(enA, 255);
  //   analogWrite(enB, 255);
  //
  //   // Turn on motor A & B
  //   digitalWrite(in1, HIGH);
  //   digitalWrite(in2, LOW);
  //   digitalWrite(in3, HIGH);
  //   digitalWrite(in4, LOW);
  //   delay(2000);
  //
  //   // Now change motor directions
  //   digitalWrite(in1, LOW);
  //   digitalWrite(in2, HIGH);
  //   digitalWrite(in3, LOW);
  //   digitalWrite(in4, HIGH);
  //   delay(2000);
  //
  //   // Turn off motors
     stopAll();
}