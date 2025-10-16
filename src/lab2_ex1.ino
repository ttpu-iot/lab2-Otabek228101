// #include <Arduino.h>
// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <ArduinoJson.h>

// constexpr uint8_t PIN_RED    = 26;
// constexpr uint8_t PIN_GREEN  = 27;
// constexpr uint8_t PIN_BLUE   = 14;
// constexpr uint8_t PIN_YELLOW = 12;

// static const char* WIFI_SSID = "Wokwi-GUEST";
// static const char* WIFI_PASS = "";  

// static const char* READ_URL =
//   "http://api.thingspeak.com/channels/3109942/feeds.json?results=1";

// const uint32_t POLL_INTERVAL_MS = 5000;
// uint32_t lastPoll = 0;

// int levelFromStr(const char* s) {
//   if (!s) return LOW;
//   return (strcasecmp(s, "HIGH") == 0) ? HIGH : LOW;
// }

// void connectWiFi() {
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(WIFI_SSID, WIFI_PASS);
//   Serial.print("Connecting to WiFi: ");
//   Serial.print(WIFI_SSID);
//   Serial.print(" ");
//   uint8_t dots = 0;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(300);
//     Serial.print(".");
//     if (++dots % 20 == 0) Serial.println();
//   }
//   Serial.println();
//   Serial.print("WiFi connected. IP: ");
//   Serial.println(WiFi.localIP());
// }

// void setupPins() {
//   pinMode(PIN_RED, OUTPUT);
//   pinMode(PIN_GREEN, OUTPUT);
//   pinMode(PIN_BLUE, OUTPUT);
//   pinMode(PIN_YELLOW, OUTPUT);

//   digitalWrite(PIN_RED, LOW);
//   digitalWrite(PIN_GREEN, LOW);
//   digitalWrite(PIN_BLUE, LOW);
//   digitalWrite(PIN_YELLOW, LOW);
// }

// void setup() {
//   Serial.begin(115200);
//   delay(200);
//   Serial.println("\n[Lab2] ESP32 + HTTP + ArduinoJson v7");
//   setupPins();
//   connectWiFi();
// }

// void pollAndUpdate() {
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi disconnected, reconnecting...");
//     connectWiFi();
//   }

//   HTTPClient http;
//   http.setReuse(true);
//   http.begin(READ_URL);

//   Serial.print("GET ");
//   Serial.println(READ_URL);
//   int code = http.GET();

//   if (code != HTTP_CODE_OK) {
//     Serial.print("HTTP error: ");
//     Serial.println(code);
//     http.end();
//     return;
//   }

//   String payload = http.getString();
//   http.end();
//   #if ARDUINOJSON_VERSION_MAJOR >= 7
//     JsonDocument doc;
//   #else
//     DynamicJsonDocument doc(4096);
//   #endif
//   DeserializationError err = deserializeJson(doc, payload);

//   if (err) {
//     Serial.print("JSON parse error: ");
//     Serial.println(err.c_str());
//     return;
//   }
//   JsonArray feeds = doc["feeds"].as<JsonArray>();
//   if (feeds.isNull() || feeds.size() == 0) {
//     Serial.println("No feeds in response.");
//     return;
//   }

//   JsonObject last = feeds[0];
//   const char* f1 = last["field1"] | "LOW";
//   const char* f2 = last["field2"] | "LOW";
//   const char* f3 = last["field3"] | "LOW";
//   const char* f4 = last["field4"] | "LOW";
//   const char* name = last["field5"] | "unknown";

//   digitalWrite(PIN_RED,    levelFromStr(f1));
//   digitalWrite(PIN_GREEN,  levelFromStr(f2));
//   digitalWrite(PIN_BLUE,   levelFromStr(f3));
//   digitalWrite(PIN_YELLOW, levelFromStr(f4));

//   Serial.print("Entry: ");
//   Serial.print((int)last["entry_id"]);
//   Serial.print("  Name: ");
//   Serial.print(name);
//   Serial.print("  LEDs: R=");
//   Serial.print(f1);
//   Serial.print(" G=");
//   Serial.print(f2);
//   Serial.print(" B=");
//   Serial.print(f3);
//   Serial.print(" Y=");
//   Serial.println(f4);
// }

// void loop() {
//   uint32_t now = millis();
//   if (now - lastPoll >= POLL_INTERVAL_MS) {
//     lastPoll = now;
//     pollAndUpdate();
//   }
// }
