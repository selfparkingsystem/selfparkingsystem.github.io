/*self car parking system
Guided By : -Dr.Vishal Rathod
Priyanka Arora
Madhusudhan Amudula
Nikhil Yadav
Himanshu Raipure
Suryansh Dhakare */

const int up = 7;                 // connect to IN3
const int down = 6;               // connect to IN4
const int forwards = 4;           // connect to IN2
const int backwards = 3;          // connect to IN1
int IRSensor = 2, statusSensor2;  // 2st floor for slot1
int IRSensor2 = 10, statusSensor; // 3rd floor for slot2
int IRSensor3 = 9, statusSensor3; // 1st floor for vechile dectection
const int trigger = 8;
const int echo = 9;
long T;
float distanceCM;
String input;

void setup()
{
  pinMode(up, OUTPUT);        // set relay as an output
  pinMode(down, OUTPUT);      // set relay as an output
  pinMode(forwards, OUTPUT);  // set relay as an output
  pinMode(backwards, OUTPUT); // set relay as an output
  pinMode(IRSensor, INPUT);
  pinMode(IRSensor2, INPUT);
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{
  // dummyup();
  // dummydown();
  // delay(10000);
  // ultrasonic();
  parking();
  delay(1000);
  // unparking();
  // exit(0);
}

void parking()
{
  if (irs_3() == 1)
  {
    UG_0();

    if (irs_1() == 0)
    {
      UG_1();
      delay(1000);
    }
    else if (irs_2() == 0)
    {
      UG_2();
      delay(1000);
    }
    else
    {
      Serial.println("parking lot is full\n");
    }
  }
}

// implement ultra sonic functions in UG functions
void UG_2()
{
  motor1_for2slot(); // vertical down for 2nd slot
  delay(1000);

  motor2_rev(); // horizontal forward
  delay(1000);
  verticaldownP(); // vertical down for 1second
  delay(1000);

  motor2_for(); // horizontal backward
  delay(1000);

  motor1_rev2slot(); // vertical Up for starting position 30 seconds
  delay(1000);
}

void UG_1()
{
  motor1_for(); // vertical down to slot 1
  delay(1000);
  motor2_rev(); // horizontal forward
  delay(1000);
  verticaldownP(); // vertical down for 1second delay
  delay(1000);
  motor2_for(); // horizontal backward
  delay(1000);
  motor1_rev(); // vertical Up for starting position
  delay(1000);
}

void UG_0()
{
  motor2_rev(); // horizontal forward
  delay(1000);
  verticalupP(); // vertical up for 1second
  delay(1000);
  motor2_for(); // horizontal backward
  delay(1000);
}

void motor1_for()
{
  digitalWrite(up, LOW);
  digitalWrite(down, HIGH); // Activate the relay one direction, they must be different to move the motor
  delay(14000);             // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void motor1_rev()
{
  digitalWrite(up, HIGH);
  digitalWrite(down, LOW); // Activate the relay the other direction, they must be different to move the motor
  delay(15000);            // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void motor2_for()
{
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH); // Activate the relay one direction, they must be different to move the motor
  delay(200);                    // wait 2 seconds
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, HIGH); // Deactivate both relays to brake the motor
  delay(200);                    // wait 2 seconds
}

void motor2_rev()
{
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, LOW); // Activate the relay the other direction, they must be different to move the motor
  delay(200);                   // wait 2 seconds
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, HIGH); // Deactivate both relays to brake the motor
  delay(200);                    // wait 2 seconds
}

void ultrasonic()
{
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH); // In order to generate the ultrasound we need to set the Trigger Pin on a High State for 10 µs. That will send out an 8 cycle sonic burst which will travel at the speed sound and it will be received in the Echo Pin. The Echo Pin will output the time in microseconds the sound wave traveled.
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  delay(1000);
}

int irs_1()
{
  statusSensor = digitalRead(IRSensor);
  if (statusSensor == 1)
  {
    Serial.print("irs1 non-empty slot\n"); // no obstacle detected
    return 1;
  }
  else
  {
    Serial.print("irs1 empty slot\n"); // no obstacle detected
    return 0;
  }
}

int irs_2()
{
  statusSensor2 = digitalRead(IRSensor2);
  if (statusSensor2 == 1)
  {
    Serial.print("irs2 non-empty slot\n"); // no obstacle detected
    return 1;
  }
  else
  {
    Serial.print("irs2 empty slot\n"); // no obstacle detected
    return 0;
  }
}

int irs_3()
{
  statusSensor3 = digitalRead(IRSensor3);
  if (statusSensor3 == 1)
  {
    Serial.print("vechicle is detected\n"); //  obstacle detected
    return 1;
  }
  else
  {
    Serial.print("vechicle is not detected\n"); // no obstacle detected
    return 0;
  }
}
void verticaldownP()
{
  digitalWrite(up, LOW);
  digitalWrite(down, HIGH); // Activate the relay one direction, they must be different to move the motor
  delay(1000);              // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void verticalupP()
{
  digitalWrite(up, HIGH);
  digitalWrite(down, LOW); // Activate the relay one direction, they must be different to move the motor
  delay(1000);             // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void motor1_for2slot()
{
  digitalWrite(up, LOW);
  digitalWrite(down, HIGH); // Activate the relay one direction, they must be different to move the motor
  delay(29000);             // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void motor1_rev2slot()
{
  digitalWrite(up, HIGH);
  digitalWrite(down, LOW); // Activate the relay the other direction, they must be different to move the motor
  delay(30000);            // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}

void dummyup()
{
  digitalWrite(up, HIGH);
  digitalWrite(down, LOW); // Activate the relay the other direction, they must be different to move the motor
  delay(50000);            // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(20000);             // wait 2 seconds
}

void dummydown()
{
  digitalWrite(up, LOW);
  digitalWrite(down, HIGH); // Activate the relay one direction, they must be different to move the motor
  delay(50000);             // wait 2 seconds
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH); // Deactivate both relays to brake the motor
  delay(1000);              // wait 2 seconds
}
