/*
* --------------------------------------------------------------------
* 
* ESP32 WiFi 접속 Example Code
*
* Date: 2024.08.21 (last update 2024.08.21)
* Author: Dongwook Shin
* Company: CandyBrain
* 
* https://github.com/CandyBrain/Embedded-Technology-and-Artist
*
* --------------------------------------------------------------------
*/

#include <WiFi.h>               // WiFi
#include <WiFiClientSecure.h>   // WiFi


/* 
* -------------------------------------------------------------------------------------------
* WiFi and MQTT Connection
* -------------------------------------------------------------------------------------------
*/
constexpr char ssid1Tmp[] = "Franklin_2.4G";
constexpr char pwd1Tmp[]  = "candybrain0314";

String ssid1 = ssid1Tmp;              // 1순위 WiFi 접속정보
String password1 = pwd1Tmp;
String hostname = "CandyBrain_Test";  // Host name 설정

// const int wifi_connect_attempt = 2;         // 와이파이 연결시도1회 1지망 1회 2지망

WiFiClientSecure net = WiFiClientSecure();
//PubSubClient client(net);
unsigned long WiFi_Reconnect = 0;
// ------------------------------------------------------------------------------------------


void setup() {
  // [System] Serial Initialization ----------------------------------------------------------
  Serial.begin(115200);
  while (!Serial)
    ;
  // -----------------------------------------------------------------------------------------

  // [WiFi] Initilaization -------------------------------------------------------------------
  ssid1.trim();
  //ssid2.trim();
  //password2.trim();
  password1.trim();
  initWiFi(ssid1, password1);
  // -----------------------------------------------------------------------------------------
  
}


/*
* -------------------------------------------------------------------------------------------
* WiFi Initialization
* -------------------------------------------------------------------------------------------
*/
void initWiFi(String i, String p) {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname.c_str());
  WiFi.begin((const char*)i.c_str(), (const char*)p.c_str());

  Serial.print("Connecting to WIFI network"); Serial.print(" / "); Serial.println(i);

  for (int i = 0; i < 20; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println(WiFi.localIP());
      // ipadd1 = WiFi.localIP().toString().c_str(); // 2022년 7월 19일 신동욱 추가 for LCD Display
      // configTime(0, 0, timeServer);
      //connectAWS();
      break;
    }
    Serial.print('.');
    delay(1000);
  }
}

void checkWiFiConnection() {
    static unsigned long lastCheckTime = 0;
    unsigned long checkInterval = 10000; // 10 seconds
    if (millis() - lastCheckTime > checkInterval) {
        lastCheckTime = millis();
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("Reconnecting to WiFi...");
            WiFi_Reconnect++;
            WiFi.disconnect();
            WiFi.reconnect();
        }
    }
}
// -----------------------------------------------------------------------------------------


void loop() {
  // put your main code here, to run repeatedly:

}
