# hackathon-consensus
Prosty program do sterowania diodami LED na procesorze ESP32

## Opis projektu

Program do sterowania diodą LED na płytce ESP32 Dev Module C Kit. Program powoduje mruganie diody LED podłączonej do pinu GPIO 2 (wbudowana dioda LED na większości płytek ESP32).

## Specyfikacja

- **Platforma:** ESP32 Dev Module C Kit
- **Framework:** Arduino
- **Język:** C/C++
- **Pin LED:** GPIO 2 (wbudowana dioda LED)
- **Częstotliwość mrugania:** 1 sekunda ON / 1 sekunda OFF
- **Komunikacja szeregowa:** 115200 baud

## Schemat podłączenia

### Opcja 1: Wbudowana dioda LED (najprostsza)
Większość płytek ESP32 Dev Module ma wbudowaną diodę LED na GPIO 2. Nie wymaga żadnych dodatkowych połączeń.

### Opcja 2: Zewnętrzna dioda LED
```
ESP32 GPIO 2 → Anoda LED (+) → Katoda LED (-) → Rezystor 220Ω → GND
```

**Alternatywne piny GPIO do wykorzystania:**
- GPIO 5, 18, 19, 21, 22, 23 (dowolny pin cyfrowy)

## Wymagania

### Sprzęt
- ESP32 Dev Module C Kit
- Kabel USB (microUSB lub USB-C w zależności od modelu)
- (Opcjonalnie) Dioda LED + rezystor 220Ω

### Oprogramowanie
- [PlatformIO](https://platformio.org/) - narzędzie do programowania ESP32
- Python 3.6 lub nowszy
- Sterowniki USB dla ESP32 (CP210x lub CH340)

## Instalacja i uruchomienie

### 1. Instalacja PlatformIO

#### Metoda 1: PlatformIO IDE (VS Code)
```bash
# Zainstaluj Visual Studio Code
# Następnie zainstaluj rozszerzenie PlatformIO IDE z marketplace
```

#### Metoda 2: PlatformIO Core (CLI)
```bash
pip install platformio
```

### 2. Sklonowanie repozytorium
```bash
git clone https://github.com/mkrzyzan/hackathon-consensus.git
cd hackathon-consensus
```

### 3. Kompilacja projektu
```bash
pio run
```

### 4. Wgranie programu na ESP32
```bash
# Podłącz ESP32 do komputera przez USB
pio run --target upload
```

### 5. Monitorowanie portu szeregowego
```bash
pio device monitor
```

Powinieneś zobaczyć:
```
ESP32 LED Blinking Program Started
LED connected to GPIO 2
LED ON
LED OFF
LED ON
LED OFF
...
```

## Konfiguracja

### Zmiana pinu LED
Edytuj plik `src/main.cpp` i zmień wartość `LED_PIN`:
```cpp
#define LED_PIN 5  // Zmień na dowolny dostępny pin GPIO
```

### Zmiana częstotliwości mrugania
Edytuj `BLINK_INTERVAL` (wartość w milisekundach):
```cpp
#define BLINK_INTERVAL 500  // 0.5 sekundy ON/OFF
```

## Testowanie

Szczegółowe informacje o testach manualnych i automatycznych znajdują się w pliku [TESTING.md](TESTING.md).

### Szybki test manualny
1. Wgraj program na ESP32
2. Obserwuj diodę LED - powinna migać co 1 sekundę
3. Otwórz monitor portu szeregowego i sprawdź komunikaty

## Struktura projektu

```
hackathon-consensus/
├── platformio.ini       # Konfiguracja PlatformIO
├── src/
│   └── main.cpp        # Główny program LED blinking
├── README.md           # Ten plik
└── TESTING.md          # Dokumentacja testów
```

## Rozwiązywanie problemów

### ESP32 nie jest wykrywany
1. Sprawdź czy zainstalowane są sterowniki USB (CP210x lub CH340)
2. Spróbuj innego kabla USB
3. Naciśnij przycisk BOOT podczas wgrywania programu

### Dioda nie miga
1. Sprawdź czy wybrałeś poprawny pin GPIO
2. Jeśli używasz zewnętrznej diody, sprawdź polaryzację
3. Sprawdź połączenia i rezystor (220Ω)

### Błędy kompilacji
```bash
# Wyczyść projekt i spróbuj ponownie
pio run --target clean
pio run
```

## Licencja

Ten projekt jest dostępny na licencji MIT.

## Autor

Projekt utworzony w ramach hackathonu.

## Wsparcie

W razie problemów otwórz issue na GitHubie.
