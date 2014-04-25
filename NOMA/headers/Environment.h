/* 
 * File:   Environment.h
 * Author: laurasirventcollado
 *
 * Created on 18 de noviembre de 2013, 11:34
 */

#ifndef ENVIRONMENT_H
#define	ENVIRONMENT_H

#include <iostream>
#include "EnvState.h"
#include "Noma.h"


class Environment {
public:
    
    struct RGB{ 
        float r; 
        float g; 
        float b; 
        RGB(float r=0, float g=0, float b=0) : r(r), g(g), b(b) {}
    };
    
    Environment();
    Environment(const Environment& orig);
    virtual ~Environment();
    void update();
    void changeState(EnvState * newState);
    void setHour(int newHour) { hour = newHour; }
    void setWeather(std::string newWeather) { weather = newWeather; }
    void setMusic(std::string newMusic) { music = newMusic; }
    void setColor(std::string newColor, RGB c) { sColor = newColor; color = c;}
    std::string getWeather() { return weather; }
    std::string getMusic() { return music; }
    std::string getSColor() { return sColor; }
    RGB getColor(){ return color; }
    float getEnvNumber() { return envNumber; }
    void setEnvNumber(float newEnvNumber){ envNumber = newEnvNumber; }
    void incrementEnvNumber (float increment) { envNumber += increment; }
private:
    EnvState * currentState;
    float envNumber;
    float antEnvNumber;
    int hour;
    std::string weather;
    std::string music;
    std::string sColor;
    RGB color;
    Noma *noma;
    
};

#endif	/* ENVIRONMENT_H */

