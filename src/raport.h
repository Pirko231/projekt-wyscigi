#pragma once

#include <fstream>
#include <string>



//tworzymy obiekt typu raport aby logowac wczytywanie z plikow
class Report
{
public:
    Report() = default;
    //otwiera plik o podanej nazwie
    void open(std::string _filename = "bootLog.txt") {this->file.open(_filename, std::ios::app); this->fileName = _filename;}

    //wypisuje wiadomosc do pliku
    //jezeli pliku nie uda sie otworzyc rzuca wyjatek 'FileCouldNotOpen'
    void logMessage(std::string _message);
    
    //dodaje entry do pliku.
    //_entry to nazwa wpisu czyli np. 'wczytywanie czcionki nr 1'
    //_status to zapisanie czy operacja sie udala
    //jesli nie uda sie otworzyc pliku rzuca wyjatek 'FileCouldNotOpen'
    void addEntry(std::string _entry, bool _status);

    //zwraca czy wszystkie operacje od otwarcia pliku zakoncyly sie powodzeniem.
    bool getStatus() const {return this->status;}
    
    //zamyka obecny plik. Zawsze wywolywac po otwarciu pliku
    void close() {this->file.close(); this->status = true;}

    //awaryjne zamkniecie pliku
    ~Report();
private:
    //plik
    std::fstream file;

    //status operacji w raporcie
    bool status{true};

    //nazwa pliku
    std::string fileName;
};

//kompatybilnosc wsteczna, lepiej przerzucic sie na Report
using Raport = Report;

//zdefiniowane w raport.h
//ten wyjatek oznacza ze plik o nazwie (funkcja what()) nie mogl sie otworzyc
struct FileCouldNotOpen
{
    FileCouldNotOpen() {this->fileName = "FILENAME-NOT-SPECIFIED";}
    FileCouldNotOpen(std::string _filename) {this->fileName = _filename;}
    //zwraca jaki plik nie mogl sie otworzyc
    const std::string what() const {return this->fileName;}
    
    std::string fileName;
};