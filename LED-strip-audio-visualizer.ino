#include "arduino_secrets.h"
#include <arduinoFFT.h>
#include "thingProperties.h"
#include <FastLED.h>
#include <EEPROM.h>

#define iloscLedow 60
#define pinDanych 27
#define ledPin 26
#define trigPin 32
#define echoPin 33
#define analogMicPin 34
#define digitalMicPin 35

#define EEPROM_SIZE 6
#define EEPROM_TRYB 0
#define EEPROM_KOLOR 1
#define EEPROM_JASNOSC 2

#define SAMPLES 1024          
#define SAMPLING_FREQUENCY 14000 

const int poczatkowaJasnosc = 60;
const int poczatkowyKolor = 8; 
const int poczatkowyTryb = 0;

double vReal[SAMPLES]; 
double vImag[SAMPLES];            

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);
unsigned int samplingPeriod;
unsigned long microSeconds;

uint8_t r,g,b;

CRGB ledy[60];
uint8_t H = 0; 

CRGB Kolor(int odczytKoloru) {
  switch (odczytKoloru) {
    case 0: return CRGB::White;
    case 1: return CRGB::Red;
    case 2: return CRGB::Green;
    case 3: return CRGB::Blue;
    case 4: return CRGB::Purple;
    case 5: return CRGB::Yellow;
    case 6: return CRGB::DeepPink;
    case 7: return CRGB::Aqua;
    case 8: return CRGB::Orange;
    case 200: return CRGB(r,g,b);
    case 250: return CRGB(EEPROM.read(3), EEPROM.read(4), EEPROM.read(5));
    default: return CRGB::Black; 
  }
}

void trybPracy(int wyborTrybu, int odczytKoloru, int odczytJasnosci, long cm) {
  switch (wyborTrybu) {
    case 0:
      statyczny(odczytKoloru, odczytJasnosci);
      break;
    case 1:
      tecza(odczytJasnosci);
      break;
    case 2:
      gradient_1(odczytJasnosci);
      break;
    case 4:
      odbijanie(odczytKoloru, odczytJasnosci);
      break;
    case 5:
      pulsowanie(odczytKoloru, odczytJasnosci);
      break;
    case 7:
      przejscia(odczytJasnosci);
      break;
    case 8:
      schodzenie(odczytKoloru, odczytJasnosci);
      break;
    case 9:
      rozchodzenie(odczytKoloru, odczytJasnosci);
      break;
    case 10:
      petla(odczytKoloru, odczytJasnosci);
      break;
    case 11:
      kolorowaPetlaPlynna(odczytJasnosci);
      break;
    case 12:
      randomKolor(odczytJasnosci);
      break;
    case 13:
      przejsciaPetla(odczytJasnosci);
      break;
    case 15:
      czujnikRev(cm, odczytJasnosci);
      break;
    case 16:
      petlaSkokowa(odczytKoloru, odczytJasnosci);
      break;
    case 17:
      petlaKolorowaZblurowana(odczytKoloru, odczytJasnosci);
      break;
    case 18:
      sinusoida(odczytKoloru, odczytJasnosci);
      break;
    case 20:
      losowyGradient(odczytJasnosci);
      break;
    default:
      FastLED.clear();
  }
}

void statyczny(int c, int j) {
  fill_solid(ledy, 60, Kolor(c));
  FastLED.setBrightness(j);
  FastLED.show();
}

void odbijanie(int c, int j) {
  for (int i = 0; i < 60; i++) {
    ledy[i] = Kolor(c);
    FastLED.setBrightness(j);
    FastLED.show();
    delay(30);
  }
  for (int i = 60 - 1; i >= 0; i--) {
    ledy[i] = Kolor(10);
    FastLED.setBrightness(j);
    FastLED.show();
    delay(30);
  }
}

void pulsowanie(int c, int j) {
  for (int i = 0; i <= 80; i++) {
    statyczny(c, i);
    FastLED.show();
    delay(30);
  }
  for (int i = 80; i >= 0; i--) {
    statyczny(c, i);
    FastLED.show();
    delay(30);
  }
}

