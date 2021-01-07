int analogInput = 0;
int pin = 13;
float vout = 0.0;
float vin = 0.0;
float R1 = 99100.0; // R1 (100K)
float R2 = 9800.0; // R2 (10K)
const float CUTOFF = 12.0; //12.1
const float HIGHCUTOFF = 12.1; //12.8
int value = 0;
const int TIME = 3600; //secs
void buttonPressed();
volatile int output = LOW; 

void setup(){
   pinMode(analogInput, INPUT);
   attachInterrupt(digitalPinToInterrupt(2),buttonPressed,RISING);
  Serial.begin(9600);
   pinMode(13, OUTPUT);
}


void buttonPressed()           //ISR function excutes when push button at pinD2 is pressed
{   
  static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 1000)
 {
   output = !output;                //Change Output value to LOW                                
  Serial.println("pressed");
 }
 last_interrupt_time = interrupt_time;                 
   
}
void loop(){
  delay(500);
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = (vout / (R2/(R1+R2)));//- (vout / (R2/(R1+R2)) * 0.08555); 

    Serial.print("INPUT V= ");
   Serial.println(vin);
   volatile int check = output;
    if (vin < CUTOFF || output == HIGH){
        digitalWrite(13, HIGH);
        for(int i = 0; i< TIME; i++){
          if(output == LOW && check == HIGH || output == HIGH && check == LOW){
            break;
          }
          delay(1000);
        }
        output = LOW;
        digitalWrite(13, LOW);
    }else if (vin > HIGHCUTOFF){
        digitalWrite(13, LOW);
        output = LOW;
    }
}
