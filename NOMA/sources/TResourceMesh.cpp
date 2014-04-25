/* 
 * File:   TResourceMesh.cpp
 * Author: iMac
 * 
 * Created on 17 de febrero de 2014, 22:24
 */

//http://www.tutorialized.com/tutorial/Write-a-WaveFront-OpenGL-3D-object-loader-in-C/59679

#include "../headers/TResourceMesh.h"
#include "../headers/TResourceManager.h"
#include "../headers/GraphicEngine.h"
#include "../headers/TShaderProgram.h"
#include "../headers/TAGConnector.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

TResourceMesh::TResourceMesh() {
    texture = new TResourceTexture();
    normalsMap = new TResourceTexture();

}

TResourceMesh::TResourceMesh(const TResourceMesh& orig) {
}

TResourceMesh::~TResourceMesh() {

    if (texture != NULL) {
        TResourceManager::Instance()->deleteResource(texture);
        texture = NULL;
        TResourceManager::Instance()->deleteResource(normalsMap);
    }
}

bool TResourceMesh::load(char *filename) {
    //cout<<"Loading: "<<filename<<endl;
    fstream objFile;
    objFile.open(filename);

    if (objFile.is_open()) {
        char line[255];

        // Parse object file line by line
        while (objFile.good()) {
            objFile.getline(line, 255);
            parseLine(line);
        }

        objFile.close();

    } else {
        //cout << "Could not open WFObject file '" << filename << "'\n";
        return false;
    }

    return true;
}

void TResourceMesh::parseLine(char *line) {
    if (!strlen(line)) // If empty string, don't do anything with it
    {
        return;
    }

    char *lineType;
    lineType = strtok(strdup(line), " ");


    // Decide what to do
    if (!strcmp(lineType, "v")) // Vertex
    {
        parseVertex(line);
    } else if (!strcmp(lineType, "vn")) // Normal
    {
        parseNormal(line);
    } else if (!strcmp(lineType, "f")) // Face
    {
        parseFace(line);
    } else if (!strcmp(lineType, "vt")) // Face
    {
        parseUV(line);
    }


    return;
}

void TResourceMesh::parseVertex(char *line) {
    vertices.push_back(Vector3f()); // Add a new element to the vertices array

    sscanf(line, "v %f %f %f", &vertices.back().X, &vertices.back().Y, &vertices.back().Z);

    return;
}

void TResourceMesh::parseNormal(char *line) {
    normals.push_back(Vector3f());

    sscanf(line, "vn %f %f %f", &normals.back().X, &normals.back().Y, &normals.back().Z);

    return;
}

void TResourceMesh::parseUV(char *line) {
    UVs.push_back(Vector3f());

    sscanf(line, "vt %f %f", &UVs.back().X, &UVs.back().Y);

    return;
}

void TResourceMesh::parseFace(char *line) {

    faces.push_back(Face());

    // Read face line. If texture indicies aren't present, don't read them.
    if (sscanf(line, "f %d//%d %d//%d %d//%d", &faces.back().v1,
            &faces.back().vn1,
            &faces.back().v2,
            &faces.back().vn2,
            &faces.back().v3,
            &faces.back().vn3) <= 1) {
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces.back().v1,
                &faces.back().vt1,
                &faces.back().vn1,
                &faces.back().v2,
                &faces.back().vt2,
                &faces.back().vn2,
                &faces.back().v3,
                &faces.back().vt3,
                &faces.back().vn3);
    }

    return;
}

void TResourceMesh::draw() {

    int repeat = texture->getRepeat();

    /*if(color->r != 1.0 || color->g != 1.0 || color->b != 1.0){
        GLfloat colorf[4] = { color->r, color->g, color->b, color->a }; 
        glMaterialfv( GL_FRONT, GL_AMBIENT, colorf );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, colorf );
    }
    
    else{
        GLfloat ambientMat[] = {0.2, 0.2, 0.2, 1.0};
        GLfloat diffuseMat[] = {0.8, 0.8, 0.8, 1.0};
        GLfloat blankMat[] = {0.0, 0.0, 0.0, 1.0}; 
        glMaterialfv( GL_FRONT, GL_AMBIENT, ambientMat );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuseMat );
        glMaterialfv( GL_FRONT, GL_SPECULAR, blankMat );
        glMaterialfv( GL_FRONT, GL_EMISSION, blankMat );
        glMaterialfv( GL_FRONT, GL_SHININESS, blankMat );
    }*/

    

    glActiveTexture(GL_TEXTURE0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    /*if(normalsMap->getName() != ""){

        //glUniform1i(TAGConnector::getRenderShader().UniformLocations[5], 1);
        
        glActiveTexture(GL_TEXTURE2);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, normalsMap->getTexture());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
    else{
        
        //glUniform1i(TAGConnector::getRenderShader().UniformLocations[5], 0);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }*/

    glBegin(GL_TRIANGLES);

    for (int f = 0; f < faces.size(); f++) {

        //cout<<vertices[faces[f].v1 - 1].X<<","<<vertices[faces[f].v1 - 1].Y<<","<<vertices[faces[f].v1 - 1].Z<<endl;
        glNormal3f(normals[faces[f].vn1 - 1].X, normals[faces[f].vn1 - 1].Y, normals[faces[f].vn1 - 1].Z);
        glTexCoord2f(UVs[faces[f].vt1 - 1].X *repeat, UVs[faces[f].vt1 - 1].Y * repeat);
        glVertex3f(vertices[faces[f].v1 - 1].X, vertices[faces[f].v1 - 1].Y, vertices[faces[f].v1 - 1].Z);

        glNormal3f(normals[faces[f].vn2 - 1].X, normals[faces[f].vn2 - 1].Y, normals[faces[f].vn2 - 1].Z);
        glTexCoord2f(UVs[faces[f].vt2 - 1].X *repeat, UVs[faces[f].vt2 - 1].Y * repeat);
        glVertex3f(vertices[faces[f].v2 - 1].X, vertices[faces[f].v2 - 1].Y, vertices[faces[f].v2 - 1].Z);

        glNormal3f(normals[faces[f].vn3 - 1].X, normals[faces[f].vn3 - 1].Y, normals[faces[f].vn3 - 1].Z);
        glTexCoord2f(UVs[faces[f].vt3 - 1].X *repeat, UVs[faces[f].vt3 - 1].Y * repeat);
        glVertex3f(vertices[faces[f].v3 - 1].X, vertices[faces[f].v3 - 1].Y, vertices[faces[f].v3 - 1].Z);


    }

    glEnd();
}

vector<Vector3f> TResourceMesh::getTriangle(int index) {

    vector<Vector3f> triple;

    Vector3f first = Vector3f(vertices[faces[index].v1 - 1].X, vertices[faces[index].v1 - 1].Y, vertices[faces[index].v1 - 1].Z);
    Vector3f second = Vector3f(vertices[faces[index].v2 - 1].X, vertices[faces[index].v2 - 1].Y, vertices[faces[index].v2 - 1].Z);
    Vector3f third = Vector3f(vertices[faces[index].v3 - 1].X, vertices[faces[index].v3 - 1].Y, vertices[faces[index].v3 - 1].Z);
    triple.push_back(first);
    triple.push_back(second);
    triple.push_back(third);

    return triple;
}