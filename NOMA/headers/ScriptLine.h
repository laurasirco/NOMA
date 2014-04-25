/* 
 * File:   ScriptLine.h
 * Author: laurasirventcollado
 *
 * Created on 22 de enero de 2014, 11:31
 */

#ifndef SCRIPTLINE_H
#define	SCRIPTLINE_H
#include "BaseGameEntity.h"

class ScriptLine {
public:
    
    enum Type{ Narrator, Citizen, Irrelevant, Place };
    
    ScriptLine();
    ScriptLine(Type t, Vector3f p, std::wstring c, std::string aF);
    ScriptLine(const ScriptLine& orig);
    virtual ~ScriptLine();
    
    void setRead(bool r){ read = r; }
    std::wstring getContent(){ return content; }
    std::string getAudioFile(){ return audioFile; }
    Vector3f getPoint(){ return point; }
    bool isRead(){ return read; }
    Type getType(){ return type; }
    bool hasArrived(){ return arrived; }
    void setArrived(bool a){ arrived = a;}
private:
    Type type;
    Vector3f point;
    std::wstring content;
    std::string audioFile;
    bool read;
    bool arrived;
};

#endif	/* SCRIPTLINE_H */