void petla(int odczytKoloru, int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  for (int i = 0; i < 60; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[i] = Kolor(odczytKoloru);
    blur1d(ledy, 60, 100);
    FastLED.show();
    ledy[i] = CRGB::Black;
    delay(20);
    FastLED.show();
  }
}

void petlaKolorowaZblurowana(int odczytKoloru, int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  for (int i = 0; i < 60; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[i] = CHSV(H, 255, 255);
    EVERY_N_MILLISECONDS(20) {
      H++;
    }
    blur1d(ledy, 60, 100);
    FastLED.show();
    delay(30);
    ledy[i] = CRGB::Black;
  }
}

void petlaSkokowa(int odczytKoloru, int odczytJasnosci) {
    for (int i = 4; i < 60; i+=8) {
      for (int j = i; j <= i+3; j++) {
        ledy[j] = Kolor(200); 
      }
    }
    FastLED.setBrightness(odczytJasnosci);
    for (int i = 0; i < 60; i += 8) { 
      FastLED.setBrightness(odczytJasnosci);
      for (int j = 0; j < 4 && (i + j) < 60; j++) {
        FastLED.setBrightness(odczytJasnosci);
        ledy[i + j] = Kolor(odczytKoloru);
      }
      FastLED.show();
      delay(120);
      for (int j = 0; j < 4 && (i + j) < 60; j++) {
        FastLED.setBrightness(odczytJasnosci);
        ledy[i + j] = CRGB::Black;
      }
      FastLED.show();
    }
}

void rozchodzenie(int odczytKoloru, int odczytJasnosci) {
  int srodekLewy = 60 / 2; 
  int srodekPrawy = (60 / 2) - 1; 
  for (int i = 0; i <= srodekLewy; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[srodekLewy - i] = Kolor(odczytKoloru);  
    ledy[srodekPrawy + i] = Kolor(odczytKoloru); 
    FastLED.show();
    delay(40);
  }
  for (int i = 0; i <= srodekLewy; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[srodekLewy - i] = CRGB::Black; 
    ledy[srodekPrawy + i] = CRGB::Black; 
    FastLED.show();
    delay(40);
  }
}

void schodzenie(int odczytKoloru, int odczytJasnosci) {
  int srodek = 60 / 2; 

  for (int i = 0; i <= srodek; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[i] = Kolor(odczytKoloru);  
    ledy[60 - i - 1] = Kolor(odczytKoloru);  
    FastLED.show();
    delay(40);
  }

  for (int i = 0; i <= srodek; i++) {
    FastLED.setBrightness(odczytJasnosci);
    ledy[i] = CRGB::Black;  
    ledy[60 - i - 1] = CRGB::Black;  
    FastLED.show();
    delay(40);
  }
}

void tecza(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  fill_rainbow(ledy, 60, 0, 255 / 60);
  FastLED.show();
}

void gradient_1(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  fill_gradient_RGB(ledy, 60, CRGB::Red, CRGB::Purple, CRGB::Blue, CRGB::Green);
  FastLED.show();
}

void przejscia(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  for (int i = 0; i < 60; i++) {
    ledy[i] = CHSV(H, 255, 110);
    FastLED.show();
  }
  EVERY_N_MILLISECONDS(20) {
    H++;
  }
}

void kolorowaPetlaPlynna(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  for (int i = 0; i < 60; i++) {
    ledy[i] = CHSV(H + (i * 10), 255, 110);
  }
  EVERY_N_MILLISECONDS(8) {
    H++;
  }
  FastLED.show();
}

void randomKolor(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  EVERY_N_MILLISECONDS(12) {
    ledy[random(0, 61)] = Kolor(random8(0, 8));
  }
  FastLED.show();
}

void przejsciaPetla(int odczytJasnosci) {
  FastLED.setBrightness(odczytJasnosci);
  for (int i = 0; i < 60; i++) {
    ledy[i] = CHSV(H, 255, 110);
    delay(10);
    H++;
    FastLED.show();
  }
}

