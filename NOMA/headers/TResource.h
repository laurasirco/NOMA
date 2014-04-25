/* 
 * File:   TResource.h
 * Author: iMac
 *
 * Created on 17 de febrero de 2014, 22:21
 */

#ifndef TRESOURCE_H
#define	TRESOURCE_H
#include <string>
using namespace std;

class TResource {
public:
    TResource();
    TResource(const TResource& orig);
    virtual ~TResource();
    std::string getName() {return name; }
    void setName(std::string n) { name = n; }
protected:
    std::string name;
};

#endif	/* TRESOURCE_H */

