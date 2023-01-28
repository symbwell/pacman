Autor: Oliwer Lisek - Studia N1 Informatyka, Nr albumu 33464.
Data spakowania 26.01.2023.

Instrukcja:
1. Po uruchomieniu określić ilośc wrogów - maksymalnie 20, minimalnie 1.
2. Oznaczenia:
	- P - gracz
	- M - potwór
	- * - owoc
3. Poruszanie się za pomocą W - góra, S - dół, A - lewo, D - prawo. 
4. Każdy owoc to 10 punktów.
5. Potwory poruszaja się wolniej od gracza (opóźnienie nieblokujące z użyciem zegara).
6. Po przegranej wynik jest zapisywany do pliku score wraz z datą oraz imieniem potwora, który nas zabił.
7. Imiona są pobierane z pliku names.txt. Można je dowolnie edytować. Ich ilość powinna być większa niż 20. 

WYMAGANIA PROGRAMOWAE:
1. Program został podzielony na pliki nagłówkowe *.h z deklaracjami o pliki *.c z definicjami.
2. Zastosowanie biblioteki string.h jest zaprezentowane w pliku monsters.c (Linia 153, użycie strdup()).
3. Struktury są zdefiniowane prawie w każdym pliku nagłówkowym *.h.
4. Zapis pliku znajduje się w pliku general.c (funkcja saveScoreToFile()). 
5. Odczyt z pliku znajduje się w pliku monsters.c (funkcja createMonsterNames()).
6. Struktura MonsterArray zawiera w sobie odniesienie do struktury Monster. Struktura Monster zawiera w sobie odniesienie do struktury MonsterName. Jest to zdefiniowane w pliku monsters.h
7. Uzycie calloc zaprezentowane np. w pliku player.c (funkcja getPlayer()). 
8. Uzycie malloc zaprezentowane np. w pliku monsters.c (funkcja getMonstersArray()).
9. Użycie realloc zaprezentowane w pliku monsters.c (funkcja addNewMonsterToArray()).
10. Uzycie structA** i A*** zaprezentowane w pliku monsters.c (funkcja createMonsterNames()).
11. Funkcje do zarządzania pamięcią w czasie wykonywania to np. addNewMonsterToArray, removeMonsterFromArray, generateNewMonster, getMonstersArray, destructMonsters.
12. Część argumentów jest pozabezpieczana z uzyciem const w pliku monsters.c (jako przykład).
 