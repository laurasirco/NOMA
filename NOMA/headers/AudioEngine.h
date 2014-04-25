/* 
 * File:   AudioEngine.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:38
 */

#ifndef AUDIOENGINE_H
#define	AUDIOENGINE_H
#include "../Irrklang/include/irrKlang.h"
#include "Vectors.h"
#include <vector>

using namespace irrklang;

class AudioEngine {
public:
    AudioEngine();
    AudioEngine(const AudioEngine& orig);
    virtual ~AudioEngine();
    static AudioEngine* Instance();
    void play2DSound(ISoundSource* source) { engine->play2D(source);}
    void play2DSound(char * source) { engine->play2D(engine->getSoundSource(source)); }
    void play3DSound(ISoundSource* source, Vector3 positionSource) { engine->play3D(source, vec3df(positionSource.x,positionSource.x,positionSource.x)); }
    void play3DSound(ISoundSource* source, float x, float y, float z) { engine->play3D(source, vec3df(x,x,x)); }
    ISoundSource * addSound(char *source) { return engine->addSoundSourceFromFile(source); }
    bool isCreated() { return soundEngineCreated; }
    void loadCommonSounds();
    void play2DRandomSound(char * source, int n);
    void play2DUniqueSound(char * source);
    void deleteEngine() { engine->drop(); }
    
private:
    static AudioEngine* pinstance;
    ISoundEngine *engine;
    bool soundEngineCreated;
};

#endif	/* AUDIOENGINE_H */

