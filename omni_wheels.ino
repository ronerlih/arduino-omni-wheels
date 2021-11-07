#define CUSTOM_SETTINGS

#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

// #include <SoftwareSerial.h>
// SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

int bluetoothData;
int isRunning = false;
int batteryMonitorPin = 18;
int dataIn = 0;
String Serialdata = "";
bool dataflag = 0;
bool recievedData = false;
class Motor
{
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
Motor::Motor(int ena, int in1, int in2)
{
   this->ena = ena;
   this->in1 = in1;
   this->in2 = in2;
}
void Motor::moveForward()
{
   digitalWrite(this->in1, LOW);
   digitalWrite(this->in2, HIGH);
};
void Motor::moveBackward()
{
   digitalWrite(this->in1, HIGH);
   digitalWrite(this->in2, LOW);
};
void Motor::setSpeed(int speed)
{
   analogWrite(this->ena, speed);
};
void Motor::stop()
{
   digitalWrite(this->in1, HIGH);
   digitalWrite(this->in2, HIGH);
};
void Motor::setup()
{
   pinMode(this->ena, OUTPUT);
   pinMode(this->in1, OUTPUT);
   pinMode(this->in2, OUTPUT);
   digitalWrite(this->in1, LOW);
   digitalWrite(this->in2, HIGH);
   this->setSpeed(0);
};

Motor bottomLeft(6, 5, 7);
Motor bottomRight(3, 2, 4);
Motor topRight(11, 13, 12);
Motor topLeft(9, 10, 8);

void setup()
{
   bottomLeft.setup();
   bottomRight.setup();
   topLeft.setup();
   topRight.setup();
   pinMode(13, OUTPUT);

   // battery monitor
   pinMode(batteryMonitorPin, OUTPUT);
   // Turn off motors - Initial state
   stopAll();

   // while (!Serial)
   // {
   //    ; // wait for serial port to connect. Needed for Native USB only
   // }

   Serial.begin(115200);
   Dabble.begin(9600, 0, 1);
   // Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
   // Bluetooth.println("Hello, world?");
}
void loop()

{

   recieveBluetooth();
   // monitorBattery();

   // if (isRunning)
   // {
   //    runRoutine();
   // }
}
void monitorBattery()
{
   //  // Monitor the battery voltage
   int sensorValue = analogRead(A0);
   float voltage = sensorValue * (5.0 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
   Serial.println(voltage);
   // If voltage is below 11V turn on the LED
   if (voltage < 3)
   {
      digitalWrite(batteryMonitorPin, LOW);
   }
   else
   {
      digitalWrite(batteryMonitorPin, HIGH);
   }
}

void recieveBluetooth()
{
   Dabble.processInput();
   while (Serial.available() != 0)
  {
    Serialdata = String(Serialdata + char(Serial.read()));
    dataflag = 1;
  }
  if (dataflag == 1)
  {
    Terminal.print(Serialdata);
    Serialdata = "";
    dataflag = 0;
  }
  if(Terminal.available())
  {
    while (Terminal.available() != 0)
    {
      Serial.println(Terminal.read());
    }
    Serial.println();
  }

   //   Terminal.println(Terminal.available());
   // dataIn = Terminal.read(); // Read the data
   // Terminal.println(1111);

   // if (dataIn != NULL && false)
   // {

   //    toggleRoutine();
   //    // if(dataIn == 1) {
   //    //    isRunning = true;
   //    // }

   //    // if(dataIn == 0) {
   //    //    isRunning = false;
   //    // }
   // }
}
void toggleRoutine()
{
   if (isRunning)
   {
      isRunning = false;
   }
   else
   {
      isRunning = true;
   }
}
void runRoutine()
{

   if (isRunning)
   {
      turnInPositionRight();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }

   recieveBluetooth();
   if (isRunning)
   {
      turnInPositionLeft();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }
   recieveBluetooth();
   if (isRunning)
   {

      right();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }
   recieveBluetooth();

   if (isRunning)
   {
      left();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }
   recieveBluetooth();

   if (isRunning)
   {

      turnRear();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }
   recieveBluetooth();

   if (isRunning)
   {

      turnBottomLeft();
      ascendDescendSpeed();
   }
   else
   {
      stopAll();
   }
}
void fullRoutine()
{
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

// control speed of the motors
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
void turnInPositionRight()
{
   topLeft.moveForward();
   topRight.moveBackward();
   bottomLeft.moveForward();
   bottomRight.moveBackward();
}
void turnInPositionLeft()
{
   topLeft.moveBackward();
   topRight.moveForward();
   bottomLeft.moveBackward();
   bottomRight.moveForward();
}
void turnRear()
{
   topLeft.moveForward();
   topRight.moveBackward();
   bottomLeft.stop();
   bottomRight.stop();
}
void turnBottomLeft()
{
   topLeft.moveForward();
   topRight.stop();
   bottomLeft.moveForward();
   bottomRight.stop();
}
void ascendDescendSpeed()
{
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
// control spinning direction of motors
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