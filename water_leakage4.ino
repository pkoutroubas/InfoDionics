  volatile int flow_frequency; // Measures flow sensor pulses
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
int flow_counter=0;
int valve_close=9;
const int resetbuttonPin = 7;
const int resetPin =  5;
int resetbuttonState = 0; 
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
  resetbuttonState = digitalRead(resetbuttonPin);
 digitalWrite(valve_close, HIGH);// THE VALVE RELAY HAS NEGATIVE LOGIC
  digitalWrite(resetPin, LOW); 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (resetbuttonState == HIGH) {
    // open the valve:
    digitalWrite(resetPin, HIGH);
     digitalWrite(valve_close, HIGH);// THE VALVE RELAY HAS NEGATIVE LOGIC
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
      if (flow_counter >   20){
        Serial.print("Water Leakage");
      digitalWrite(valve_close, LOW  );// THE VALVE RELAY HAS NEGATIVE LOGIC
       digitalWrite(resetPin, LOW);
      delay(6000) ;
      digitalWrite(valve_close, LOW);      
      }
    }
    else {
        flow_counter = 0; // Reset Counter
              digitalWrite(valve_close, LOW);     
        Serial.print(flow_counter);
        Serial.print(valve_close);
     }
     
     }
}
