# Arduino LED Visualizer + IoT Cloud Control

## Project Description
This project implements a **WS2812B** LED strip control system using the **FastLED** library in C++. It runs on an **ESP32** board and is managed via **Arduino IoT Cloud**. 

The system features 20 lighting modes, including special modes based on a distance sensor (**HC-SR04**) and a microphone (**KY-038**) with FFT analysis. Settings such as mode, color, and brightness are stored in **EEPROM** memory, ensuring they persist after a device restart.

---

## Technologies and Libraries
* **Arduino IoT Cloud** – Remote control via the cloud
* **KY-038** – Sound detection
* **FastLED** – Addressable LED strip support
* **arduinoFFT** – Audio frequency analysis
* **EEPROM** – Persistent storage for settings (mode, color, brightness)
* **HC-SR04** – Distance measurement
* **Arduino Cloud Properties** – Cloud variable management

---

## Main Functionalities
* Remote control of LED colors, brightness, and modes
* Sound reactivity (FFT analysis)
* Distance sensor integration (color mapped to distance)
* Persistent settings storage in EEPROM
* Seamless integration with Arduino IoT Cloud

---

## LED Operation Modes
The project supports various lighting effects, including:
* Static Color
* Rainbow
* Gradient
* Bouncing and Pulsing
* Color Chasing and Spreading
* Sine Wave effects
* Audio Visualizer (Sound reactive)
* Distance Visualization (HC-SR04 sensor)

---

## Arduino IoT Cloud Integration
* Remote adjustment of mode, color, and brightness
* System Power Toggle (variable `w`)
* RGB Color selection (variable `ergiebe`)
* Cloud change handling via the following functions:
    * `onOdczytJasnosciChange();`
    * `onWyborTrybuChange();`
    * `onErgiebeChange();`

---

## Sound Reactivity (FFT)
* **Analog Microphone**: Pin 34
* **Sampling Frequency**: approx. 14 kHz
* Real-time FFT signal analysis and LED color mapping

---

## Distance Sensor Interaction
The **HC-SR04** sensor measures distance and visualizes the result on the LED strip:
* **Close** – Blue color
* **Medium** – Green color
* **Far** – Red color

---

## EEPROM Memory
The following data is stored in memory:
* **Address 0**: Operating Mode
* **Address 1**: Color
* **Address 2**: Brightness
* **Address 3, 4, 5**: RGB Components

---

## Hardware
* ESP32
* WS2812B LED Strip
* HC-SR04 Ultrasonic Sensor
* KY-038 Microphone

---
---

## Opis projektu
Projekt realizuje system sterowania taśmą LED **WS2812B** z wykorzystaniem biblioteki **FastLED** w języku C++.
Działa na płytce **ESP32** i jest sterowany za pomocą **Arduino IoT Cloud**.
Zawiera 20 trybów świecenia oraz tryby specjalne oparte o czujnik odległości (**HC-SR04**) i mikrofon (**KY-038**) z analizą FFT.
Ustawienia (tryb, kolor, jasność) zapisywane są w pamięci **EEPROM**, dzięki czemu zachowują się po restarcie urządzenia.

---

## Technologie i biblioteki
- Arduino IoT Cloud – zdalne sterowanie przez chmurę
- KY-038 – detekcja dźwięku
- FastLED – obsługa taśm adresowalnych LED
- arduinoFFT – analiza częstotliwości dźwięku
- EEPROM – zapis ustawień (tryb, kolor, jasność)
- HC-SR04 – pomiar odległości
- Arduino Cloud Properties – obsługa zmiennych w chmurze

---

## Główne funkcjonalności
- Sterowanie kolorami, jasnością i trybami LED
- Reakcja na dźwięk (analiza FFT)
- Reakcja na czujnik odległości (kolor zależny od dystansu)
- Zapis ustawień w pamięci EEPROM
- Integracja z Arduino IoT Cloud

---

## Tryby pracy LED
Projekt obsługuje różne efekty świetlne, m.in.:
- Statyczny kolor
- Tęcza
- Gradient
- Odbijanie i pulsowanie
- Schodzenie i rozchodzenie kolorów
- Efekty sinusoidalne
- Reakcja na dźwięk (Audio Visualizer)
- Wizualizacja odległości (czujnik HC-SR04)

---

## Integracja z Arduino IoT Cloud
- Zdalna zmiana trybu, koloru i jasności
- Włączanie i wyłączanie systemu (zmienna `w`)
- Ustawienie koloru RGB (zmienna `ergiebe`)
- Obsługa zmian poprzez funkcje:
  - onOdczytJasnosciChange();
  - onWyborTrybuChange();
  - onErgiebeChange();

---

## Reakcja na dźwięk (FFT)
- Mikrofon analogowy: pin 34
- Częstotliwość próbkowania: około 14 kHz
- Analiza sygnału FFT i zmiana koloru taśmy LED w czasie rzeczywistym

---

## Reakcja na czujnik odległości
Czujnik **HC-SR04** mierzy odległość i wizualizuje wynik na pasku LED:
- Blisko – kolor niebieski
- Średnio – kolor zielony
- Daleko – kolor czerwony

---

## Pamięć EEPROM
W pamięci zapisywane są: tryb pracy (0), Kolor (1), Jasność (2), Składowe RGB (3,4,5)
---

## Sprzęt
- ESP32
- Taśma LED WS2812B
- Czujnik ultradźwiękowy HC-SR04
- Mikrofon KY-038

---

