/* 
 * File:   TResourceAnimatedMesh.cpp
 * Author: MAC
 * 
 * Created on 12 de marzo de 2014, 16:16
 */

#include "../headers/TResourceAnimatedMesh.h"
#include "../headers/Game.h"
using namespace std;
#include <sstream>

TResourceAnimatedMesh::TResourceAnimatedMesh(void) {
    frame = 0;
}

TResourceAnimatedMesh::~TResourceAnimatedMesh(void) {

}

bool TResourceAnimatedMesh::load(char *filename, TResourceTexture* texture) {

    bool cont = true;
    int i = 0;
    while (cont) {
        TResourceMesh *mesh = new TResourceMesh();
        std::ostringstream file;
        file << filename << i << ".obj";
        std::string f = file.str();
        //cout << "vamos a leer el archivo: " << f << endl;
        cont = mesh->load((char*) f.c_str());
        if (cont) {
            animation.push_back(mesh);
            animation[i]->setTexture(texture);
        }
        i++;
    }
}

void TResourceAnimatedMesh::draw() {

    
    TResourceMesh * m = animation[(int)frame];
    
    m->draw();
}

bool TResourceAnimatedMesh::setFrame(float f) {
    if (f >= animation.size()) {
        frame = 0;
        
        return true;
    } else {
        frame = f;
        return false;
    }
}
