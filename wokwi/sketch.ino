#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define NTC_PIN 34
#define BETA 3950

int accLED = 26;
int gyroLED = 27;
int TempLED = 25;

Adafruit_MPU6050 mpu;

// WiFi (Wokwi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// 🔧 WiFi connect
void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

// 🔁 MQTT reconnect
void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("AstraPulseClient")) {
      Serial.println("MQTT Connected!");
    } else {
      Serial.print("Failed, retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(TempLED, OUTPUT);
  pinMode(accLED, OUTPUT);
  pinMode(gyroLED, OUTPUT);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  Serial.println("MPU6050 Ready!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // 📡 Connect WiFi
  setup_wifi();

  // 📡 MQTT setup
  client.setServer(mqtt_server, 1883);
}

void loop() {

  // 🔁 Maintain MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 🌡 Temperature
  int analogValue = analogRead(NTC_PIN);
  if (analogValue <= 0) analogValue = 1;
  if (analogValue >= 4095) analogValue = 4094;

  float temperature = 1 / (log(1 / (4095.0 / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;

  // LED logic
  if (temperature < 50) {
    digitalWrite(TempLED, LOW);
  } else if (temperature < 60) {
    digitalWrite(TempLED, HIGH);
    delay(500);
    digitalWrite(TempLED, LOW);
    delay(500);
  } else {
    digitalWrite(TempLED, HIGH);
    delay(150);
    digitalWrite(TempLED, LOW);
    delay(150);
  }

  // 📊 MPU
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float totalAcc = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  float totalGyro = sqrt(
    g.gyro.x * g.gyro.x +
    g.gyro.y * g.gyro.y +
    g.gyro.z * g.gyro.z
  );

  // LED logic
  if (totalAcc < 11.772) {
    digitalWrite(accLED, LOW);
  } else if (totalAcc < 14.715) {
    digitalWrite(accLED, HIGH);
    delay(500);
    digitalWrite(accLED, LOW);
    delay(500);
  } else {
    digitalWrite(accLED, HIGH);
    delay(150);
    digitalWrite(accLED, LOW);
    delay(150);
  }

  if (totalGyro <= 0.087) {
    digitalWrite(gyroLED, LOW);
  } else if (totalGyro <= 0.524) {
    digitalWrite(gyroLED, HIGH);
    delay(500);
    digitalWrite(gyroLED, LOW);
    delay(500);
  } else {
    digitalWrite(gyroLED, HIGH);
    delay(50);
    digitalWrite(gyroLED, LOW);
    delay(50);
  }

  // 📦 JSON
String payload = "{";

payload += "\"time\":" + String(millis()) + ",";
payload += "\"temperature\":" + String(temperature) + ",";

payload += "\"acc_x\":" + String(a.acceleration.x) + ",";
payload += "\"acc_y\":" + String(a.acceleration.y) + ",";
payload += "\"acc_z\":" + String(a.acceleration.z) + ",";

payload += "\"gyro_x\":" + String(g.gyro.x) + ",";
payload += "\"gyro_y\":" + String(g.gyro.y) + ",";
payload += "\"gyro_z\":" + String(g.gyro.z) + ",";

payload += "\"acceleration\":" + String(totalAcc) + ",";
payload += "\"gyro\":" + String(totalGyro);


payload += "}";

  // 📡 Publish
  client.publish("astrapulse/jd/data", payload.c_str());

  Serial.println(payload);

  delay(1000);
}