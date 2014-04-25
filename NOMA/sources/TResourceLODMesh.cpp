/* 
 * File:   TResourceLODMesh.cpp
 * Author: MAC
 * 
 * Created on 16 de abril de 2014, 17:41
 */

#include "../headers/TResourceLODMesh.h"
#include <sstream>

TResourceLODMesh::TResourceLODMesh() {
    texture = new TResourceTexture();
    LOD = 0;
}

TResourceLODMesh::TResourceLODMesh(const TResourceLODMesh& orig) {
}

TResourceLODMesh::~TResourceLODMesh() {
}

bool TResourceLODMesh::load(char* filename) {
    bool cont = true;
    int i = 0;
    while (cont) {
        TResourceMesh *mesh = new TResourceMesh();
        std::ostringstream file;
        string nameFile (filename);
        nameFile.erase(nameFile.end()-4, nameFile.end());
        file << nameFile << i << ".obj";
        std::string f = file.str();
        //cout << "vamos a leer el archivo: " << f << endl;
        cont = mesh->load((char*) f.c_str());
        if (cont) {
            vectorLODMesh.push_back(mesh);
        }
        i++;
    }
}
