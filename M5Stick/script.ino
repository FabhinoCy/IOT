#include <M5StickCPlus.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define Echo_Pin 26
#define Trigger_Pin 0

WiFiMulti wifiMulti;
HTTPClient http;

int maximumRange = 300;
int minimumRange = 2;
long Distance;
long Duree;

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(4);

  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);
  pinMode(M5_LED, OUTPUT);
  Serial.begin(9600);

  digitalWrite (M5_LED, HIGH);

  wifiMulti.addAP("toto", "12345678");
  while(wifiMulti.run() != WL_CONNECTED) {
    M5.Lcd.fillScreen(BLACK);
    delay(1000);
    M5.Lcd.print("Connexion au reseau WiFi...");
  }
  M5.Lcd.print("Connecté au réseau WiFi");
}

void loop() {
  M5.Lcd.setCursor(0,0);

  digitalWrite(Trigger_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_Pin, LOW);

  Duree = pulseIn(Echo_Pin, HIGH);
  Distance = Duree/58.2;

  if (Distance >= maximumRange || Distance <= minimumRange)
  {
    M5.Lcd.fillScreen(RED);
    M5.Lcd.print("Absence de distance");
  }
  else
  {
    if(digitalRead(M5_BUTTON_HOME) == 0) {
      digitalWrite(10, LOW);

      String postData = "distance=" + String(Distance) + "&instant=false";
      http.begin("http://193.168.146.106/iot/update-distance.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(postData);
      http.end();
    } else {
      digitalWrite(10, HIGH);
    }

    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.print(Distance);
    M5.Lcd.print("cm");

    String postData = "distance=" + String(Distance) + "&instant=true";
    http.begin("http://193.168.146.106/iot/update-distance.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(postData);
    http.end();

    if (httpResponseCode != HTTP_CODE_OK) {
      M5.Lcd.println("Erreur lors de la requête POST");
    }

  }

 delay(400);
}