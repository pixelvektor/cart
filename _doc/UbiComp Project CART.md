# UbiComp: Project CART (carrera autonomous route tracker)

## Kick-Off
*Prof. Stefan Henkler, Adrian Schmidt, Tom Quinders, Fabian Schneider // 2017-05-12*

- Aufteilung in Stufen
-- erst horizontaler Schwenk
-- Slider
-- vertikaler Schwenk nachziehen wenn hor. funktioniert
- nach Bibliotheken für die Bilderkennung suchen
- Verfolgung eines IR Lichtes auf dem Auto
- Raspberry Pi scheint eine passende Plattform zu sein
- Kamera für RPi (IR)
- zwei Kameras (eine zum Steuern, eine zum Aufnehmen)

## Research
- Servos oder **Schrittmotoren**
- Raspberry Pi 3 sollte die benötigte Rechenleistung haben
- IR Kamera (8MP): https://www.adafruit.com/product/3100
- OpenCV zum Tracken des Autos auf der Strecke
- OpenCV muss lernen was es verfolgen soll
- Sensoren (Licht / Druck?) für Endpositionen

## Benötigte Hardware
- Raspberry Pi Kamera
- Schrittmotoren
- Sensoren

## OpenCV unter Raspbian
- OpenCV 3.x
- Raspbian Jessie (Kernel 3.10)
- soll das Auto und dessen Richtung erkennen
- http://www.instructables.com/id/RasPi-OpenCV-Face-Tracking/