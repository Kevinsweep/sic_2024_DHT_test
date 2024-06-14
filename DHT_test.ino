#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTTYPE DHT11 
DHT dht(13, DHTTYPE);

const char* wifi_name = "Punya kepin";
const char* pass = "koinonia";


const char* serverName = "http://192.168.99.159:5000/dataDHT";

void printData(){
    Serial.print(F("Humidity: "));
    Serial.print(humid);
    Serial.println("%")

    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println(F("°C "));
    Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT11 test!"));

  dht.begin();

  // connect wifi
  WiFi.begin(wifi_name, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting");
  }
  Serial.println("Connected");
}

void loop() {
  delay(3000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  printData();

  String url_name = String(serverName) + "?temperature=" + String(t) + "&humidity=" + String(h);

  HTTPClient http;

  http.begin(url_name);

  int httpResponse = http.POST("");

  if (httpResponse > 0) {
    String response = http.getString();
    Serial.println(httpResponse);
    Serial.println(response);
  }
  else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
}