/* 
 * File:   ScriptLine.cpp
 * Author: laurasirventcollado
 * 
 * Created on 22 de enero de 2014, 11:31
 */

#include "../headers/ScriptLine.h"

ScriptLine::ScriptLine() {
}

ScriptLine::ScriptLine(Type t, Vector3f p, std::wstring c, std::string aF){
    
    type = t;
    point = p;
    content = c;
    audioFile = aF;
    read = false;
    arrived = false;
}

ScriptLine::ScriptLine(const ScriptLine& orig) {
}

ScriptLine::~ScriptLine() {
}

