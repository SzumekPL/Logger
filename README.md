# Logger
 
🔹 Kluczowe funkcjonalności \
✔️ Logowanie na różnych poziomach (INFO, WARNING, ERROR, DEBUG). \
❌ Obsługa wielu wyjść (plik, konsola, przyszłościowo: baza danych). \
❌ Asynchroniczne logowanie (opcja: zapis w osobnym wątku). \
✔️ Rotacja logów – ograniczenie rozmiaru pliku (np. 5 MB) + archiwizacja. \
❌ Konfigurowalne formatowanie logów (data, czas, typ logu, wątek). \
✔️ Możliwość zmiany poziomu logowania w trakcie działania. \
❌ Bezpieczeństwo wątkowe – kilku wątków może logować jednocześnie.

CI/CD Status 🔨 

Build: ![Build Status](https://github.com/SzumekPL/Logger/actions/workflows/build.yml/badge.svg)

Tests: ![Tests Status](https://github.com/SzumekPL/Logger/actions/workflows/tests.yml/badge.svg)

TO DO:
Wskaznik pokrycia testami
Napisac testy
Artefakty / cache żeby nie pobierać za każdym razem gtestow i instalowac
