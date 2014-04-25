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

#define GET_GAME_DATA 'http://noma.herokuapp.com/api/players'
#define ADD_GAME 'http://noma.herokuapp.com/api/player'
#define UPDATE_TIME 'http://noma.herokuapp.com/api/updateTime'
#define UPDATE_ENVIRONMENT 'http://noma.herokuapp.com/api/updateEnvironment'
#define UPDATE_ACT 'http://noma.herokuapp.com/api/updateLastUnlockedAct'
#define UPDATE_PERSONALITY 'http://noma.herokuapp.com/api/updatePersonality'
#define UPDATE_AFFINITY_OF 'http://noma.herokuapp.com/api/updateAffinityOfNPC'

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

