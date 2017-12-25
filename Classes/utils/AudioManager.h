#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"

class AudioManager
{
private:
    static bool soundEnabled;

    AudioManager() {}

public:
    static void muteSounds();
    static void unmuteSounds();
    static void playBackgroundMusic(const std::string& filePath, bool loop, float volume);
    static void playSoundEffect(const std::string& filePath, float volume);
    static void pause();
    static void resume();
    static void end();
};

#endif // __AUDIO_MANAGER_H__
