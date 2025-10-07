# Arduino LED Visualizer + IoT Cloud Control

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

