/* 
 * File:   TParticles.cpp
 * Author: iMac
 * 
 * Created on 18 de abril de 2014, 12:59
 */

#include "../headers/TParticles.h"
#include "../headers/TShaderProgram.h"
#include "../headers/GraphicEngine.h"

Vertex Vertices[] = {
    {   {1, -1, 0},
        {1, 0},
        {1, 0, 0, 1}
    },
    {   {1, 1, 0},
        {1, 1},
        {0, 1, 0, 1}
    },
    {   {-1, 1, 0},
        {0, 1},
        {0, 0, 1, 1}
    },
    {   {-1, -1, 0},
        {0, 0},
        {0, 0, 0, 1}
    }
};

const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
};

GLuint _vertexBuffer;
GLuint _indexBuffer;
GLuint _texture;
GLuint _program;
GLfloat _rotation;
GLfloat _pointSize;
GLfloat _particleSize;
GLfloat _particlePos[3];

TParticles::TParticles() {
}

TParticles::TParticles(const TParticles& orig) {
}

TParticles::~TParticles() {
}

void TParticles::prepareOpengl() {
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_TEXTURE_2D);
    
       
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    _texture = GraphicEngine::Instance()->getTConnector()->getResourceManager()->getResourceTexture("snow.png")->getTexture();
    
    TShaderProgram * shader = new TShaderProgram();
    shader->Load("Emisor.vs", "Emisor.fs");
    
    _program = shader->program();
    
    _rotation = 0;
    _pointSize = 32;
    _particleSize = 2.0;
    _particlePos[0] = 0;
    _particlePos[1] = 0;
    _particlePos[2] = 0;
}

void TParticles::drawPointSpriteBillboard() {
    glUseProgram(_program);

    glPointSize(_pointSize);
    glDrawArrays(GL_POINTS, 0, sizeof(Vertices)/sizeof(Vertices[0]));
}

void TParticles::drawTriangleStripBillBoard() {
    GLdouble m[16];
    glGetDoublev (GL_MODELVIEW_MATRIX, m);

    GLfloat particleRadius = _particleSize/2;
    
    GLfloat right[3];
    GLfloat up[3];
    
    right[0] = m[0] * particleRadius;
    right[1] = m[4] * particleRadius;
    right[2] = m[8] * particleRadius;

    up[0] = m[1] * particleRadius;
    up[1] = m[5] * particleRadius;
    up[2] = m[9] * particleRadius;
    
    Vertices[0].Position[0] = _particlePos[0] + right[0] + up[0];
    Vertices[0].Position[1] = _particlePos[1] + right[1] + up[1];
    Vertices[0].Position[2] = _particlePos[2] + right[2] + up[2];

    Vertices[1].Position[0] = _particlePos[0] + right[0] - up[0];
    Vertices[1].Position[1] = _particlePos[1] + right[1] - up[1];
    Vertices[1].Position[2] = _particlePos[2] + right[2] - up[2];

    Vertices[2].Position[0] = _particlePos[0] - right[0] - up[0];
    Vertices[2].Position[1] = _particlePos[1] - right[1] - up[1];
    Vertices[2].Position[2] = _particlePos[2] - right[2] - up[2];

    Vertices[3].Position[0] = _particlePos[0] - right[0] + up[0];
    Vertices[3].Position[1] = _particlePos[1] - right[1] + up[1];
    Vertices[3].Position[2] = _particlePos[2] - right[2] + up[2];
    
    glUseProgram(0);
    glDrawElements(GL_TRIANGLE_STRIP, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
}

void TParticles::drawRect() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -4);
    glRotatef(_rotation, 0, 1, 0);
    
    _rotation +=0.5;
    
    // Drawing code here.
    glClearColor(0.8, 0.8, 0.9, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);
   
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Position));
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Color));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, TexCoord));
  
    drawTriangleStripBillBoard();
    drawPointSpriteBillboard();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
}
