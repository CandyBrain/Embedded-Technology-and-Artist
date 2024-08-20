/*
* --------------------------------------------------------------------
* 
* ESP32 RTC 시간 디스플레이 Example Code
*
* Date: 2024.08.21 (last update 2024.08.21)
* Author: Dongwook Shin
* Company: CandyBrain
* 
* https://github.com/CandyBrain/Embedded-Technology-and-Artist
*
* --------------------------------------------------------------------
*/

#include <RTClib.h>             // RTC


RTC_DS3231 rtc;  // RTC 객체 생성
unsigned long lastDisplayTime = 0;


void setup() {
  // [System] Serial Initialization ----------------------------------------------------------
  Serial.begin(115200);
  while (!Serial)
    ;
  // -----------------------------------------------------------------------------------------

  // [RTC] Initialization --------------------------------------------------------------------
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // 컴파일된 시간으로 설정
  }
  // -----------------------------------------------------------------------------------------  
}



void displayTime() {
  DateTime now = rtc.now();

  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void loop() {
  if (millis() - lastDisplayTime >= 1000) { // 1초마다 실행
    lastDisplayTime = millis();
    displayTime();  // 시간 출력
  }
}
