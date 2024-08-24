#include "DHT.h"  

#define DHTTYPE DHT11    
#define DHTPIN 13  

DHT dht(DHTPIN , DHTTYPE);  

int temp = 0, humid = 0;  
  
void setup() {    
  Serial.begin(115200);  
  dht.begin();  
}  
  
void loop() {  
  temp  = dht.readTemperature();  
  humid = dht.readHumidity();  
  
  Serial.print("temp="); Serial.print(temp);  
  Serial.print(",humid="); Serial.println(humid);     
  delay(1000);  
}  