volatile int flow_frequency; // Measures flow sensor pulses
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
int flow_counter=0;
int valve_close=5;
const int resetbuttonPin = 7;
const int resetPin =  9;
int buttonState = 0; 
void flow () // Interrupt function
{
   flow_frequency++;
}



void setup() {
  // put your setup code here, to run once:
pinMode(valve_close, OUTPUT);
pinMode(flowsensor, INPUT);
pinMode(resetbuttonPin, INPUT);
pinMode(resetPin, OUTPUT);
   digitalWrite(flowsensor, HIGH);
   Serial.begin(9600);

   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  currentTime = millis();
   cloopTime = currentTime;
   
}

void loop() {
  buttonState = digitalRead(resetbuttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // open the valve:
    digitalWrite(resetPin, HIGH);
    delay(6000) ;
      digitalWrite(resetPin, LOW);  }
  
currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
     
       flow_counter++; //increase counter every second
       flow_frequency = 0;
      Serial.print(flow_counter);
      if (flow_counter>20){Serial.print("Water Leakage");
      digitalWrite(valve_close, HIGH);
      delay(6000) ;
      digitalWrite(valve_close, LOW);      
      }
    }
    else {
        flow_counter = 0; // Reset Counter
        Serial.print(flow_counter);
     }
     
     }
}
