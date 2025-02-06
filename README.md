# Logger
 
🔹 Kluczowe funkcjonalności \
✔️ Logowanie na różnych poziomach (INFO, WARNING, ERROR, DEBUG). \
❌ Obsługa wielu wyjść (plik, konsola, przyszłościowo: baza danych). \
✔️ Rotacja logów – ograniczenie rozmiaru pliku (np. 5 MB) + archiwizacja. \
✔️ Konfigurowalne formatowanie logów (data, czas, typ logu, wątek). \
✔️ Możliwość zmiany poziomu logowania w trakcie działania. \
❌ Asynchroniczne logowanie (opcja: zapis w osobnym wątku). \
❌ Bezpieczeństwo wątkowe – kilku wątków może logować jednocześnie.

CI/CD Status 🔨 

|          	|                                                                                                      Status                                                                                                     	|
|:--------:	|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:	|
|   Build  	|                                                            ![Build Status](https://github.com/SzumekPL/Logger/actions/workflows/build.yml/badge.svg)                                                            	|
|   Tests  	|                                                         ![Tests Status](https://github.com/SzumekPL/Logger/actions/workflows/google_tests.yml/badge.svg)                                                        	|
| Coverage 	| ![Coverage %](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fraw.githubusercontent.com%2FSzumekPL%2FLogger%2Fgh-pages%2Fcoverage%2Fcoverage.json&query=%24.message&label=Coverage&color=%24.color) 	|

TO DO: \
Artefakty / cache żeby nie pobierać za każdym razem gtestow i instalowac

# Kompilacja i uruchamianie

Aby skompilować i uruchomić projekt, użyj poleceń `make` w terminalu:

## Podstawowe komendy:

```bash
make all
```
Kompiluje cały projekt.

```bash
make run
```
Uruchamia skompilowaną aplikację.

```bash
make clean
```
Usuwa pliki wynikowe i binaria.

## Kompilacja testów:

```bash
make test
```
Kompiluje testy.

```bash
make run_tests
```
Uruchamia testy.

```bash
make clean
```
Usuwa pliki wynikowe testów.

## Wybór kompilatora:

Domyślnie używany jest `g++`, ale można zmienić kompilator na `clang++` poprzez:

```bash
make all CL=1
```
lub
```bash
make test CXX=clang++
```

Możesz przy użyciu CXX=kompilator wybrać dowolny zainstalowany kompilator, nie ma gwarancji że będzie działało!
