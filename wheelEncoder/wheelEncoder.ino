// wheel encoder for dfrobot mobile platform
// connection for Arduino Uno
// left wheel encoder -> digital pin 2
// right wheel encoder -> digital pin 3
#define LEFT 0
#define RIGHT 1

long encoder[2]={0,0};
int prevSpeed[2]={0,0};

void setup() {
  // For Arduino Uno, interrupt number 0 = pin 2, interrupt number 1 = pin 3
  
  Serial.begin(9600); // init serial port to print data
  attachInterrupt(LEFT, encodeLeftWheel,CHANGE); // init interrupt mode for digital pin 2
  attachInterrupt(RIGHT, encodeRightWheel, CHANGE); // init interrupt mode for digital pin 3
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long timer =0; // print manager timer

  if(millis() - timer > 500){
    Serial.print("Coder value: ");
    Serial.print(encoder[LEFT]);
    Serial.print("[Left Wheel] ");
    Serial.print(encoder[RIGHT]);
    Serial.println("[Right Wheel]");
    Serial.println(" ");

    prevSpeed[LEFT] = encoder[LEFT]; // record the latest speed value
    prevSpeed[RIGHT] = encoder[RIGHT];
    encoder[LEFT]=0; // clear the data buffer
    encoder[RIGHT]=0;
    timer=millis();
  }
}

void encodeLeftWheel(){
  encoder[LEFT]++; // count the left wheel encoder interrupts
}

void encodeRightWheel(){
  encoder[RIGHT]++; // count the right wheel encoder interrupts
}

