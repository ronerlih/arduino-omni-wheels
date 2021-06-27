
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
  digitalWrite(this->in1, HIGH);
  digitalWrite(this->in2, LOW);
};
void Motor::moveBackward() {
  digitalWrite(this->in1, LOW);
  digitalWrite(this->in2, HIGH);
};
void Motor::setSpeed(int speed) {
  analogWrite(this->ena, speed);
};
void Motor::stop() {
  digitalWrite(this->in1, LOW);
  digitalWrite(this->in2, LOW);
};
void Motor::setup() {
  pinMode(this->ena, OUTPUT);
  pinMode(this->in1, OUTPUT);
  pinMode(this->in2, OUTPUT);
};

Motor bottomLeft(6, 5, 7);
Motor bottomRight(3, 2, 4);
Motor topLeft(11, 13, 12);
Motor topRight(9, 10, 8);

void setup()
{
  bottomLeft.setup();
  bottomRight.setup();
  topLeft.setup();
  topRight.setup();

  // Turn off motors - Initial state
  stopAll();
}
void loop()
{
  // directionControl();
  // delay(10000);
  speedControl();
  delay(10000);
}
void stopAll()
{
  bottomLeft.stop();
  bottomRight.stop();
  topLeft.stop();
  topLeft.stop();
}
//
//void zeroSpeed()
//{
//   digitalWrite(bottomLeftEN, 0);
//   digitalWrite(bottomRightEN, 0);
//   digitalWrite(topLeftEN, 0);
//   digitalWrite(topRightEN, 0);
//}

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
  //   stopAll()
}

// This function lets you control speed of the motors
void speedControl()
{
  // Turn on motors
  bottomLeft.moveForward();
  bottomRight.moveForward();
  topLeft.moveForward();
  topRight.moveForward();

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    bottomLeft.setSpeed(i);
    bottomRight.setSpeed(i);
    topLeft.setSpeed(i);
    topRight.setSpeed(i);
    delay(30);
  }

  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    bottomLeft.setSpeed(i);
    bottomRight.setSpeed(i);
    topLeft.setSpeed(i);
    topRight.setSpeed(i);
    delay(30);
  }

  // Now turn off motors
  stopAll();
}