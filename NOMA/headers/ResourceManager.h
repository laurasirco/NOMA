/* 
 * File:   ResourceManager.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:39
 */

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H
#include "PGraph.h"
#include <iostream>
#include <string>

class ResourceManager {
public:
    ResourceManager ();
    ResourceManager (const ResourceManager& orig);
    virtual ~ResourceManager ();
    PGraph * openGraph (string file);
private:

};

#endif	/* RESOURCEMANAGER_H */

