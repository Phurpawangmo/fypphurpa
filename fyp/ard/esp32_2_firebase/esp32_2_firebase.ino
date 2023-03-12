#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(26, DHT11);

#define WIFI_SSID "CST-HD"
#define WIFI_PASSWORD "Hostel@HD#"
#define FIREBASE_AUTH "https://esp32-firebase-d84f6-default-rtdb.firebaseio.com/"
#define FIREBASE_HOST "lLxdIjycu39rhYKH2L3NkrsLEMLOKhHcshlMZHY3"

void setup() {
  Serial.begin(115200);
  Serial.print("DHT TEST");
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_AUTH, FIREBASE_HOST);
}

int n = 0;

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Humidity: " + String(h) + "%\t");
  Serial.println("Temperature: " + String(t));

  Firebase.pushFloat("sensor_data/Humidity", h);
  if (Firebase.failed()) {
    Serial.println("Failed to set humidity value in Firebase");
    return;
  }

  Firebase.pushFloat("sensor_data/Temperature", t);
  if (Firebase.failed()) {
    Serial.println("Failed to set temperature value in Firebase");
    return;
  }

  Serial.println("Temperature and Humidity Data Sent Successfully");
  delay(1000);
}
