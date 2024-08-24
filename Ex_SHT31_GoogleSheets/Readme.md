### 1. 제목: Google Sheets를 사용한 Data monitoring 
### 2. 파일명: Ex_THM_GoogleSheets.ino
### 3. 날짜: 2024.0824
### 4. 작성자: Candybrain 신동욱
### 5. 설명
본 코드는 구글시트의 단일셀에 ESP32의 I2C 포트에 연결된 SHT31센서의 온도 값과 시간을 지속적으로 업데이트 하는 예제코드 입니다.
### 6. 핵심데이
아래의 세가지의 데이터를 획득해야만 정상적인 작동이 가능합니다.

(1) fingerprint = "69:46:8B:B9:19:91:49:4C:E8:9B:A4:EC:A2:C4:A2:40:B0:54:E5:CD:06:7C:CE:BE:DC:88:F2:7C:10:56:F7:F8"
Google Sheets에서 웹 앱과 연결하기 위한 finger print는 고유 식별자를 사용하여 
Google Sheets를 웹 애플리케이션에 안전하게 연결하는 프로세스를 의미합니다. 
이 기술은 승인된 사용자 또는 시스템만 웹 앱에 액세스하고 상호 작용할 수 있도록 보장하는 데 자주 사용됩니다.
본인의 웹 앱 접근을 위해서 finger print를 생성해야 합니다.

(2) GAS_ID = "AKfycbyscxKxiG6nugUTm9LQaUx6tS_9Kf2RRy1FrEoQf8YN-_56nLgoMw9n5VRIGQIaeWn0"
Apps Script에서 웹 앱을 만들면 해당 웹 앱을 배포하게 됩니다. 이때 해당 웹 앱의 배포 ID를 획득 할 수 있습니다. 
GAS_ID는 배포된 Google Apps Script ID를 의미 합니다. 

(3) sheet_id = '1qc9ND7cO3mAGIjDTPpqzOySRi3emDDTJoFQfesG1eEM';
sheet id는 본인이 생성한 google sheet의 ID를 의미 합니다. 
다음과 같은 주소형식에서 
https://docs.google.com/spreadsheets/d/1qc9ND7cO3mAGIjDTPpqzOySRi3emDDTJoFQfesG1eEM/edit?gid=0#gid=0

아래 부분이 sheet id 입니다. 
1qc9ND7cO3mAGIjDTPpqzOySRi3emDDTJoFQfesG1eEM
