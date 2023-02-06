volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
 float vol = 0.0,l_minute;
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
int flow_counter=0;
int valve;

void flow () // Interrupt function
{
   flow_frequency++;
}



void setup() {
  // put your setup code here, to run once:
pinMode(flowsensor, INPUT);
pinMode(valve, OUTPUT);
   digitalWrite(flowsensor, HIGH); 
   digitalWrite(valve, LOW);
   Serial.begin(9600);

   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  currentTime = millis();
   cloopTime = currentTime;
   
}

void loop() {
  // put your main code here, to run repeatedly:
currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      
       flow_counter++; //increase counter every second
       flow_frequency = 0;
      Serial.print(flow_counter);
      if (flow_counter>20)
      {
       digitalWrite(valve, HIGH); }
      }
    }
    else {
        flow_counter = 0; // Reset Counter
        Serial.print(flow_counter);
     }
     
     }
