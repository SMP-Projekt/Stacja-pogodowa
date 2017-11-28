# Stacja-pogodowa


Wymagania:
1. Wykonanie projektu jest obowiązkowe.
2. Projekt powinien być wykonany na platformie FRDM-KL46Z lub podobnej (procesor ARM Cortex-M). Język programowania mikrokontrolera: C/C++.
3. Projekt musi zawierać:
wykorzystanie minimum jednego protokołu nie omawianego w trakcie ćwiczeń laboratoryjnych (np. I2C, SPI, 1-Wire, IRDA, ...),
podłączenie minimum jednego układu do platformy na której wykonywany jest projekt (np. MPU6500, DS18B20, DS1302, WS2812B, M24LR64E, ...),
skonfigurowanie i uruchomienie jednego z peryferiów nie wykorzystywanych w trakcie ćwiczeń laboratoryjnych (np. tryby uśpienia, DMA, AWIC, DAC, RTC, ...).
4. Ocena z projektu jest średnią ocen z następujących części: 
założenia projektowe,
algorytm działania,
dokumentacja projektu,
kod (jakość i komentarze),
opis i symulacja protokołu, wykorzystanego układu zewnętrznego oraz peryferium procesora,
repozytorium (porządek i aktualizacja),
efekt końcowy.
5. W trakcie wykonywania projektu należy przestrzegać ustalonych przez prowadzącego zajęcia terminów.


Założenia projektowe:
  1) Odczyt danych z Nucleo Weather przez I2C przy użyciu przerwań co 10 minut.
  2) Zapis pomiarów w mikrokontrolerze.
  3) Przesłanie danych przez UART do modułu ESP z wifi.
  4) Pobranie danych przy użyciu wi-fi przez urządrzenie zewnętrzne.
  5) Prezentacja pomiarów w na stronie internetowej (HTML).

<b>WŁADZA W RĘCE LUDU!!!</b> ddd
