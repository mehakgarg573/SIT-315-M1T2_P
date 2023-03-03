//Adding interrupts to ultrasonic sensor connected to Piezo buzzer
const int TRIG = 6; // Arduino pin connected to Sensor's TRIG pin
const int ECHO = 3;   // Arduino pin connected to Sensor's ECHO pin
const int BUZZER = 13;  // Arduino pin connected to Piezo Buzzer's pin
const int   DISTANCE_THRESHOLD = 50; //centimeters
static unsigned long startTime = 0;
static unsigned long endTime = 0;

void setup() {
  Serial.begin(9600);  // initializing serial port
  pinMode(TRIG, OUTPUT); // sets arduino pin to output mode
  pinMode(ECHO, INPUT);  // sets arduino pin to input mode
  pinMode(BUZZER, OUTPUT);   // sets arduino pin to output mode
  
  attachInterrupt(digitalPinToInterrupt(ECHO), ISR_Ultrasonic, CHANGE);  //adding interrupt via echo pin
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // generating a 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long pulseDuration = pulseIn(ECHO, HIGH);

  int dist = pulseDuration / 58;   // calculates the distance

  Serial.print("dist: ");
  Serial.print(dist);
  Serial.println(" cm");

  delay(100);
}

// Function to generate interrupts
void ISR_Ultrasonic() {
  int echo = digitalRead(ECHO);
  if(echo == HIGH){
  	startTime = micros();
  }else{
    endTime = micros();
  	long duration = endTime - startTime;
    int dist = duration/58;
    if(dist < DISTANCE_THRESHOLD)
    {
      Serial.println("Ultrasonic Interrupt genrated!");
   	  digitalWrite(BUZZER,HIGH);  // turn on buzzer
      delay(500);
      digitalWrite(BUZZER,LOW);   // turn off buzzer
      delay(500);
    }
  }
  
}