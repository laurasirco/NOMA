/* 
 * File:   TAnimatedMesh.cpp
 * Author: MAC
 * 
 * Created on 12 de marzo de 2014, 16:15
 */

#include "../headers/TAnimatedMesh.h"

TAnimatedMesh::TAnimatedMesh() {
    frame = 0;
}

TAnimatedMesh::TAnimatedMesh(const TAnimatedMesh& orig) {
}

TAnimatedMesh::~TAnimatedMesh() {
}

void TAnimatedMesh::beginDraw() {
    animations->setCurrentAnimationCycle(cycle);
    animations->setFrame(frame);
    animations->draw();
    frame = animations->getFrame();
}

