#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "secrets.h"

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define RX 9
#define TX 10

#define TRIG_PIN A0
#define ECHO_PIN A1
#define LED_PIN 8

const char HOST[] = "api.thingspeak.com";
const char PORT[] = "80";

int countTrueCommand;
int countTimeCommand;
boolean found = false;

SoftwareSerial esp8266(RX, TX);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("  WELCOME");
  delay(1000);

  lcd.clear();
  lcd.print("IoT smart waste");
  lcd.setCursor(0, 1);
  lcd.print("   monitoring");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  esp8266.begin(115200);

  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand(
    "AT+CWJAP=\"" + String(WIFI_SSID) + "\",\"" +
    String(WIFI_PASSWORD) + "\"",
    20,
    "OK"
  );
}

void loop() {
  int distance = ultrasonic_read();

  String getData =
    "GET /update?api_key=" + String(THINGSPEAK_API_KEY) +
    "&field1=" + String(distance);

  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand(
    "AT+CIPSTART=0,\"TCP\",\"" + String(HOST) + "\"," + String(PORT),
    15,
    "OK"
  );
  sendCommand(
    "AT+CIPSEND=0," + String(getData.length() + 4),
    4,
    ">"
  );

  esp8266.println(getData);
  delay(2000);

  sendCommand("AT+CIPCLOSE=0", 5, "OK");

  delay(5000); // ThingSpeak update delay
}

int ultrasonic_read() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.print("Bin level: ");
  lcd.print(distance);
  lcd.print("cm");

  if (distance < 10) {
    digitalWrite(LED_PIN, HIGH);
    delay(2000);
    digitalWrite(LED_PIN, LOW);
    sms();
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  return distance;
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print("AT CMD => ");
  Serial.println(command);

  while (countTimeCommand < maxTime) {
    esp8266.println(command);

    if (esp8266.find(readReplay)) {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found) {
    Serial.println("OK");
  } else {
    Serial.println("FAIL");
  }

  found = false;
  countTimeCommand = 0;
}

void sms() {
  // This routine assumes the GSM module is connected to the
  // Arduino hardware serial interface in the prototype.
  Serial.begin(9600);

  Serial.print("\r");
  delay(1000);

  Serial.print("AT+CMGF=1\r");
  delay(1000);

  Serial.print("AT+CMGS=\"");
  Serial.print(SMS_NUMBER);
  Serial.print("\"\r");
  delay(1000);

  Serial.print("Smart bin filled. Please check the waste collection point.");
  delay(1000);

  Serial.write(0x1A);
  delay(1000);
}
