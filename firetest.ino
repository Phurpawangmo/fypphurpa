#include <IOXhop_FirebaseESP32.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#define WIFI_SSID "Darshans wifi"
#define WIFI_PASSWORD "17523988"
#define FIREBASE_AUTH "https://esp32-firebase-d84f6-default-rtdb.firebaseio.com/"
#define FIREBASE_HOST "lLxdIjycu39rhYKH2L3NkrsLEMLOKhHcshlMZHY3"

int button = 5;

SoftwareSerial abc (18, 19);  //rx tx serial pins bw esp and ard


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  abc.begin(9600);
  pinMode(5, INPUT_PULLUP);
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
void loop() {
    String msg = abc.readStringUntil('\n');
    Serial.println(msg);
    if(msg.length()>0)    
    {
      FBpush(msg);
    }    
}

void FBpush(String msg)
{
   Firebase.pushString("sensor_data/alldata", msg);
  
}
    
   
