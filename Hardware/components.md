# Hardware Components

The academic project documentation identifies the following major hardware components.

| Component | Role |
|---|---|
| Arduino Uno | Main microcontroller |
| Ultrasonic sensor | Measures distance / waste level |
| 16x2 LCD | Local status display |
| ESP8266 Wi-Fi | IoT connectivity and ThingSpeak communication |
| GSM module | SMS alert communication |
| GPS module | Location information in the broader prototype design |
| Servo motor | Automated lid operation in the broader prototype design |
| Solar panel | Renewable power source in the broader prototype design |
| Regulated power supply | Stable power for electronics |
| LED | Local threshold indication in the current sketch |

## Current Sketch Wiring

The current Arduino sketch uses:

- LCD: D2-D7
- LED: D8
- ESP8266 SoftwareSerial: D9-D10
- Ultrasonic TRIG: A0
- Ultrasonic ECHO: A1

The project report describes a broader hardware architecture with additional modules. Add verified wiring diagrams and source code for those modules when they are available.
