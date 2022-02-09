#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "NETGEAR94";
const char* password = "imaginaryrabbit652";

void setup() {
  // put your setup code here, to run once:
  WiFi.begin(ssid, password);

  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to WiFi network");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  // Serial.print(WiFi.localIPv6());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    long rnd = random(1, 10);
    HTTPClient client;
    // client.begin("http://jsonplaceholder.typicode.com/comments?id=" + String(rnd));
    // client.begin("https://api.coingecko.com/api/v3/simple/price?ids=ethereum%2Cbitcoin&vs_currencies=usd%2Ceur");
    // client.begin("http://192.168.0.6:3001/api");
    client.begin("https://react-iot-webapp.herokuapp.com/api");
    
    int httpCode = client.GET();

    if (httpCode > 0) {
      String payload = client.getString();
      Serial.println("\nStatus code: " + String(httpCode));
      Serial.println("\n" + String(payload));

      // DynamicJsonDocument doc(192);
      // // StaticJsonDocument<192> doc;

      // DeserializationError error = deserializeJson(doc, payload);

      // if (error) {
      //   Serial.print("deserializeJson() failed: ");
      //   Serial.println(error.c_str());
      //   return;
      // }

      // for (JsonPair item : doc.as<JsonObject>()) {
      //   const char* item_key = item.key().c_str(); // "bitcoin", "ethereum"

      //   float value_usd = item.value()["usd"]; // 42842, 3096.09
      //   float value_eur = item.value()["eur"]; // 37466, 2707.59

      //   Serial.println("\n" + String(item_key) + ": " + "USD $" + String(value_usd) + ", EUR $" + String(value_eur));
      // }

    } else {
      Serial.println("Error on HTTP request");
    }

  } else {
    Serial.println("Connection lost");
  }

  delay(10000);
}