# Projekt: Replika ładunku wybuchowego C4 / akcesoria ASG

## Opis projektu

Projekt ten to system rozbrajania bomby oparty na mikrokontrolerze Arduino. Umożliwia użytkownikowi wprowadzenie kodu rozbrojenia, ustawienie czasu detonacji oraz rozpoczęcie odliczania. Po upływie czasu, jeśli kod rozbrojenia jest poprawny, bomba zostaje rozbrojona. W przeciwnym razie następuje eksplozja. W trakcie działania systemu używany jest buzzer oraz wyświetlacz LCD, który pokazuje aktualny stan.

## Wykorzystane elementy:

- **Arduino** (mikrokontroler)
- **Wyświetlacz LCD** (I2C)
- **Klawiatura matrycowa** (4x4)
- **Rozszerzenie PCF8574** do obsługi dodatkowych pinów
- **Głośnik/buzzer**
- Pozostała elektronika

## Instrukcja obsługi

### 1. Wprowadzenie kodu rozbrojenia
Po uruchomieniu systemu, na wyświetlaczu LCD pojawi się komunikat „Kod Rozbrojenia:”. Użytkownik wprowadza czterocyfrowy kod za pomocą klawiatury matrycowej. Każda naciśnięta cyfra będzie wyświetlana na ekranie w postaci *.

### 2. Ustawienie czasu detonacji
Po wprowadzeniu kodu rozbrojenia, użytkownik ustawia czas detonacji w formacie GG:MM:SS, gdzie GG to godziny, MM to minuty, a SS to sekundy. Czas ten jest również wprowadzany za pomocą klawiatury matrycowej.

### 3. Odliczanie
Po zapisaniu czasu, system przechodzi do odliczania, wyświetlając pozostały czas do detonacji. Buzzer zaczyna wydawać dźwięki ostrzegawcze, gdy czas do detonacji jest bliski końca.

### 4. Rozbrojenie bomby
Jeżeli użytkownik wprowadzi poprawny kod rozbrojenia, a czas nie przekroczy godziny, bomba zostanie rozbrojona. Na wyświetlaczu pojawi się komunikat „Bomba rozbrojona”.

### 5. Eksplozja
Jeśli kod rozbrojenia jest niepoprawny lub czas detonacji minął, bomba wybucha. Na wyświetlaczu pojawi się komunikat „Bomba wybuchła”. W trakcie wybuchu emitowane są dźwięki alarmowe.

## Struktura projektu

### 1. Kod Rozbrojenia
Przechowywany w tablicy `kodRozbrojenia[4]`. Użytkownik wprowadza czterocyfrowy kod.

### 2. Czas Detonacji
Przechowywany w tablicy `czas[6]`, zdefiniowane jako godziny, minuty i sekundy.

### 3. Wyświetlacz LCD
Używany do wyświetlania komunikatów o stanie systemu, w tym kodu rozbrojenia, czasu detonacji oraz stanu bomby.

### 4. Klawiatura Matrycowa
Używana do wprowadzania kodu rozbrojenia i ustawiania czasu detonacji.

### 5. Buzzer
Używany do wydawania dźwięków alarmowych w czasie odliczania oraz po wybuchu bomby.

## Zdjęcie projektu

![Opis zdjęcia](link_do_zdjęcia.jpg)

## Link do filmu na YouTube

Zobacz film prezentujący projekt na YouTube:  
[Link do filmu](https://www.youtube.com/watch?v=przykladowylink)

