# Schemat połączeń - ESP32 LED Blinking

## GPIO 2 - Rekomendowany pin dla diody LED

### Dlaczego GPIO 2?
1. **Wbudowana dioda LED** - Większość płytek ESP32 Dev Module ma wbudowaną diodę LED podłączoną do GPIO 2
2. **Bezpieczny do użycia** - GPIO 2 nie jest używany do bootowania (w przeciwieństwie do GPIO 0, 12, 15)
3. **Łatwy dostęp** - Dostępny na standardowym złączu pinowym
4. **Testowany** - Powszechnie używany w przykładowych projektach

## Schemat połączenia - Wbudowana dioda LED

```
┌─────────────────────────────┐
│      ESP32 Dev Module       │
│                             │
│  [GPIO 2] ──→ Built-in LED │
│                             │
│          [GND]              │
│          [3V3]              │
│          [USB]──── USB Cable│
└─────────────────────────────┘
```

**Uwaga:** Wbudowana dioda LED nie wymaga żadnych dodatkowych połączeń!

## Schemat połączenia - Zewnętrzna dioda LED

### Opcja 1: Standard (Anoda do GPIO)

```
ESP32                        Componenty                  
                                                         
GPIO 2 ──────┬──────→ [+|LED|-] ──────→ [Rezystor 220Ω] ──────→ GND
             │                                                        
          (Wyjście)        (Anoda/Katoda)                            
```

### Schemat szczegółowy:

```
┌─────────────────┐
│    ESP32        │
│                 │
│  GPIO 2 ◄─┐    │     ┌─────┐      ┌──────────┐
│           │    │────→│ ►── │─────→│ 220Ω    │─────→ GND
│           │    │     └─────┘      └──────────┘
│  (Pin 24) └─────┘    LED           Resistor
│                 │    (Anoda→Katoda)
│  GND ───────────┼──────────────────────────────────→ GND
│  3V3            │
│  USB ═══════════╪═ USB Cable
└─────────────────┘
```

### Parametry:
- **Napięcie zasilania GPIO:** 3.3V
- **Maksymalny prąd GPIO:** 40mA (zalecane max 20mA)
- **Spadek napięcia na LED:** ~2V (czerwona LED)
- **Rezystor:** 220Ω
- **Prąd przez LED:** (3.3V - 2V) / 220Ω ≈ 6mA (bezpieczny)

## Obliczenia rezystora

### Wzór:
```
R = (Vcc - Vled) / Iled

gdzie:
Vcc  = 3.3V (napięcie zasilania GPIO)
Vled = 2.0V (spadek napięcia na LED, zależy od koloru)
Iled = 0.01A (10mA - bezpieczny prąd dla LED)

R = (3.3V - 2.0V) / 0.01A = 130Ω

Używamy 220Ω (najbliższa standardowa wartość), co daje ~6mA
```

### Wartości spadku napięcia dla różnych kolorów LED:
- **Czerwona:** ~1.8-2.2V → Rezystor: 220Ω
- **Żółta:** ~2.0-2.2V → Rezystor: 220Ω  
- **Zielona:** ~2.0-3.0V → Rezystor: 220Ω
- **Niebieska:** ~3.0-3.4V → Rezystor: 100Ω lub 220Ω
- **Biała:** ~3.0-3.4V → Rezystor: 100Ω lub 220Ω

## Alternatywne piny GPIO

Jeśli GPIO 2 jest zajęty, możesz użyć innych pinów:

### Zalecane piny:
- **GPIO 5** - Bezpieczny, często używany
- **GPIO 18** - Bezpieczny
- **GPIO 19** - Bezpieczny
- **GPIO 21** - Bezpieczny
- **GPIO 22** - Bezpieczny
- **GPIO 23** - Bezpieczny

### Piny, których należy unikać:
- **GPIO 0** - Używany do bootowania (przycisk BOOT)
- **GPIO 1** - TX UART (port szeregowy)
- **GPIO 3** - RX UART (port szeregowy)
- **GPIO 6-11** - Podłączone do pamięci Flash (nie używać!)
- **GPIO 12** - Używany podczas bootowania
- **GPIO 15** - Używany podczas bootowania

## Fizyczne podłączenie - Krok po kroku

### Materiały:
1. ESP32 Dev Module C Kit
2. Płytka stykowa (breadboard)
3. Dioda LED (5mm)
4. Rezystor 220Ω (czerwony-czerwony-brązowy)
5. Kable połączeniowe (2 szt)

### Kroki:

1. **Umieść ESP32** na płytce stykowej
2. **Podłącz anodę LED** (+, dłuższa nóżka) do GPIO 2 przez kabel
3. **Podłącz katodę LED** (-, krótsza nóżka) do jednej nóżki rezystora
4. **Podłącz drugą nóżkę rezystora** do GND na ESP32
5. **Podłącz USB** do zasilania i programowania

### Weryfikacja połączeń:
- [ ] LED podłączona we właściwej polaryzacji (anoda do GPIO)
- [ ] Rezystor 220Ω w szeregu z LED
- [ ] Połączenie z GND
- [ ] USB podłączone

## Rozwiązywanie problemów

### LED nie świeci się:
1. **Sprawdź polaryzację** - anoda (+) do GPIO 2, katoda (-) do GND
2. **Sprawdź rezystor** - powinien być 220Ω
3. **Sprawdź połączenia** - upewnij się, że kable są dobrze podłączone
4. **Sprawdź kod** - upewnij się, że LED_PIN = 2

### LED świeci się zbyt słabo:
1. **Zmniejsz wartość rezystora** - spróbuj 100Ω lub 150Ω
2. **Sprawdź napięcie zasilania** - powinno być 3.3V na GPIO

### LED świeci się ciągle (nie miga):
1. **Sprawdź kod** - upewnij się, że program został poprawnie wgrany
2. **Sprawdź monitor portu szeregowego** - czy wyświetlają się komunikaty?
3. **Zresetuj ESP32** - naciśnij przycisk RESET

## Przykładowe zdjęcie podłączenia

```
     ┌──USB──┐
     │       │
  ┌──┴───────┴──┐
  │   ESP32     │
  │             │
  │ [2]◄────────┼─────► + LED - ►──[220Ω]──► GND
  │             │
  │ [GND]───────┼──────────────────────────► GND
  └─────────────┘
```

## Bezpieczeństwo

⚠️ **WAŻNE:**
- Nigdy nie podłączaj LED bezpośrednio do GPIO bez rezystora!
- Maksymalny prąd z pojedynczego GPIO: 40mA (zalecane max 20mA)
- Maksymalny łączny prąd ze wszystkich GPIO: 200mA
- Zawsze używaj rezystora ograniczającego prąd

## Dodatkowe zasoby

- [ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
