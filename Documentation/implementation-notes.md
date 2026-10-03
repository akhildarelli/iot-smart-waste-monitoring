# Implementation Notes

## Important distinction

The academic report describes the complete prototype concept, including two ultrasonic sensors, GSM, GPS, Wi-Fi, LCD, servo motor and solar power.

The Arduino sketch currently included in this repository directly contains code for:

- Arduino Uno
- One ultrasonic sensor
- 16x2 LCD
- LED
- ESP8266 via SoftwareSerial
- ThingSpeak HTTP updates
- An SMS routine

GPS coordinate acquisition, servo control and the second ultrasonic sensor are not present in the pasted sketch. The repository therefore avoids claiming those functions are implemented by this particular source file.

## Threshold

The current sketch triggers the LED/SMS routine when:

```cpp
distance < 10
```

Adjust the threshold after testing it against the physical bin dimensions and sensor placement.

## Security

Credentials must be stored in the local `secrets.h` file. That file is ignored by Git.
