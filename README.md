## Narzędzie sterujące mocą sygnału karty bezprzewodowej

Projekt zaliczeniowy laboratorium z przedmiotu Programowanie Sieciowe 2024 na Politechnice Poznańskiej, prowadzący: dr inż. Michał Kalewski.

## Sposób uruchomienia programu
1. Kompilacja: `gcc -Wall ./wifi_card_power_manager.c -o ./wifi_card_power_manager`
2. Uruchomienie: `sudo ./wifi_card_power_manager <interfejs_wifi>`

Plik `wifi_card_power_manager.c` załącza wszystkie inne pliki źródłowe, należy więc kompilować tylko ten plik.

## Zawartość plików źródłowych:
### globals.h
Plik nagłówkowy zawierający #define dla zmiennych globalnych, na podstawie których obliczana jest liniowa zależność mocy karty od obecnego sygnału. W celu dostosowania algorytmu na potrzeby użytku dla własnej bezprzewodowej karty sieciowej, należy dokonać pomiarów i sprawdzić wartości najsilniejszego i najsłabszego sygnału oraz dopuszczalnych wartości mocy karty.

### wifi_card_power_manager.c 
Główny plik programu zawierający wywołania pozostałych funkcji i obsługujący flow programu. Zawiera nieskończoną pętlę, w której odczytywana jest obecna moc oraz sygnał, następnie obliczana jest nowa moc karty według liniowej zależności, na podstawie wartości podanych w pliku nagłówkowym `globals.h`

### calculations.c
Zawiera funkcje obsługujące logikę programu: odczytanie obecnych wartości mocy i sygnału karty, funkcję mapującą dla zdefiniowanych zmiennych globalnych z pliku `globals.h`, funkcję obliczającą następną wartość mocy dla podanego sygnału oraz funkcję wykonującą system call w celu zmiany mocy karty sieciowej.

### pretty_print.c
Funkcja wypisująca w terminalu obecne wartości mocy i sygnału. Przyjmuje wskaźnik do pliku, w przypadku podania wskaźnika `stdout` funkcja co odświeżenie będzie wypisywała nowe wartości (działanie jak komenda `watch`) z dodatkowymi paskami stanu, wizualizującymi obecne poziomy w odniesieniu do całkowitych poziomów. W przypadku przekazania wskaźnika do pliku innego niż `stdout` funkcja do pliku zapisuje wartości mocy i sygnału linia po linii.
