/* 
 * File:   ServerConnector.cpp
 * Author: laurasirventcollado
 * 
 * Created on 25 de abril de 2014, 10:22
 */

#include "../headers/ServerConnector.h"

ServerConnector::ServerConnector() {
    
    curl_global_init(CURL_GLOBAL_ALL);

    handler = curl_easy_init();
    if (handler == NULL) {
        cerr << "Unable to initialize cURL interface" << endl;
    }
}

ServerConnector::ServerConnector(const ServerConnector& orig) {
}

ServerConnector::~ServerConnector() {
}

