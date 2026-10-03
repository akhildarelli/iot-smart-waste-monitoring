# IoT Smart Waste Monitoring and Alerting System

An IoT-based smart waste management project developed around an Arduino Uno, ultrasonic sensing, Wi-Fi connectivity, ThingSpeak monitoring, LCD status display, and alert mechanisms.

## Overview

The project is designed to monitor waste-bin conditions and reduce unnecessary manual inspection. The academic project documentation describes a broader prototype architecture incorporating Arduino Uno, ultrasonic sensors, GSM, GPS, Wi-Fi, LCD, servo motor and solar power.

The current Arduino sketch in this repository directly demonstrates:
- Ultrasonic distance measurement for bin-level monitoring
- 16x2 LCD status display
- LED threshold indication
- ESP8266 Wi-Fi communication
- ThingSpeak data updates
- SMS alert routine

> **Implementation note:** The project report describes additional prototype features such as a second ultrasonic sensor, GPS, servo-controlled lid and solar power. Those features should only be claimed as implemented in the repository when their corresponding source code/hardware documentation is added.

## System Architecture

```text
             +-------------------+
             |   Ultrasonic      |
             |      Sensor       |
             +---------+---------+
                       |
                       v
                 +-----------+
                 | Arduino   |
                 |   Uno     |
                 +-----+-----+
                       |
          +------------+-------------+
          |            |             |
          v            v             v
       16x2 LCD       LED       ESP8266 Wi-Fi
                                      |
                                      v
                                +-----------+
                                | ThingSpeak|
                                |   Cloud   |
                                +-----------+

       Threshold condition
              |
              v
        Alert / SMS routine
```

## Hardware

Based on the project documentation:

- Arduino Uno
- Ultrasonic sensor(s)
- 16x2 LCD
- ESP8266 Wi-Fi module
- GSM module
- GPS module
- Servo motor
- LED
- Solar panel / regulated power supply

See [`Hardware/components.md`](Hardware/components.md).

## Software

- Arduino IDE
- Embedded C / Arduino C++
- ESP8266 AT commands
- ThingSpeak HTTP update API

## Current Pin Configuration

| Component | Arduino Pin |
|---|---|
| LCD RS | D2 |
| LCD E | D3 |
| LCD D4 | D4 |
| LCD D5 | D5 |
| LCD D6 | D6 |
| LCD D7 | D7 |
| LED | D8 |
| ESP8266 RX | D9 |
| ESP8266 TX | D10 |
| Ultrasonic TRIG | A0 |
| Ultrasonic ECHO | A1 |

## How It Works

1. The Arduino initializes the LCD, ultrasonic sensor, LED and ESP8266.
2. The ESP8266 is configured in station mode and connects to Wi-Fi.
3. The ultrasonic sensor measures the distance to the waste surface.
4. The measured distance is displayed on the LCD.
5. The reading is sent to ThingSpeak through an HTTP GET request.
6. When the measured distance falls below the configured threshold, the LED is activated and the SMS routine is triggered.
7. ThingSpeak can then be used for remote visualization of the recorded field.

## ThingSpeak

The sketch uses the ThingSpeak HTTP endpoint:

```text
GET /update?api_key=YOUR_API_KEY&field1=VALUE
```

Do **not** commit a real ThingSpeak API key.

## Configuration

Create a local file:

```text
Arduino/Smart_Waste_Monitoring/secrets.h
```

using:

```text
Arduino/Smart_Waste_Monitoring/secrets.h.example
```

The real `secrets.h` is ignored by Git.

### Required values

- Wi-Fi SSID
- Wi-Fi password
- ThingSpeak Write API key
- SMS destination number

## Uploading the Sketch

1. Install Arduino IDE.
2. Open `Arduino/Smart_Waste_Monitoring/Smart_Waste_Monitoring.ino`.
3. Copy `secrets.h.example` to `secrets.h`.
4. Enter your own local credentials in `secrets.h`.
5. Connect the Arduino Uno.
6. Select the correct board and COM port.
7. Install/use the required Arduino libraries:
   - LiquidCrystal
   - SoftwareSerial
8. Upload the sketch.
9. Open Serial Monitor at 9600 baud for diagnostics.

## Security

Never upload:
- Wi-Fi passwords
- ThingSpeak API keys
- Phone numbers
- SIM credentials
- Private GPS/location information

If a credential has already been exposed publicly, regenerate/revoke it before publishing the repository.

## Documentation

The complete academic project report is included under [`Documentation/`](Documentation/).

It contains the project abstract, introduction, objectives, literature survey, proposed system, benefits, working principle, block diagram, hardware/software descriptions, results section, conclusion, future scope and references.

## Future Scope

The academic documentation identifies possible extensions including:
- AI-based predictive waste collection
- Machine-learning analysis of waste-generation patterns
- Solar-powered smart-bin deployment
- Mobile application integration
- Citizen waste reporting
- Automated waste segregation
- Larger smart-city deployments

## Project Status

Academic / prototype project.

## Author

**Akhil Darelli**

B.Tech Computer Science and Engineering

## Repository Structure

```text
iot-smart-waste-monitoring/
├── Arduino/
│   └── Smart_Waste_Monitoring/
├── Hardware/
├── Documentation/
├── Images/
├── Demo/
├── .gitignore
└── README.md
```
