#include "musicPlayer.h"

Settings* util::MusicPlayer::settings{nullptr};

util::MusicPlayer::MusicPlayer()
{
    songs[0] = "resources/sounds/soundtrack1.wav";
    songs[1] = "resources/sounds/soundtrack2.wav";
    songs[2] = "resources/sounds/soundtrack3.wav";
}

void util::MusicPlayer::play()
{
    if (music.getStatus() == sf::Music::Status::Stopped)
    {
        if (currentSong < (int)songs.size() - 1)
            currentSong++;
        else
            currentSong = 0;
        music.openFromFile(songs[currentSong]);
    }
    
    music.setVolume((settings->getData()->mainVolume / 100.f) * (settings->getData()->musicVolume / 100.f) * 100.f);
    music.play();
}