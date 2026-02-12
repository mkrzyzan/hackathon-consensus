# Testy dla programu ESP32 LED Blinking

## Testy Manualne (Manual Tests)

### Test 1: Podstawowe mruganie LED
**Cel:** Sprawdzenie czy dioda LED miga regularnie

**Wymagania:**
- ESP32 Dev Module C Kit
- Kabel USB do połączenia z komputerem
- (Opcjonalnie) Zewnętrzna dioda LED z rezystorem 220Ω

**Kroki:**
1. Podłącz ESP32 do komputera przez USB
2. Wgraj program na płytkę używając PlatformIO
3. Obserwuj diodę LED na GPIO 2 (wbudowana dioda)

**Oczekiwany rezultat:**
- Dioda LED powinna migać regularnie
- Okres mrugania: 1 sekunda ON, 1 sekunda OFF
- Wizualna potwierdzenie działania

**Status:** ✅ PASS / ❌ FAIL

---

### Test 2: Weryfikacja komunikatów szeregowych
**Cel:** Sprawdzenie poprawności logowania przez port szeregowy

**Wymagania:**
- ESP32 podłączone do komputera
- Monitor portu szeregowego (115200 baud)

**Kroki:**
1. Otwórz monitor portu szeregowego: `pio device monitor`
2. Zresetuj płytkę ESP32
3. Obserwuj komunikaty

**Oczekiwany rezultat:**
```
ESP32 LED Blinking Program Started
LED connected to GPIO 2
LED ON
LED OFF
LED ON
LED OFF
...
```

**Status:** ✅ PASS / ❌ FAIL

---

### Test 3: Test z zewnętrzną diodą LED
**Cel:** Sprawdzenie działania z zewnętrzną diodą

**Wymagania:**
- ESP32 Dev Module
- Dioda LED
- Rezystor 220Ω
- Kable połączeniowe

**Schemat połączenia:**
```
GPIO 2 → Anoda LED → Katoda LED → Rezystor 220Ω → GND
```

**Kroki:**
1. Podłącz diodę LED zgodnie ze schematem
2. Wgraj program na płytkę
3. Obserwuj zewnętrzną diodę LED

**Oczekiwany rezultat:**
- Zewnętrzna dioda LED miga regularnie
- Okres: 1s ON, 1s OFF

**Status:** ✅ PASS / ❌ FAIL

---

### Test 4: Test przy różnych napięciach zasilania
**Cel:** Sprawdzenie stabilności działania

**Kroki:**
1. Test z zasilaniem przez USB (5V)
2. Test z zewnętrznym zasilaczem (3.3V - 5V)

**Oczekiwany rezultat:**
- Program działa stabilnie przy obu napięciach
- Częstotliwość mrugania nie zmienia się

**Status:** ✅ PASS / ❌ FAIL

---

## Testy Automatyczne (Automated Tests)

### Test 1: Test jednostkowy logiki mrugania (dla symulatorów)
**Opis:** Test sprawdza czy stan GPIO zmienia się prawidłowo

**Pseudokod testu:**
```cpp
TEST(LEDBlinkTest, ToggleState) {
    // Setup
    int pin = 2;
    pinMode(pin, OUTPUT);
    
    // Test HIGH
    digitalWrite(pin, HIGH);
    ASSERT_EQ(digitalRead(pin), HIGH);
    
    // Test LOW
    digitalWrite(pin, LOW);
    ASSERT_EQ(digitalRead(pin), LOW);
}
```

### Test 2: Test timingu mrugania
**Opis:** Test mierzy rzeczywisty czas między zmianami stanu

**Pseudokod:**
```cpp
TEST(LEDBlinkTest, TimingAccuracy) {
    unsigned long startTime = millis();
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(LED_PIN, LOW);
    unsigned long elapsed = millis() - startTime;
    
    // Tolerancja +/- 50ms
    ASSERT_NEAR(elapsed, BLINK_INTERVAL, 50);
}
```

### Test 3: Test inicjalizacji portu szeregowego
**Opis:** Sprawdzenie czy komunikacja szeregowa została poprawnie zainicjalizowana

**Implementacja:**
- Użycie biblioteki do testowania embedded (np. Unity)
- Test sprawdza czy Serial.begin() wykonało się poprawnie
- Weryfikacja prędkości transmisji (115200 baud)

---

## Propozycje automatyzacji testów

### 1. Wykorzystanie PlatformIO Testing Framework
Dodaj do `platformio.ini`:
```ini
[env:native]
platform = native
test_framework = unity
```

### 2. Testy integracyjne z wykorzystaniem symulatorów
- **Wokwi Simulator** - symulator online ESP32
- **QEMU** - emulator ARM dla ESP32
- Umożliwiają automatyczne testy bez fizycznego sprzętu

### 3. CI/CD Pipeline
Możliwa konfiguracja z GitHub Actions:
```yaml
- Kompilacja kodu dla ESP32
- Uruchomienie testów jednostkowych na native platform
- Weryfikacja czy projekt się kompiluje bez błędów
```

### 4. Testy sprzętowe z użyciem platformy testowej
- Automatyczne wgrywanie firmware przez USB
- Monitorowanie portu szeregowego
- Parsing logów i weryfikacja oczekiwanych komunikatów
- Użycie sensora światła do weryfikacji mrugania LED

---

## Podsumowanie

### Testy manualne - zalety:
✅ Proste do wykonania  
✅ Nie wymagają specjalnego środowiska  
✅ Wizualna weryfikacja działania  
✅ Bezpośrednia interakcja ze sprzętem  

### Testy automatyczne - zalety:
✅ Powtarzalne  
✅ Szybkie wykonanie  
✅ Integracja z CI/CD  
✅ Wczesne wykrywanie błędów  

### Zalecenia:
1. Rozpocznij od testów manualnych (Test 1 i 2)
2. Zaimplementuj testy automatyczne dla logiki biznesowej
3. Użyj CI/CD do automatycznej kompilacji
4. Dla produkcji rozważ automatyczne testy sprzętowe
