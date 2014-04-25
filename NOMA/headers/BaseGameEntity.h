/* 
 * File:   BaseGameEntity.h
 * Author: laurasirventcollado
 *
 * Created on 25 de octubre de 2013, 10:33
 */

#ifndef BASEGAMEENTITY_H
#define	BASEGAMEENTITY_H
#include <cmath>
#include <iostream>
#include <vector>
#include "TNode.h"

using namespace std;

struct Vector3f{
    float X;
    float Y;
    float Z;
    
    Vector3f(float X=0, float Y=0, float Z=0) : X(X), Y(Y), Z(Z) {}
    Vector3f& operator=(const Vector3f& a){
        X = a.X;
        Y = a.Y;
        Z = a.Z;
        return *this;
    }
    Vector3f operator+(const Vector3f& a) const{
        return Vector3f(a.X+X, a.Y+Y, a.Z+Z);
    }
    Vector3f operator-(const Vector3f& a) const{
        return Vector3f(X-a.X, Y-a.Y, Z-a.Z);
    }
    Vector3f operator*(const float i) const{
        return Vector3f(X*i, Y*i, Z*i);
    }
    Vector3f operator/(const float i) const{
        return Vector3f(X/i, Y/i, Z/i);
    }
    float magnitude(){
        return sqrt(X*X + Y*Y + Z*Z);
    }
    Vector3f normalize(){
        float magnitude = sqrt(X*X + Y*Y + Z*Z);
        return Vector3f(X/magnitude, Y/magnitude, Z/magnitude);
    }
    Vector3f truncate(float val){
        if(fabsf(X) > val){
            if(X > 0)
                X = val;
            else
                X = -val;
        }
        if(fabsf(Y) > val){
            if(Y > 0)
                Y = val;
            else
                Y = -val;
        }
        if(fabsf(Z) > val){
            if(Z > 0)
                Z = val;
            else
                Z = -val;
        }
        return Vector3f(X,Y,Z);
    }
    
    Vector3f heading(){
        
        if(X > 0) X = 1;
        else if(X < 0) X = -1;
        else X = 0;
        if(Y > 0) Y = 1;
        else if(Y < 0) Y = -1;
        else Y = 0;
        if(Z > 0) Z = 1;
        else if(Z < 0) Z = -1;
        else Z = 0;
        
        return Vector3f(X,Y,Z);
    }
    void print(){
        cout<<"("<<X<<", "<<Y<<", "<<Z<<")";
    }
    
};

class BaseGameEntity {
    
    typedef std::vector<BaseGameEntity *> EntitiesVector;
    typedef std::vector<BaseGameEntity *>::iterator EntitiesVectorIterator;
    
public:
    
    enum Type {
        TNoma, TCitizen, TDynamic
    };
    
    BaseGameEntity();
    BaseGameEntity(const BaseGameEntity& orig) : position(orig.position), ID(orig.ID){}
    BaseGameEntity(int i, Vector3f v){ ID = i; position = v; }
    virtual ~BaseGameEntity();
    int getID(){ return ID; }
    Vector3f getPosition(){ return position; }
    void setPosition(float x, float y, float z){ position.X = x; position.Y = y; position.Z = z; }
    void setOrientation(float o){ orientation = o;}
    float getOrientation(){return orientation; }
    EntitiesVector getNeighborhood (EntitiesVector entities, float radius);
    TNode * getTNode(){ return graphicNode; }
    void setTNode(TNode *n){ graphicNode = n; }
    void setAccesoryTNode(TNode *n){ accesoryNode = n; }
    Type getType(){ return type; }
    
protected:

    int ID;
    Vector3f position;
    float orientation;
    TNode * graphicNode;
    TNode * accesoryNode;
    Type type;
    
    float frame;
    
};

#endif	/* BASEGAMEENTITY_H */

