
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

void setup(){
   pinMode(analogInput, INPUT);
 //  Serial.begin(9600);
   pinMode(13, OUTPUT);
}
void loop(){
  delay(500);
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = (vout / (R2/(R1+R2))) ;//- (vout / (R2/(R1+R2)) * 0.08555); 

  //  Serial.print("INPUT V= ");
  // Serial.println(vin);
    if (vin < CUTOFF){
        digitalWrite(13, HIGH);
        for(int i = 0; i< TIME; i++){
          delay(1000);
        }
    }else if (vin > HIGHCUTOFF){
        digitalWrite(13, LOW);
    }
}
