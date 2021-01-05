#include <WiFi.h>
#include <ThingSpeak.h>

#include <DHT.h>
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Tertiary Infotech"; // key in SSID
const char* password = "Tertiary888"; //key in Wifi password

WiFiClient client;
unsigned long myChannelNumber = YYYYYY; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "XXXXXXXXXXXXXXX"; //Your Write API Key

const char* server = "api.thingspeak.com";

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Temperature = ");
  Serial.println(t);
  Serial.print("Humidity = ");
  Serial.println(h);
  delay(1000);
      

  ThingSpeak.writeField(myChannelNumber, 1,t, myWriteAPIKey); //Update Temperature in ThingSpeak
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 2,h, myWriteAPIKey); //Update Humidity in ThingSpeak
  delay(100);

}
