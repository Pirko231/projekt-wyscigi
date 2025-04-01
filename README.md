# Wymagania:
CMake 2.27 lub wyzej

Konfiguracja (Windows, MSVC)

wejdz w terminalu do folderu gry

wpisz:
```
mkdir build
cd build
cmake ..
cmake --build .
```

Przejdz do folderu build/bin/Debug i odpal plik main.exe

# Jak używać:

Rozpoczynajac gre trafia się na ekran glowny.
Klikajac graj mozemy wybrac mapę. Mozna wybrac tylko mapy odblokowane.
Teraz wybieramy samochod. Mozna wybrac tylko odblokowany samochod.
Samochody / mapy odblokowuje sie za dobry czas przejazdu jakiejs mapy.
Jezeli chce sie jednak miec je wszystkie na start, to trzeba wpisac cheatcode w ustawieniach (aby wlaczyc ustawienia nacisnac escape)
cheatcodes:
```
ALLMAPS
ALLCARS
```

Aby ukonczyc wyscig nalezy przejechac 3 okrazenia. Na mapie nr 1 nie da sie wyjechac poza granice toru.
W innych mapach da sie wyjezdzac poza granice toru, a mapa poziomu 1 to prototyp gdzie widac jak chcielismy to zaimplementowac na wszystkich poziomach.

Po zakonczeniu wyscigu mozna wybrac nazwe i wyswietlany bedzie najlepszy czas okrazenia i wyscigu w tabeli wynikow.

## Tryb developera

aby wejsc w tryb developera nalezy dodac do pliku cmakelists.txt te linijki:
```
add_compile_definitions(HITBOXTEST)
add_compile_definitions(SPEEDTEST)
add_compile_definitions(MEMTRACKER)
```
Teraz:
   -hitboxy i checkpointy będą widzialne.
   -w plikach będa zbierane informacje o alokowanej i zwalnianej pamieci oraz czasie.

# Trochę o projekcie

## Plan projektu

Tutaj chce trochę opowiedziec o planie na projekt - gdzie moim zdaniem najlepiej zaczac patrzec:
   ```
   -Main.cpp, Program.h i Program.cpp - main sluzy glownie do pomiarow i w nim jest game loop. Program przygotowuje funkcje do gameLoop. Wlasciwie wszystko dzieje sie wlasnie w Program.
   -BodyFunction.h - jest tam szkielet każdej klasy do wyswietlania ekranu
   -MainMenu.h, LevelSelection.h, CarSelection.h - piersze trzy ekrany
      -/buttons - przyciski ktore zastosowalismy w pracy nad tymi ekranami (i nie tylko tymi)
   -Level.h - przygotowanie bazy pod rozne poziomy. Jest tam własciwie cala baza wyscigu.
      -/gameObjects - są tam przechowywane takie rzeczy jak hitboxy czy checkpointy
   -Klasy dziedziczace od level - tam jest tylko ustawienie hitboxow, danych o odblokowaniach i pozycjach startowych
   -Car.h - cała baza dla auta. Można by to było przebudowac aby tez dzialaly na tym boty
      -Player.h - komunikacja z klasą Car poprzez chroniony interfejs (protected)
      -Bot.h - pusty, ale dzialalby podobnie do klasy Player - porozumiewal by sie poprzez chroniony interfejs
      -/utils - duzo funkcji do poruszania sie auta
   -Settings.h, SettingsData.h, Cars.h:
      -Settings.h - interfejs ktory porozumiewa uzytkownikiem z programem
      -SettingsData.h - przechowywane są dane o odblokowaniach czy glosnosci dzwieku
      -Cars.h - przechowuje gracza (i boty gdyby były zrobione) oraz jego tekstury i statystyki
```
## Mniejsza zaalokowana pamiec:

Dzieki temu ze ekrany byly alokowane na heapie, mozna je bylo dynamicznie zwalniac (niestety nie udalo nam sie tego wprowadzic). Oznaczalo to by, ze gdyby ekran np. ekran glowny zostal przelaczony na inny ekran, to ekran glowny bylby usuwany (delete) a ekran na ktory sie przelaczamy bylby alokowany (new). Pozwalaoby to na o wiele mniejsze zuzycie pamieci przez program.
   
## Jak zaimplementowane byłyby przeszkody?

do implementacji przeszkod pomysl byl taki (baza juz zostala zrobiona):
   -w folderze gameObjects widac abstrakcyjna klase collidable. Ta klasa jest juz wykorzystywana do przechowywania hitboxow. W tym samym pojemniku gdzie sa przechowywane hitboxy trzymane by tez byly przeszkody - z pewnymi roznicami.
   -Przeszkody bylyby tworzone kiedy uzytkownik wybral poziom a potem usuwane. W takim pojemniku hitboxy by byly przechowywane przez caly czas dzialania projektu a przeszkody usuwane i dodawane dynamicznie.
   -Przeszkody dziedziczylyby od klasy Trap. Aby sprawdzic czy cos jest przeszkodą nalezaloby uzyc dynamic_cast. Wtedy zawsze na koniec wyscigu przeszkody bylyby usuwane.
   -Kiedy przeszkody dziedziczylyby od klasy trap to mogloby ich byc wiele roznych wariantow.
   -Przeszkody pojawialyby sie w specjalnei wyznaczonych kwadratach (sf::FloatRect), dzieki czemu nie pojawialyby sie poza mapą.
   -Kiedy gracz by wjezdzal w przeszkodę lub hitbox, wywolywana by byla wirtualna funkcja ktora bralaby poprzez referencje klasę Car lub jej statystki. (bylaby to funkcja zaprzyjazniona z Car). Kiedy wjezdzal w hitbox, ta funkcja nie mialaby implementacji, a kazdy rodzaj pulapki mialby swoją implementacje i modyfikowalby wyslany argument - Car.

## Pomysł na boty

Jeżeli chodzi o boty to niestety nie myslelismy o nich duzo. Na ten moment to byl nasz pomysl:
   -Boty mialyby wyznaczona trase w roznych punktach na mapie.
   -Boty podczas ruchu sprawdzaly by punkt do ktorego mają jechac, losowalyby inny punkt w poblizu i jechaly do tego wylosowanego (aby dodac losowosc)
   -Losowosc bylaby zmienjszana z poziomem trudnosci

# Od autorów:


