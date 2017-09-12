// ultrasonic sensor module HC-SR04-JX

// define pin numbers
const int trigPin = 2;
const int echoPin = 4;
// define vars
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // clear the trigPin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  
  // set the trigPin to HIGH for 10ms
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

 // read echoPin, returns the sound wave return time in ms
 duration = pulseIn(echoPin,HIGH);

 // calculate the distance
 distance = duration * 0.034/2;

}
