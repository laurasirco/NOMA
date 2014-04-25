/* 
 * File:   Noma.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:26
 */

#ifndef NOMA_H
#define	NOMA_H
#include "Character.h"

class Noma : public Character {
public:
    Noma(Vector3f pos = Vector3f(0,0,0));
    Noma(const Noma& orig);
    virtual ~Noma();
    void update();
    void accelerate(float ax, float ay, float az);
    void deccelerate();
    void jump();
    void elevate();
    void fall();
    void setActivity (float newActivity) { if(newActivity < 100 && newActivity > 0) activity = newActivity; }
    void setConversacion (float newConversation) { if(newConversation < 100 && newConversation > 0) conversation = newConversation; }
    void setTemperament (float newTemperament) { if(newTemperament < 100 && newTemperament > 0) temperament = newTemperament; }
    void setConfidence (float newConfidence) { if(newConfidence < 100 && newConfidence > 0) confidence = newConfidence; }
    float getActivity () { return activity; }
    float getConversation () { return conversation; }
    float getTemperament () { return temperament; }
    float getConfidence () { return confidence; }
    bool isInteracting(){ return interacting; }
    void setInteracting(bool i){ interacting = i; }
    void setWalking(bool i){ walking = i; }
    bool isWalking(){ return walking; }
    bool canTravel(){ return travel; }
    void setCanTravel(bool t){ travel = t; }
    
    void setInitPosition(Vector3f p);
 
private:
    float activity;
    float conversation;
    float temperament;
    float confidence;
    float auxFrame;
    bool interacting;
    bool walking;
    bool travel;
    bool jumping;
    
    
};

#endif	/* NOMA_H */

