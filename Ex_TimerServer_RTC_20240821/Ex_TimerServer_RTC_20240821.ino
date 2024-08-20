/*
* --------------------------------------------------------------------
* 
* ESP32 RTC, Time server 초기화 Example Code
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

#include <RTClib.h>             // RTC
#include <time.h>               // Time library for NTP

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

RTC_DS3231 rtc;  // RTC 객체 생성
unsigned long lastDisplayTime = 0;

// NTP 서버 정보
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;


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

  // [WiFi] Initilaization -------------------------------------------------------------------
  ssid1.trim();
  //ssid2.trim();
  //password2.trim();
  password1.trim();
  initWiFi(ssid1, password1);
  // -----------------------------------------------------------------------------------------
  
  // [NTP] Time Server 연결 및 RTC 초기화 ------------------------------------------------------
  // 인터넷이 연결안된 경우에는 RTC 그대로 사용 연결 됐으면 항상 타임서버에서 시간 가져오기
  if (WiFi.status() == WL_CONNECTED) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                          timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
      Serial.println("RTC initialized with NTP time");
    } else {
      Serial.println("Failed to obtain time from NTP server, using last saved time from RTC");
    }
  } else {
    Serial.println("No WiFi connection, using last saved time from RTC");
  }
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
  checkWiFiConnection();

  if (millis() - lastDisplayTime >= 1000) { // 1초마다 실행
    lastDisplayTime = millis();
    displayTime();  // 시간 출력
  }

}
