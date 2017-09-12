// wheel encoder for dfrobot mobile platform

// connection for Arduino Uno
// left wheel encoder -> digital pin 2
// right wheel encoder -> digital pin 4

#define LEFT 0
#define RIGHT 1

long coder[2]={0,0};
int lastSpeed[2]={0,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // init serial port to print data
  attachInterrupt(LEFT, LwheelSpeed,CHANGE); // init interrupt mode for digital pin 2
  attachInterrupt(RIGHT, RwheelSpeed, CHANGE); // init interrupt mode for digital pin 4
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long timer =0; // print manager timer

  if(millis() - timer > 500){
    Serial.print("Coder value: ");
    Serial.print(coder[LEFT]);
    Serial.print("[Left Wheel] ");
    Serial.print(coder[RIGHT]);
    Serial.println("[Right Wheel]");
    Serial.println(" ");

    lastSpeed[LEFT] = coder[LEFT]; // record the latest speed value
    lastSpeed[RIGHT] = coder[RIGHT];
    coder[LEFT]=0; // clear the data buffer
    coder[RIGHT]=0;
    timer=millis();
  }
}

void LwheelSpeed(){
  coder[LEFT]++; // count the left wheel encoder interrupts
}

void RwheelSpeed(){
  coder[RIGHT]++; // count the right wheel encoder interrupts
}

