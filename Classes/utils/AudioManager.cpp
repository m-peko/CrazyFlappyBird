#include "AudioManager.h"

#define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
#endif

USING_NS_CC;

bool AudioManager::soundEnabled = true;

void AudioManager::muteSounds()
{
    soundEnabled = false;

#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
#endif
}

void AudioManager::unmuteSounds()
{
    soundEnabled = true;

#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
#endif
}

void AudioManager::playBackgroundMusic(const std::string& filePath, bool loop, float volume)
{
#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::play2d(filePath, loop, volume);
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath.c_str(), loop);
#endif
}

void AudioManager::playSoundEffect(const std::string& filePath, float volume)
{
    if (soundEnabled)
    {
#if USE_AUDIO_ENGINE
        cocos2d::experimental::AudioEngine::play2d(filePath, false, volume);
#elif USE_SIMPLE_AUDIO_ENGINE
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(), false, 1.0, 0.0, volume);
#endif
    }
}

void AudioManager::pause()
{
#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

void AudioManager::resume()
{
#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

void AudioManager::end()
{
#if USE_AUDIO_ENGINE
    cocos2d::experimental::AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::end();
#endif
}