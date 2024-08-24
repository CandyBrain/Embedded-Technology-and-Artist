/*
* --------------------------------------------------------------------
*  
* CandyBrain ART and TEC Lecture Example Code
* 
* Ex_THM.GoogleSheets_1.ino
* 
* Date: 2024.08.22 (last update 2024.08.22)
* Author: Dongwook Shin / CandyBrain
*
* GitHub: 
*
* --------------------------------------------------------------------
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DFRobot_SHT3x.h>
// #include <WebServer.h>
//#include <ESPmDNS.h>
#include <Update.h>
#include <esp_task_wdt.h>

const char* ssid = "Franklin_2.4G";
const char* password = "candybrain0314";
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;

const char* fingerprint = "06:5E:3B:66:39:0A:5D:3C:7C:E5:1F:27:34:24:42:60:64:53:B3:D9:8E:4D:4E:97:F5:B7:08:B5:9D:19:0A:0A";
 String GAS_ID = "AKfycbyXCKgNxwmXXYNQwONGWAcVnwN9kHu7luBZv2XMf4gJIaAt539dOgi36WkixhuNyhWYcg"; // 데이터 쌓임
//String GAS_ID = "AKfycbw4n7cwEgjU9Fk8pBCaFzH6IStoSaDOd55ufS3Udgitn5x-3FN-NsYxF6PFjbhHQMhFEQ"; // 단일셀

DFRobot_SHT3x sht3x(&Wire, 0x44, 4);

/* 
* -------------------------------------------------------------------------------------------
* 데이터 전송 테스크
* -------------------------------------------------------------------------------------------
*/
void sendDataTask(void *parameter) {
  while (true) {
    static unsigned long lastCheckTime = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastCheckTime > 5000) { // 데이터를 N초 간격으로 전송, 1000 = 1초
      lastCheckTime = currentMillis;

      float t = sht3x.getTemperatureC();  // 온도데이터 획득
      float h = sht3x.getHumidityRH();    // 습도데이터 획득

      sendData(t);                        // Google Web App으로 데이터 전송
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // 작은 딜레이로 안정성 확보
  }
}


/* 
* -------------------------------------------------------------------------------------------
* 실제 획득한 데이터를 구글로 전송하는 함수
* -------------------------------------------------------------------------------------------
*/
void sendData(float value) {
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) 
  {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) 
  {
    Serial.println("certificate matches");
  } 
  else 
  {
    Serial.println("certificate doesn't match");
  }

  String url = "/macros/s/" + GAS_ID + "/exec?Cds=" + value;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP32\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  while (client.available()) {
    String response = client.readStringUntil('\n');
    Serial.println(response);
  }

  Serial.println("closing connection");
  client.stop();  // Ensure the connection is properly closed
}
// ------------------------------------------------------------------------------------------


/* 
* -------------------------------------------------------------------------------------------
* ESP32 시스템 초기화
* -------------------------------------------------------------------------------------------
*/
void setup() {
  delay(2000);  // 안전성 확보

  // Serial Initialization -------------------------------------------------------------------
  Serial.begin(115200);
  while (!Serial)
    ;
  // -----------------------------------------------------------------------------------------


  // WiFi Connection -------------------------------------------------------------------------
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  //WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // -----------------------------------------------------------------------------------------


  // 온습도 센서 초기화 -----------------------------------------------------------------------
  while (sht3x.begin() != 0) {
    Serial.println("Failed to Initialize the chip, please confirm the wire connection");
    delay(1000);
  }

  Serial.print("SHT31 chip serial number: ");
  Serial.println(sht3x.readSerialNumber());

  if (!sht3x.softReset()) {
    Serial.println("Failed to Initialize the chip....");
  }
  // -----------------------------------------------------------------------------------------

  client.setInsecure(); // WiFiClientSecure 클라이언트에 SSL/TLS 인증서 확인 비활성화

  xTaskCreatePinnedToCore(sendDataTask, "sendDataTask", 8192, NULL, 1, NULL, 1);  // 태스크 정의
}
// ------------------------------------------------------------------------------------------


void loop() {
  // 메인 루프에서는 별도로 처리할 작업 없음
}
