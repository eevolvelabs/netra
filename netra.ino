// Updates: Dhaval Malaviya
// Public Domain.


/* Eye for visually impaired

   This project uses PING))) sensor and arduino micro.
   Device measures the distance between the PING sensor and
   objects infront of it.
   Depending on the distance PWM value is sent to the vibtrating
   motor, or in detail, if distance between object and device
   decreases the PWM with 100 % duty cycle is applied to vibrating motor
   hence it vibrates most.
   Now as distance increases, duty cycle decreases resutling in reduction
   of the vibration of the motor.
      
 */

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(6,OUTPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  // Now based on the value of the distance regulate the 
  // the vibration of the motor by putting appropiate value of PWM.
  // Hence based on distance following vibration will be felt
  // a) if the distance is more than 100 cm then vibration will be less hence PWM value will be 30% duty cycle
  // b) if the distance is more than 30 cm but less than 100 cm then vibration will be more than 30% and it will be 70%
  // c) if the distance is less than 30 cm then vibration will be maximum and will be 100% duty cycle

  if(cm > 100)
  {
    analogWrite(6,10);
  }
  else if( cm < 100 && cm > 30 )
  {
    analogWrite(6,125);
  }
  else if(cm < 30)
  {
    analogWrite(6,255);
  }
  // Output PWM on pin 6 100% dutycycle
  //analogWrite(6,255);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
  //analogWrite(6,50);
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
