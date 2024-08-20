/*
* --------------------------------------------------------------------
*
* The beginning: Embedded Technology & Artist 
* Example Code #1 (version 1.0)
*
* 2024.08.13 (last update 2024.08.13)
* Dongwook Shin (CandyBrain)
* 
* --------------------------------------------------------------------
*/

#include <WiFiNINA.h>                     // Change to WiFiNINA for MKR WiFi 1010
#include <WiFiSSLClient.h>                // Change to WiFiSSLClient for secure connection
#include <DFRobot_SHT3x.h>                // [Sensor] Temperature and Humidity

const char* ssid = "Franklin_2.4G";       // Your WiFi network
const char* password = "candybrain0314";      // Your WiFi password
const char* host = "script.google.com";   // 
const int httpsPort = 443;

WiFiSSLClient client;

const char* fingerprint = "69:46:8B:B9:19:91:49:4C:E8:9B:A4:EC:A2:C4:A2:40:B0:54:E5:CD:06:7C:CE:BE:DC:88:F2:7C:10:56:F7:F8";
// String GAS_ID = "AKfycby3jbLrXAhikdOTInVmtrguEej5FIH_ZbiXMTY2nPIu4ifTb1ndFLTXxmKH6rsVIsbs";  // Webapp ID
String GAS_ID = "AKfycbyscxKxiG6nugUTm9LQaUx6tS_9Kf2RRy1FrEoQf8YN-_56nLgoMw9n5VRIGQIaeWn0";

// DFRobot_SHT3x sht3x(&Wire, /*address=*/0x44, /*RST=*/4);  // 온습도 센서 객체 생성

float kk = 30.1;

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // // Initialize SHT31
  // while (sht3x.begin() != 0) {
  //   Serial.println("Failed to Initialize the chip, please confirm the wire connection");
  //   delay(1000);
  // }

  // Serial.print("SHT31 chip serial number: ");
  // Serial.println(sht3x.readSerialNumber());

  // if (!sht3x.softReset()) {
  //   Serial.println("Failed to Initialize the chip....");
  // }

  // Serial.println("Read data in single measurement mode");
  // Serial.println("");
  // client.setInsecure();  // 이 줄은 제거됨
}

void loop() 
{
  static unsigned long lastCheckTime = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastCheckTime > 500) {   // Adjusting the delay to 5 seconds
    lastCheckTime = currentMillis;

    float t = kk++; //sht3x.getTemperatureC();
    float h = 32.1; //sht3x.getHumidityRH();  // 수정: `:`을 `;`으로 변경

    sendData(t);

    yield();  // Yield to the system to maintain stability
  }
}

void sendData(float cds)
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  // client.verify() 함수는 WiFiSSLClient에 없음, 이 부분 제거
  // if (client.verify(fingerprint, host)) {
  //   Serial.println("certificate matches");
  // } else {
  //   Serial.println("certificate doesn't match");
  // }

  String url = "/macros/s/" + GAS_ID + "/exec?Cds=" + cds;
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

  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("ESP32/Arduino CI successful!");
  } else {
    Serial.println("ESP32/Arduino CI has failed");
    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
  }

  while (client.available()) {
    String response = client.readStringUntil('\n');
    Serial.println(response);
  }

  Serial.println("closing connection");
  client.stop();  // Ensure the connection is properly closed
}
