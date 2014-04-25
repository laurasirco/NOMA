/* 
 * File:   ServerConnector.h
 * Author: laurasirventcollado
 *
 * Created on 25 de abril de 2014, 10:22
 */

#ifndef SERVERCONNECTOR_H
#define	SERVERCONNECTOR_H

#include <curl/curl.h>
#include <iostream>

#define BASE_URL 'http://noma.herokuapp.com/api'

using namespace std;

class ServerConnector {
public:
    ServerConnector();
    ServerConnector(const ServerConnector& orig);
    virtual ~ServerConnector();
private:
    CURL * handler;
    CURLcode result;
};

#endif	/* SERVERCONNECTOR_H */