void czujnikRev(long cm, int odczytJasnosci) {
  CRGB kolorCzujnik = CRGB::Blue;
  cm = constrain(cm, 2, 100);
  float ledIndex = map(cm, 100, 2, 0, iloscLedow - 1);
  if (ledIndex >= 15) {kolorCzujnik = CRGB::Green;}
  if (ledIndex >= 30) {kolorCzujnik = CRGB::Orange;}
  if (ledIndex >= 45) {kolorCzujnik = CRGB::Red;}

  for (int i = 0; i <= iloscLedow-1; i++) {
    FastLED.setBrightness(odczytJasnosci);
    if (i < ledIndex) {
      ledy[i] = kolorCzujnik;
    } else {
      ledy[i] = CRGB::Black;
    }
  }
  FastLED.show();
}

void sinusoida(int odczytKoloru, int odczytJasnosci) {
    FastLED.setBrightness(odczytJasnosci);
    float czas = millis() / 1000.0;  
    for (int i = 0; i < 60; i++) {
      float sinValue = sin(i * 0.2 + czas * 2.0); 
      int jasnosc = map(sinValue * 100, -100, 100, 10, 255);
      ledy[i] = Kolor(odczytKoloru); 
      ledy[i].nscale8(jasnosc);      
      FastLED.show();
      delay(30);  
    }
}

