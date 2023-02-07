int duration;  //this is the time it takes for the ultrasonic distance sensor to return an echo
float distance; //this is the distance of the obstacle calculated from the duration it took for the ultrasonic wave to travel and return as echo
int waittime = 0; // this is the required delay time between on and off state, calculated from the distance of obstacle
int starttime; // this is the time when we start counting down to our waittime
int countdown = 0; // this is the time reached so far, we need it to climb from starttime to starttime+waittime before we change the state of the light
int pinstate = 0; // this is the state of the light, 1 means ON, 0 means OFF

# include <Servo.h>

Servo myservo;
const int servopin = 9;

void setup() {
  myservo.attach(servopin);
  pinMode(13, OUTPUT); // LED was connected to pin 13, so this means pin 13 is an output pin
  pinMode(7, OUTPUT); // Buzzer was conected to pin 7, so this means pin 7 is an output pin
  pinMode(4, OUTPUT);// TRIGGER of the ultrasonic sensor was connected to pin 4, so this means pin 4 is an output pin
  pinMode(6, INPUT); //ECHO of the ultrasonic sensor was connected to pin 6, so this means pin 6 is an input pin
  Serial.begin(9600); // this way, we setup our arduino to activate serial monitor (viewing information on the monitor)
}

void loop() {

  digitalWrite(4, HIGH); //this means we send a 5V out through pin 4, goin to the TRIG of the ultrasonic sensor, this sends out the sound wave
  delayMicroseconds(1000);//this means we wait for 1 second, the arduino will just wait and do nothing else while the previous code is still running
  digitalWrite(4, LOW);//this means we send a 0V out through pin 4, goin to the TRIG of the ultrasonic sensor, this stops the sound wave
  duration = pulseIn(6, HIGH);//this returns the time in miliseconds that arduino now has to wait before pin 6 (the ECHO pin) receives a HIGH
  distance = 0.017 * duration; // this converts the duration to distance using the formular distance = speed of sound * time


  if (distance > 15) {     //if the obstacle is more than 50 cm away from the sensor, then do what??
    //off the LED and buzzer
    digitalWrite(13, LOW);       //this sens a 0V to the LED
    digitalWrite(7, LOW);         //this sens a 0V to the buzzer
    starttime = millis();         //this resets the starttime to the time RIGHT NOW, in milliseconds
    pinstate = 99;                 //this gives the pinstate a value of 99, which we have chosen as a way of indicating that we are yet to start flickering the state from on to off to on to off

} 
  else {                             //OTHERWISE, i
    
  
    //on and off the LED and buzzer
    waittime = distance * 100;           //first, we calculate the time we need to give between when we ON out led, OFF and ON again.
    countdown = millis() - starttime;   //then we check how much time has elapsed since the last time we reset our starttime,
    myservo.write(180);  
    delay(1000);
    myservo.write(0);
    delay(1000);                                 //to know whether we need to change the state of our light and buzzer and then reset our starttime again

   if (countdown < waittime) {      //if the countdown time has not reached the required time we need to wait before changing the state of the led and buzzer, then do what??
      //do not change anything. However if this is the first time distance is less than 50cm in a long while, then turn on the led and buzzer
      if (pinstate == 99) {                //so we say, if pinstate is 99,
        digitalWrite(13, HIGH);       //then turn on the led
        digitalWrite(7, HIGH);        //and turn on the buzzer
        pinstate = 1;              //now change the pinstate to 1, so we dont assume it is still 99, 1 means the led and buzzer are now ON
      }
} 
    else {                        //if the countdown time has now climbed up to the waittime, then its time to do what?
      //change on to off and vice versa
      if (pinstate == 0) {
        digitalWrite(13, HIGH);
        digitalWrite(7, HIGH);
        pinstate = 1;
      } else {
        digitalWrite(13, LOW);
        digitalWrite(7, LOW);
        pinstate = 0;
      }

      //and reset the starttime to present time
      starttime = millis();
    }
  }
  Serial.print("Distance: ");   //print on to the monitor,the exact word "Distance: "
  Serial.print(distance);        // print on to the monitor,the value of the distance calculated earlier
  Serial.print("    PIN STATE: ");    //print on to the monitor,the exact words "PIN STATE: "
  Serial.println(pinstate);             // print on to the monitor,the current value of pinstate, which is either 99, 1 or 0
}
