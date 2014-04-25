/* 
 * File:   TResourceAnimatedMeshContainer.cpp
 * Author: laurasirventcollado
 * 
 * Created on 15 de marzo de 2014, 20:39
 */

#include "../headers/TResourceAnimatedMeshContainer.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "../headers/GraphicEngine.h"

TResourceAnimatedMeshContainer::TResourceAnimatedMeshContainer() {
    frame = 0;
}

TResourceAnimatedMeshContainer::TResourceAnimatedMeshContainer(const TResourceAnimatedMeshContainer& orig) {
}

TResourceAnimatedMeshContainer::~TResourceAnimatedMeshContainer() {
}

bool TResourceAnimatedMeshContainer::load(char* filename) {
    struct dirent **namelist;
    int n;
    n = scandir(filename, &namelist, 0, alphasort);
    if (n < 0) {
        std::cout << "No hay cosicas" << endl;
    } else {
        for (int i = 2; i < n; i++) {
            if (strcmp(namelist[i]->d_name, ".DS_Store") != 0) {
                TResourceAnimatedMesh * resource = new TResourceAnimatedMesh();

                char path[255];
                char texturePath[255];
                strcpy(path, filename);
                strcpy(texturePath, filename);
                strcat(texturePath,".png");
                strcat(path, "/");
                strcat(path, namelist[i]->d_name);
                strcat(path, "/");
                strcat(path, namelist[i]->d_name);
                resource->load(path, GraphicEngine::Instance()->getTConnector()->getResourceManager()->getResourceTexture(texturePath));

                //Stand, Talk, Walk, RunNeutral, RunTired, Jump, Start, Stop, Wave
                if (strcmp(namelist[i]->d_name, "Stand") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Stand, resource));
                if (strcmp(namelist[i]->d_name,"Talk") == 0) 
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Talk, resource));
                if (strcmp(namelist[i]->d_name,"Walk") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Walk, resource));
                if (strcmp(namelist[i]->d_name, "RunNeutral") == 0) 
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (RunNeutral, resource));
                if (strcmp(namelist[i]->d_name,"RunTired") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (RunTired, resource));
                if (strcmp(namelist[i]->d_name,"Jump") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Jump, resource));
                if (strcmp(namelist[i]->d_name,"Start") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Start, resource));
                if (strcmp(namelist[i]->d_name,"Stop") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Stop, resource));
                if (strcmp(namelist[i]->d_name,"Wave") == 0)
                    animations.insert(std::pair<Cycle, TResourceAnimatedMesh*> (Wave, resource));
                
                }  
            
        }
    }
    return true;

}

void TResourceAnimatedMeshContainer::draw() {
    
    TResourceAnimatedMesh * animMesh = animations.find(currentCycle)->second;

    bool b = animMesh->setFrame(frame);

    if(b == true)
        frame = 0;

    animMesh->draw();

}