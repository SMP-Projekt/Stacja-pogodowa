# Stacja-pogodowa


<b>Wymagania:</b>
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

<b>--------------------------------------------------------------------------------------------------------------------------------</b>

<b>I. Tytuł: Stacja pogodowa</b>  
  
<b>II. Autorzy: /b>  
  
<b>III. Założenia projektowe:</b>  
1.	Odczyt danych z Nucleo Weather przez I2C po przyciśnięciu przycisku na stronie internetowej, w sposób ciągły co 10 sekund lub jednorazowo. Gdy przestaniemy pobierać dane, układ przejdzie w tryb uśpienia.  
2.	Zapis pomiarów w mikrokontrolerze.  
3.	Przesłanie danych przez UART do modułu ESP z wifi.  
4.	Pobranie danych przy użyciu wi-fi przez urządzenie zewnętrzne.  
5.	Prezentacja pomiarów na stronie internetowej (HTML).  
  
<b>IV.</b>  
 a) Wykorzystane protokoły:  
•	UART,  
•	I2C.  
  
b) Wykorzystane układy:  
•	płytka Kinetis FRDM-KL46Z,  
•	KA Nucleo Weather (stacja pogodowa),  
•	moduł ESP2866.  
  
c)  Wykorzystane peryferia:  
•	timery,  
•	tryb uśpienia.  
  
<b>V. Schemat blokowy:</b>  
![](Schemat blokowy.png)
  
<b>VI. Kamienie milowe:</b>  
1. Połączenie mikrokontrolera z zestawem czujników. (18-24 grudnia)  
2. Połączenie mikrokontrolera z modułem esp8266. (8-14 stycznia)  
3. Strona internetowa, zakończenie projektu. (22-26 stycznia)  

  
