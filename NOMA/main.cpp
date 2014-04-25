/* 
 * File:   main.cpp
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:16
 */

#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>
#include <iostream>
#include "Irrlicht/include/irrlicht.h"
#include "Irrklang/include/irrKlang.h"
#include "headers/Character.h"
#include "headers/GraphicEngine.h"
#include "headers/Game.h"
#include "headers/Parser.h"
#include <time.h>
#include <sys/time.h>
#include "headers/MovingEntity.h"
#include "headers/AudioEngine.h"

#include "headers/PNode.h"
#include "headers/PEdge.h"
#include "headers/PGraph.h"
#include "headers/PRoute.h"
#include <ctime>
#include <unistd.h>

#include "headers/Matrices.h"
#include "headers/TResourceMesh.h"
#include "headers/TResourceManager.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>
#include "headers/TAGConnector.h"
#include "headers/TTransformation.h"
#include "headers/TMesh.h"

#include "SOIL/include/SOIL.h"

#include <math.h>

#include "headers/Freetype.h"
#include "headers/GUIButton.h"
#include "headers/BaseGameEntity.h"

#include <curl/curl.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace irrklang;

std::vector<GUIButton *> buttons;
int graphicEngine;

void initGame(int graphicEngine);
void pathSettings(char** argv);
void draw();
void mouseMoved(int x, int y);
void processMouse(int button, int state, int x, int y);

int main(int argc, char** argv) {

    pathSettings(argv);

    //GRAPHIC ENGINE SELECTOR
    graphicEngine = 1;

/*
    //CURL TEST
    curl_global_init(CURL_GLOBAL_ALL);
    //Lo primero es crear un contexto.                                                                                         
    CURL* contexto = curl_easy_init();
    if (contexto == NULL) {
        cerr << "Unable to initialize cURL interface" << endl;
        return 1;
    }
    curl_easy_setopt(contexto, CURLOPT_URL, "http://noma.herokuapp.com/api/players");

    curl_easy_setopt(contexto, CURLOPT_NOPROGRESS, 1);

    //WRITEHEADER necesita de un FILE* para escribir la cabecera                                                               
    //WRITE=recibir datos READ=mandar datos                                                                                    
    curl_easy_setopt(contexto, CURLOPT_WRITEHEADER, stderr);

    //Igual, pero para el contenido real de la respuesta                                                                       
    curl_easy_setopt(contexto, CURLOPT_WRITEDATA, stdout);

    //Fin de configuración. Ahora acción!.
    const CURLcode rc = curl_easy_perform(contexto);

    if (CURLE_OK != rc) {
        cerr << "Error from cURL: " << curl_easy_strerror(rc) << endl;
    } else {
        // Estudiar algunos parómetros de la respuesta                                                                           
        cout << "\n\n **STATS** \n\n" << endl;
        double valorDouble;
        long valorLong;
        char* valorChar = NULL;
        if (CURLE_OK == curl_easy_getinfo(contexto, CURLINFO_HTTP_CODE, &valorLong)) {
            cout << "Codigo de Respuesta:  " << valorLong << endl;
        }

        if (CURLE_OK == curl_easy_getinfo(contexto, CURLINFO_CONTENT_TYPE, &valorChar)) {
            cout << "Tipo de Contenido:   " << valorChar << endl;
        }

        if (CURLE_OK == curl_easy_getinfo(contexto, CURLINFO_SIZE_DOWNLOAD, &valorDouble)) {
            cout << "Bytes Descargados:  " << valorDouble << "bytes" << endl;
        }

        if (CURLE_OK == curl_easy_getinfo(contexto, CURLINFO_SPEED_DOWNLOAD, &valorDouble)) {
            cout << "Velocidad de Descarga: " << valorDouble << "bytes/sec" << endl;
        }

    }
    //Limpiar contexto y el sistema de libcurl
    curl_easy_cleanup(contexto);
    curl_global_cleanup();
*/

    initGame(graphicEngine);
    return 0;

}

void initGame(int graphicEngine) {
    float ac = 0.0f;


    GraphicEngine * gEngine = GraphicEngine::Instance();

    CGRect mainMonitor = CGDisplayBounds(CGMainDisplayID());
    CGFloat monitorHeight = CGRectGetHeight(mainMonitor);
    CGFloat monitorWidth = CGRectGetWidth(mainMonitor);

    //gEngine->init(graphicEngine, (int) monitorWidth, (int) monitorHeight);
    gEngine->init(graphicEngine, 1280, 720);

    //Initialize GAME
    Game * game = Game::Instance();
    //Game::Instance()->setDemoMode(demoMode);
    game->setWhichGraphicConnector(graphicEngine);
    game->init();
    //TO DO: Initialize SOUND ENGINE


    float updateTime = 0;
    float renderTime = 0;

    struct timeval start;
    gettimeofday(&start, NULL);
    double nextTime = start.tv_sec + (start.tv_usec / 1000000.0);
    
    //ISoundSource* menu = AudioEngine::Instance()->addSound("Audio/mainMenu.ogg");
    //AudioEngine::Instance()->play2DSound(menu);
 
    do {
        
        
        gettimeofday(&start, NULL);
        double currentTime = start.tv_sec + (start.tv_usec / 1000000.0);

        if (currentTime >= nextTime) {
            nextTime += FPS;
            game->eventManager();
            game->update();
            if (currentTime < nextTime) {
                float fps = 1 / (nextTime - currentTime);
                gEngine->printActualFPS(1000 / fps);
                game->render(false);
            }

        } else {
            float sleepTime = (1000000 * (nextTime - currentTime));
            if (sleepTime > 0) {
                usleep(sleepTime);
            }
        }
    } while (gEngine->isDeviceRunning());

    //Free memory
    delete(gEngine);
    gEngine = NULL;
    delete(game);
    game = NULL;

}

void pathSettings(char** argv) {
    char cwd[256];
    getcwd(cwd, sizeof (cwd));
    std::string path = cwd;
    std::string pathIDE = path + "/dist/noma.app/Contents/Resources";
    if (chdir(pathIDE.c_str()) == -1) {
        std::string pathAPP = argv[0];
        pathAPP.erase(pathAPP.end() - 10, pathAPP.end());
        pathAPP = pathAPP + "Resources";
        chdir(pathAPP.c_str());
        getcwd(cwd, sizeof (cwd));
    } else {
        getcwd(cwd, sizeof (cwd));
    }
}
