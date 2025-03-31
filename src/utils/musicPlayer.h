#pragma once

#include <SFML/Audio.hpp>
#include <array>
#include "../game/settings.h"

namespace util
{

class MusicPlayer
{
public:
    static void init(Settings* _settings) {settings = _settings;}
    static MusicPlayer& get()
    {
        static MusicPlayer mPlayer;
        return mPlayer;
    }
    void play();
    //void setMusic(sf::String fileName);
private:
    static Settings* settings;

    MusicPlayer();
    sf::Music music;
    std::array<sf::String, 3> songs;
    int currentSong{0};
};

};