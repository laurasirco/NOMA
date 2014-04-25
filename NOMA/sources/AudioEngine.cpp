/* 
 * File:   AudioEngine.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:38
 */

#include "../headers/AudioEngine.h"
#include "../headers/Game.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>

AudioEngine::AudioEngine() {
    soundEngineCreated = false;
    engine = createIrrKlangDevice();
    if (engine) {
        soundEngineCreated = true;
        loadCommonSounds();
    }
}

AudioEngine* AudioEngine::pinstance = 0;

AudioEngine* AudioEngine::Instance() {

    if (pinstance == 0) {
        pinstance = new AudioEngine;
    }
    return pinstance;
}

AudioEngine::AudioEngine(const AudioEngine& orig) {
}

AudioEngine::~AudioEngine() {
}

void AudioEngine::loadCommonSounds() {
    ISoundSource *jump = addSound("Audio/jump1.ogg");
}

void AudioEngine::play2DRandomSound(char* source, int n) {
    int w = rand() % n + 1;
    std::stringstream file;
    file << source << w << ".ogg";
    std::string fileName = file.str();
    //cout << "random: "<< w <<endl;
    play2DSound((char *) fileName.c_str());
}

void AudioEngine::play2DUniqueSound(char* source) {
    ISoundSource* i = addSound(source);
    engine->play2D(i);

}