void losowyGradient(int odczytJasnosci) {
  CRGB color1 = CRGB(random8(1,256), random8(1,256), random8(1,256));
  CRGB color2 = CRGB(random8(1,256), random8(1,256), random8(1,256));
  CRGB color3 = CRGB(random8(1,256), random8(1,256), random8(1,256));
  CRGB color4 = CRGB(random8(1,256), random8(1,256), random8(1,256));
  fill_gradient_RGB(ledy, 60, color1, color2, color3, color4);
  FastLED.setBrightness(odczytJasnosci);
  FastLED.show();
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(analogMicPin, INPUT);
  pinMode(digitalMicPin, INPUT);
  EEPROM.begin(EEPROM_SIZE);
  wyborTrybu = EEPROM.read(EEPROM_TRYB);
  odczytKoloru = EEPROM.read(EEPROM_KOLOR);
  odczytJasnosci = EEPROM.read(EEPROM_JASNOSC);
  r = EEPROM.read(3);
  g = EEPROM.read(4);
  b = EEPROM.read(5);
  if (wyborTrybu > 13) EEPROM.write(EEPROM_TRYB, poczatkowyTryb);
  if (odczytKoloru > 9) EEPROM.write(EEPROM_KOLOR, poczatkowyKolor);
  if (odczytJasnosci > 110) EEPROM.write(EEPROM_JASNOSC, poczatkowaJasnosc);
  samplingPeriod = round(1000000.0 / SAMPLING_FREQUENCY);
  analogReadResolution(12);
  FastLED.addLeds<WS2812B, pinDanych, GRB>(ledy, iloscLedow);
  FastLED.setBrightness(poczatkowaJasnosc);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  uint8_t Sinus1 = beatsin8(30, 0, 59, 0);
  uint8_t Sinus2 = beatsin8(30, 0, 59, 85);
  uint8_t Sinus3 = beatsin8(30, 0, 59, 170);
  ArduinoCloud.update();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long droga = pulseIn(echoPin, HIGH);
  long cm = droga/29/2;
  ArduinoCloud.update();
  for (int i = 0; i < SAMPLES; i++) {
    microSeconds = micros();
    vReal[i] = analogRead(34);
    vImag[i] = 0;              
    while (micros() < (microSeconds + samplingPeriod)) {}
  }
  FFT.dcRemoval();
  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HANN, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(vReal, vImag, SAMPLES);
  int maxIndex = 0;
  double maxVal = 0;
  for (int i = 1; i < SAMPLES / 2; i++) {
      if (vReal[i] > maxVal) {
          maxVal = vReal[i];
          maxIndex = i;
      }
  }
  double peak = ((maxIndex * SAMPLING_FREQUENCY) / SAMPLES);
  ArduinoCloud.update();
  int prevKolor = EEPROM.read(EEPROM_KOLOR);
  int prevJasnosc = EEPROM.read(EEPROM_JASNOSC);
  int prevTryb = EEPROM.read(EEPROM_TRYB);
  int prevR = EEPROM.read(3);
  int prevG = EEPROM.read(4);
  int prevB = EEPROM.read(5);
  ArduinoCloud.update();
  if (w) {
    ArduinoCloud.update();
    if (wyborTrybu == 14) {
      ArduinoCloud.update();
      trybPracy(prevTryb, prevKolor, prevJasnosc, cm); 
    }
    if (wyborTrybu == 19) {
      ledy[Sinus1] = CRGB::Red;
      ledy[Sinus2] = CRGB::Green;
      ledy[Sinus3] = CRGB::Blue;
      blur1d(ledy, 60, 172);
      fadeToBlackBy(ledy, 60, 10);
      FastLED.setBrightness(odczytJasnosci);
      FastLED.show();
    }
    ArduinoCloud.update();
    if (wyborTrybu == 21) {
      int level = map(peak, 50, 1500, 0, iloscLedow);
      for (int i = 0; i < 60; i++) {
        if (peak < 220) { 
          ledy[i] = CRGB::Red;
        } else if (peak < 429) {    
          ledy[i] = CRGB::Green;
        } else if (peak < 611) {     
          ledy[i] = CRGB::Blue;
        } else if (peak < 858){                    
          ledy[i] = CRGB::Purple;
        } else if (peak < 1072) {
          ledy[i] = CRGB::Yellow;
        } else if (peak < 1286) {
          ledy[i] = CRGB::White;
        } else if (peak < 1501) {
          ledy[i] = CRGB::Magenta;
        }
      }
      FastLED.setBrightness(odczytJasnosci);
      FastLED.show(); 
    }
    if (wyborTrybu != 21 && wyborTrybu != 19) {
      ArduinoCloud.update();
      trybPracy(wyborTrybu, odczytKoloru, odczytJasnosci, cm);
      if (wyborTrybu != prevTryb) EEPROM.write(EEPROM_TRYB, wyborTrybu);
      if (odczytKoloru != prevKolor) EEPROM.write(EEPROM_KOLOR, odczytKoloru);
      if (odczytJasnosci != prevJasnosc) EEPROM.write(EEPROM_JASNOSC, odczytJasnosci); 
      if (prevR != r) EEPROM.write(3, r);
      if (prevG != g) EEPROM.write(4, g);
      if (prevB != b) EEPROM.write(5, b);
      ArduinoCloud.update();
    }
  }
  else {
    ArduinoCloud.update();
    FastLED.clear();
    FastLED.show();
  }
  
  // Serial.print("Dominująca częstotliwość: ");
  // Serial.print(peak);
  // Serial.print(" Hz\t");
  // Serial.println(level);

  // Serial.print("Odczyt: ");
  // Serial.print(droga);
  // Serial.print("us \t odleglosc: ");
  // Serial.print(cm);
  // Serial.print(" cm\n");
  
  // Serial.print("EEPROM: ");
  // Serial.print('\t');
  // Serial.print(EEPROM.read(EEPROM_TRYB));
  // Serial.print('\t');
  // Serial.print(EEPROM.read(EEPROM_KOLOR));
  // Serial.print('\t');
  // Serial.print(EEPROM.read(EEPROM_JASNOSC));
  // Serial.print('\t');
  
  // Serial.print(EEPROM.read(3));
  // Serial.print('\t');
  // Serial.print(EEPROM.read(4));
  // Serial.print('\t');
  // Serial.print(EEPROM.read(5));
  // Serial.print('\n');
  
  // Serial.print("Kolor: ");
  // Serial.print(odczytKoloru);
  // Serial.print("\tJasność: ");
  // Serial.print(odczytJasnosci);
  // Serial.print("\tTryb: ");
  // Serial.println(wyborTrybu);
  
  ArduinoCloud.update();
  delay(20);
}

void onOdczytJasnosciChange() {
  Serial.print("[Cloud] odczytJasnosci zmieniono na: ");
  Serial.println(odczytJasnosci);
}

void onOdczytKoloruChange() {
  Serial.print("[Cloud] odczytKoloru zmieniono na: ");
  Serial.println(odczytKoloru);
}

void onWyborTrybuChange() {
  Serial.print("[Cloud] wyborTrybu zmieniono na: ");
  Serial.println(wyborTrybu);
}

void onWChange() {
  Serial.print("[Cloud] w zmieniono na: ");
  Serial.println(w);
}

void onErgiebeChange()  {
  ergiebe.getValue().getRGB(r, g, b);
}