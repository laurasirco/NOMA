/* 
 * File:   TAGConnector.cpp
 * Author: iMac
 * 
 * Created on 18 de febrero de 2014, 11:46
 */

#include <ApplicationServices/ApplicationServices.h>
#include "../headers/TAGConnector.h"
#include "../headers/Matrices.h"
#include "../headers/EventManager.h"
#include "../headers/GUIElement.h"
#include "../headers/Game.h"
#include "../headers/Citizen.h"
#include "../headers/TLODMesh.h"
#include "../headers/OptionMenuState.h"
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <algorithm>

#include "../headers/Freetype.h"

#define SHADOW_Q 1

float TAGConnector::prevMouseX = 0;
vector<TNode *> TAGConnector::cameras;
vector<TLight *> TAGConnector::lights;
TNode* TAGConnector::scene = new TNode();
float TAGConnector::cont = 0;
int TAGConnector::screenHeight = 0;
int TAGConnector::screenWidth = 0;
float TAGConnector::xrot = 0;
float TAGConnector::yrot = 20;
GLDebugDraw * TAGConnector::debugDraw = new GLDebugDraw();
GLdouble TAGConnector::modelview[16] = {0};
GLdouble TAGConnector::projection[16] = {0};
GLint TAGConnector::viewport[4] = {0};

TShadowMapFBO * TAGConnector::shadowMapFBO = new TShadowMapFBO();
TFBO * TAGConnector::sceneFBO = new TFBO();
TShaderProgram TAGConnector::postShader = TShaderProgram();
TShaderProgram TAGConnector::DOFShader = TShaderProgram();
TTransformation * TAGConnector::mainLight = new TTransformation();
GLuint TAGConnector::auxiliarTex = 0;

TShaderProgram TAGConnector::renderShader = TShaderProgram();
Matrix4 TAGConnector::shadowMatrix = Matrix4();

TShaderProgram TAGConnector::skyShader = TShaderProgram();
float TAGConnector::SunR = 600.0f;
Vector3 TAGConnector::SunRotVec = Vector3(0.0f, -0.66f, -1.0f).normalize();
Vector3 TAGConnector::SunCPos = Vector3();
GLuint TAGConnector::VBO = 0;
GLfloat TAGConnector::ambientColor[4] = {0};
GLfloat TAGConnector::diffuseColor[4] = {0};
GLfloat TAGConnector::sunPosition[4] = {0};

TShaderProgram TAGConnector::sunDepthTest = TShaderProgram();
TShaderProgram TAGConnector::blurH = TShaderProgram();
TShaderProgram TAGConnector::blurV = TShaderProgram();
TShaderProgram TAGConnector::sunRaysLensFlareHalo = TShaderProgram();
GLuint TAGConnector::sunTextures[4] = {0};
GLuint TAGConnector::depthTexture = 0;
GLuint TAGConnector::FBO = 0;
TResourceTexture * TAGConnector::dirtTexture = new TResourceTexture();

TShaderProgram TAGConnector::gaussianBlurH = TShaderProgram();
TShaderProgram TAGConnector::gaussianBlurV = TShaderProgram();
float TAGConnector::sunAngle = 0.0;

int TAGConnector::graphicsQuality = 0;

TAGConnector::TAGConnector() {

    resourceManager = TResourceManager::Instance();

    SunCPos = Vector3(0.0, -5000.0, 10000.0);

    //cout << "SunRotVec: " << SunRotVec << endl;
    //cout << "SunCPos: " << SunCPos << endl;

}

void TAGConnector::display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

TAGConnector::TAGConnector(const TAGConnector& orig) {
}

TAGConnector::~TAGConnector() {
}

void TAGConnector::init(int h, int w) {

    TAGConnector::screenHeight = h;
    TAGConnector::screenWidth = w;

    char *argv[] = {"TAGConnector"};
    int argc = 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("NOMA");
    glEnable(GL_NORMALIZE);

    //Glut Callbacks
    glutDisplayFunc(draw);
    glutKeyboardFunc(EventManager::keyPressed);
    glutKeyboardUpFunc(EventManager::keyUp);
    glutMouseFunc(EventManager::processMouse);
    glutMotionFunc(EventManager::mouseMoved);
    glutPassiveMotionFunc(EventManager::passiveMouseMoved);
    //glutFullScreen();

    glClearColor(0, 0, 0, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    //**************PRUEBAS LUCES*****************
    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader

    GLfloat ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat diffuse[] = {0.75f, 0.75f, 0.75f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f / 128.0f);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0001f / 256.0f);

    GLfloat LightPosition[] = {0.0, 10.0, -20.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    //Main Light
    mainLight->translate(SunCPos.x, SunCPos.y, SunCPos.z);
    TNode * lightNode = createNode(scene, mainLight);

    /* TLight *ambientLight = new TLight();
     ambientLight->setIntensity(RGBA(1.0, 1.0, 1.0, 1.0));
     registerLight(ambientLight);


     //angle of rotation
     GLfloat angle = 0.0;

     //diffuse light color variables
     GLfloat dlr = 1;
     GLfloat dlg = 1;
     GLfloat dlb = 1;

     //ambient light color variables
     GLfloat alr = 1.0;
     GLfloat alg = 1.0;
     GLfloat alb = 1.0;

     //light position variables
     GLfloat lx = 40;
     GLfloat ly = 50.0;
     GLfloat lz = 0.0;
     GLfloat lw = 0.0;

     glClearColor(0.0, 0.0, 0.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     GLfloat AmbientLight[] = {alr, alg, alb};
     glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);

     GLfloat DiffuseLight[] = {dlr, dlg, dlb};
     glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
     GLfloat LightPosition[] = {lx, ly, lz, lw};
     glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

     glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
     GLfloat LightPosition2[] = {lx, 100, lz, lw};
     glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);*/
    //*************/

    postShader.Load("ChromaticAberration.vs", "ChromaticAberration.fs");
    postShader.Link();

    postShader.UniformLocations = new GLuint[2];
    postShader.UniformLocations[0] = glGetUniformLocation(postShader.program(), "resolution");
    postShader.UniformLocations[1] = glGetUniformLocation(postShader.program(), "texture");

    DOFShader.Load("DOF.vs", "DOF.fs");
    DOFShader.Link();

    DOFShader.UniformLocations = new GLuint[3];
    DOFShader.UniformLocations[0] = glGetUniformLocation(DOFShader.program(), "resolution");
    DOFShader.UniformLocations[1] = glGetUniformLocation(DOFShader.program(), "texture");
    DOFShader.UniformLocations[2] = glGetUniformLocation(DOFShader.program(), "depth");

    glGenTextures(1, &auxiliarTex);

    glBindTexture(GL_TEXTURE_2D, auxiliarTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    TAGConnector::shadowMapFBO->Init(screenWidth * SHADOW_Q, screenHeight * SHADOW_Q);
    TAGConnector::sceneFBO->Init(screenWidth, screenHeight);

    renderShader.Load("ShadowMapping.vs", "ShadowMapping.fs");
    renderShader.Link();

    renderShader.UniformLocations = new GLuint[7];
    renderShader.UniformLocations[0] = glGetUniformLocation(renderShader.program(), "ShadowMatrix");
    renderShader.UniformLocations[1] = glGetUniformLocation(renderShader.program(), "Texture");
    renderShader.UniformLocations[2] = glGetUniformLocation(renderShader.program(), "ShadowMap");
    renderShader.UniformLocations[3] = glGetUniformLocation(renderShader.program(), "ModelViewInverse");
    renderShader.UniformLocations[4] = glGetUniformLocation(renderShader.program(), "NormalsMap");
    renderShader.UniformLocations[5] = glGetUniformLocation(renderShader.program(), "CustomNormal");
    renderShader.UniformLocations[6] = glGetUniformLocation(renderShader.program(), "SunPosition");

    glUseProgram(renderShader.program());
    glUniform1i(renderShader.UniformLocations[1], 0);
    glUniform1i(renderShader.UniformLocations[2], 1);
    glUniform1i(renderShader.UniformLocations[4], 2);
    glUseProgram(0);
    //particles = new TParticles();



    sunDepthTest.Load("sundepthtest.vs", "sundepthtest.fs");
    sunDepthTest.Link();

    glGenTextures(1, &depthTexture);
    glGenTextures(4, sunTextures);
    glGenFramebuffersEXT(1, &FBO);

    glUseProgram(sunDepthTest.program());
    glUniform1i(glGetUniformLocation(sunDepthTest.program(), "SunTexture"), 0);
    glUniform1i(glGetUniformLocation(sunDepthTest.program(), "DepthTexture"), 1);
    glUseProgram(0);

    blurH.Load("blur.vs", "blurh.fs");
    blurH.Link();
    blurV.Load("blur.vs", "blurv.fs");
    blurV.Link();

    gaussianBlurH.Load("gBlur.vs", "gBlurH.fs");
    gaussianBlurH.Link();

    glUseProgram(gaussianBlurH.program());
    glUniform1i(glGetUniformLocation(gaussianBlurH.program(), "RTScene"), 0);
    glUseProgram(0);

    gaussianBlurV.Load("gBlur.vs", "gBlurV.fs");
    gaussianBlurV.Link();

    glUseProgram(gaussianBlurV.program());
    glUniform1i(glGetUniformLocation(gaussianBlurV.program(), "RTBlurH"), 0);
    glUseProgram(0);

    sunRaysLensFlareHalo.Load("sunrayslensflarehalo.vs", "sunrayslensflarehalo.fs");
    sunRaysLensFlareHalo.Link();

    glUseProgram(sunRaysLensFlareHalo.program());
    glUniform1i(glGetUniformLocation(sunRaysLensFlareHalo.program(), "LowBlurredSunTexture"), 0);
    glUniform1i(glGetUniformLocation(sunRaysLensFlareHalo.program(), "HighBlurredSunTexture"), 1);
    glUniform1i(glGetUniformLocation(sunRaysLensFlareHalo.program(), "DirtTexture"), 2);
    glUniform1f(glGetUniformLocation(sunRaysLensFlareHalo.program(), "Dispersal"), 0.1875f);
    glUniform1f(glGetUniformLocation(sunRaysLensFlareHalo.program(), "HaloWidth"), 0.45f);
    glUniform1f(glGetUniformLocation(sunRaysLensFlareHalo.program(), "Intensity"), 2.25f);
    glUniform3f(glGetUniformLocation(sunRaysLensFlareHalo.program(), "Distortion"), 0.94f, 0.97f, 1.00f);
    glUseProgram(0);

    dirtTexture = resourceManager->getResourceTexture("lensdirt_lowc.jpg");

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    int SunTextureWidth = screenWidth;
    int SunTextureHeight = screenHeight;

    for (int i = 0; i < 4; i++) {
        glBindTexture(GL_TEXTURE_2D, sunTextures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SunTextureWidth, SunTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    skyShader.Load("skyfromatmosphere.vs", "skyfromatmosphere.fs");
    skyShader.Link();

    skyShader.UniformLocations = new GLuint[1];
    skyShader.UniformLocations[0] = glGetUniformLocation(skyShader.program(), "globalTime");

    float Kr = 0.0030f;
    float Km = 0.0015f;
    float ESun = 16.0f;
    float g = -0.75f;
    float InnerRadius = 200.0f;
    float OuterRadius = 205.0f;
    float Scale = 1.0f / (OuterRadius - InnerRadius);
    float ScaleDepth = 0.7f;
    float ScaleOverScaleDepth = Scale / ScaleDepth;

    glUseProgram(skyShader.program());
    glUniform3f(glGetUniformLocation(skyShader.program(), "v3CameraPos"), 0.0f, InnerRadius, 0.0f);
    glUniform3f(glGetUniformLocation(skyShader.program(), "v3InvWavelength"), 1.0f / powf(0.650f, 4.0f), 1.0f / powf(0.570f, 4.0f), 1.0f / powf(0.475f, 4.0f));
    glUniform1f(glGetUniformLocation(skyShader.program(), "fCameraHeight"), InnerRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fCameraHeight2"), InnerRadius * InnerRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fInnerRadius"), InnerRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fInnerRadius2"), InnerRadius * InnerRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fOuterRadius"), OuterRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fOuterRadius2"), OuterRadius * OuterRadius);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fKrESun"), Kr * ESun);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fKmESun"), Km * ESun);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fKr4PI"), Kr * 4.0f * (float) M_PI);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fKm4PI"), Km * 4.0f * (float) M_PI);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fScale"), Scale);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fScaleDepth"), ScaleDepth);
    glUniform1f(glGetUniformLocation(skyShader.program(), "fScaleOverScaleDepth"), ScaleOverScaleDepth);
    glUniform1f(glGetUniformLocation(skyShader.program(), "g"), g);
    glUniform1f(glGetUniformLocation(skyShader.program(), "g2"), g * g);
    glUniform1i(glGetUniformLocation(skyShader.program(), "Samples"), 4);
    glUniform2f(glGetUniformLocation(skyShader.program(), "resolution"), screenWidth, screenHeight);
    glUseProgram(0);

    Vector3 *SkyDomeVertices = new Vector3[112 * 3], va, vb, vc, vd;
    float stepa = (float) M_PI * 2.0f / 16, startb = asin(InnerRadius / OuterRadius), stepb = ((float) M_PI_2 - startb) / 4;
    int pos = 0;

    for (int y = 0; y < 3; y++) {
        float b = startb + stepb * y;

        for (int x = 0; x < 16; x++) {
            float a = stepa * x;

            va = Vector3(sin(a) * cos(b) * OuterRadius, sin(b) * OuterRadius, -cos(a) * cos(b) * OuterRadius);
            vb = Vector3(sin(a + stepa) * cos(b) * OuterRadius, sin(b) * OuterRadius, -cos(a + stepa) * cos(b) * OuterRadius);
            vc = Vector3(sin(a + stepa) * cos(b + stepb) * OuterRadius, sin(b + stepb) * OuterRadius, -cos(a + stepa) * cos(b + stepb) * OuterRadius);
            vd = Vector3(sin(a) * cos(b + stepb) * OuterRadius, sin(b + stepb) * OuterRadius, -cos(a) * cos(b + stepb) * OuterRadius);

            SkyDomeVertices[pos + 0] = va;
            SkyDomeVertices[pos + 1] = vb;
            SkyDomeVertices[pos + 2] = vc;

            pos += 3;

            SkyDomeVertices[pos + 0] = vc;
            SkyDomeVertices[pos + 1] = vd;
            SkyDomeVertices[pos + 2] = va;

            pos += 3;
        }
    }

    float b = startb + stepb * 3;

    for (int x = 0; x < 16; x++) {
        float a = stepa * x;

        va = Vector3(sin(a) * cos(b) * OuterRadius, sin(b) * OuterRadius, -cos(a) * cos(b) * OuterRadius);
        vb = Vector3(sin(a + stepa) * cos(b) * OuterRadius, sin(b) * OuterRadius, -cos(a + stepa) * cos(b) * OuterRadius);
        vc = Vector3(0, OuterRadius, 0);

        SkyDomeVertices[pos + 0] = va;
        SkyDomeVertices[pos + 1] = vb;
        SkyDomeVertices[pos + 2] = vc;

        pos += 3;
    }

    /*cout << "Skydome: " << endl;
    for (int i = 0; i < 112 * 3; i++)
        cout << SkyDomeVertices[i] << ",";
    cout << endl;*/

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 112 * 3 * 3 * sizeof (float), SkyDomeVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete [] SkyDomeVertices;

    graphicsQuality = OptionMenuState::Instance()->getGraphicsQuality();

}

void TAGConnector::updateAmbientLightIntensity(float r, float g, float b, float a) {

    //TLight * ambient = lights[0];
    //ambient->setIntensity(RGBA(r, g, b, a));
}

TNode *TAGConnector::createNode(TNode* parent, TEntity* entity) {
    TNode *node = new TNode();
    node->setEntity(entity);
    node->addParent(parent);
    parent->addChild(node);
    return node;
}

TAnimatedMesh *TAGConnector::createAnimatedMesh(std::string file) {
    TAnimatedMesh *mesh = new TAnimatedMesh();
    mesh->setAnimatedMeshContainer(resourceManager->getResourceAnimatedMesh(file));

    return mesh;
}

TMesh *TAGConnector::createMesh(std::string file) {
    cout << "-------" << file << endl;
    TMesh *mesh = new TMesh();
    mesh->setMesh(resourceManager->getResourceMesh(file));
    return mesh;
}

void TAGConnector::addEntity(BaseGameEntity* entity, std::string meshName, std::string textureName) {


    TTransformation * transformation = new TTransformation();
    transformation->translate(entity->getPosition().X, entity->getPosition().Y, entity->getPosition().Z);
    TNode * transformationNode = createNode(scene, transformation);

    TAnimatedMesh * mesh = createAnimatedMesh(meshName);



    //mesh->getResourceMesh()->setTexture(resourceManager->getResourceTexture(textureName));
    TNode * meshNode = createNode(transformationNode, mesh);
    entity->setTNode(meshNode);
    if (meshName == "Animations/Noma") {
        TAnimatedMesh * coat = createAnimatedMesh("Animations/Coat");
        TNode * coatNode = createNode(transformationNode, coat);
        entity->setAccesoryTNode(coatNode);
    }

    //cout << "added: " << meshName << "," << textureName << endl;



}

void TAGConnector::addWorldEntity(Matrix4 transformation, std::string meshName, std::string textureName) {

    TTransformation * t = new TTransformation();
    t->loadMatrix(transformation);
    t->rotateX(-90);
    //t->scale(-1,1,1);
    TNode * transformationNode = createNode(scene, t);

    /*TMesh * mesh = createMesh(meshName);
    mesh->getResourceMesh()->setTexture(resourceManager->getResourceTexture(textureName));
    TNode * meshNode = createNode(transformationNode, mesh);*/

    //SPECIAL CASES

    if (meshName.find("terrain.obj") != -1) {

        TMesh * mesh = createMesh(meshName);
        mesh->getResourceMesh()->setTexture(resourceManager->getResourceTexture(textureName));
        mesh->getResourceMesh()->setNormalsMap(resourceManager->getResourceTexture("World0/terrain_NRM.png"));
        TNode * meshNode = createNode(transformationNode, mesh);
        mesh->getResourceMesh()->setRepeatTexture(100);

    } else if (meshName.find("Esfera.obj") != -1) {
        TMesh * mesh = createMesh(meshName);
        mesh->getResourceMesh()->setTexture(resourceManager->getResourceTexture(textureName));
        TNode * meshNode = createNode(transformationNode, mesh);
    } else if (meshName.find("monolith.obj") != -1) {

        TMesh * mesh = createMesh(meshName);
        mesh->getResourceMesh()->setTexture(resourceManager->getResourceTexture(textureName));
        TNode * meshNode = createNode(transformationNode, mesh);
        Vector3f monolithPosition = Vector3f(transformation[3], transformation[11], -transformation[7]);
        cout << "Monolith position:";
        monolithPosition.print();
        cout << endl;
        GameState::Instance()->getCurrentWorld()->addMonolith(monolithPosition);
    } else {

        TLODMesh *TLOD = new TLODMesh();
        TLOD->setResource(resourceManager->getResourceLOD(meshName));
        TLOD->getResource()->setTexture(resourceManager->getResourceTexture(textureName));
        TNode * meshNode = createNode(transformationNode, TLOD);

    }


}

void TAGConnector::clearSceneTree() {
    cout << TAGConnector::scene->getNumberOfChilds() << endl;

    for (int i = 0; i < scene->getNumberOfChilds(); i++) {

        TNode *aux = scene->getChild(i);
        int j = 0;
        while (aux->getNumberOfChilds() != 0) {
            aux = aux->getChild(j);
        }

        while (aux->getParent() != scene) {
            TNode* parent = aux->getParent();
            parent->removeChild(aux);
            aux = parent;
        }
        scene->removeChild(aux);
        aux = NULL;
    }

    scene->reset();
    cout << "Deleted world, childs:" << TAGConnector::scene->getNumberOfChilds() << endl;
}

void TAGConnector::checkMouse() {

    int auxDiff = abs(prevMouseX - EventManager::Instance()->getMouseX());

    int diff = EventManager::Instance()->getMouseX() - (TAGConnector::screenWidth / 2);
    int diffVertical = (EventManager::Instance()->getMouseY() - (TAGConnector::screenHeight / 2)) * 0.5;
    if ((diffVertical > 2 || diffVertical < -2) && yrot <= 60 && yrot >= 5) {
        yrot += diffVertical * 0.2;
    } else if (yrot > 60) {
        yrot = 60;
    } else if (yrot < 5) yrot = 5;

    if ((diff > 1 || diff < -1) && auxDiff > 0)
        xrot += diff * 0.2;

    if (xrot >= 360 || xrot <= -360)
        xrot = 0;

    GameState::Instance()->getHUD()->setRotation(xrot);
    //cout<<"yrot:"<<yrot<<endl;
    //cout<<"xrot:"<<xrot<<endl;
    CGSetLocalEventsSuppressionInterval(0.0);
    CGPoint centerPos = CGPointMake((TAGConnector::screenWidth / 2) + glutGet(GLUT_WINDOW_X), (TAGConnector::screenHeight / 2) + glutGet(GLUT_WINDOW_Y));
    CGWarpMouseCursorPosition(centerPos);
    glutSetCursor(GLUT_CURSOR_NONE);


    if (EventManager::Instance()->isKeyDown(KEY_KEY_W)) {
        GameState::Instance()->getNoma()->setRotation(-xrot);
        TTransformation * nomaTransf = (TTransformation*) GameState::Instance()->getNoma()->getTNode()->getParent()->getEntity();
        nomaTransf->absoluteRotateY(-xrot);
    }

    prevMouseX = EventManager::Instance()->getMouseX();

}

void TAGConnector::draw() {

    if (Game::Instance()->getCurrentState()->getType() == State::Game || Game::Instance()->getCurrentState()->getType() == State::Map) {

        SunCPos.z = 10000.0 * cos(sunAngle * 3.14 / 180);
        SunCPos.y = 5000.0 * sin(sunAngle * 3.14 / 180);
        //cout << "Sun pos: " << SunCPos << endl;
        sunAngle += 0.1;

        skyRender();

        shadowPass();

        renderPass();

        sunRender();

        postEffectsPass();


    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }

    if (Game::Instance()->getCurrentState()->getType() == State::Option)
        graphicsQuality = OptionMenuState::Instance()->getGraphicsQuality();


    //Ambient Lighting

    /*if (Game::Instance()->getCurrentState()->getType() == State::Game && Game::Instance()->getDemoMode() == 3) {

        RGBA intensity = RGBA(GameState::Instance()->getEnvironment()->getColor().r, GameState::Instance()->getEnvironment()->getColor().g, GameState::Instance()->getEnvironment()->getColor().b, 1.0);
        GLfloat AmbientLight[] = {intensity.r, intensity.g, intensity.b, intensity.a};
        glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);

    }*/

    //********* DEBUGGER ***********/ 

    /*if (Game::Instance()->getCurrentState()->getType() == State::Game && Game::Instance()->getDebugMode()) {
        GameState::Instance()->getPhysicsEngine()->debugRender();
        TAGConnector::debugDraw->drawPathfindingRoutes(GameState::Instance()->getCurrentWorld()->getWayPoints());
    }*/

    /****************************/

    drawGUIElements();

    /*if (Game::Instance()->getCurrentState()->getType() == State::Game || Game::Instance()->getCurrentState()->getType() == State::Map) {
        glDisable(GL_DEPTH_TEST);
        glUseProgramObjectARB(0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-screenWidth / 2, screenWidth / 2, -screenHeight / 2, screenHeight / 2, 1, 20);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor4f(1, 1, 1, 1);
        glActiveTextureARB(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTextures[3]);
        glEnable(GL_TEXTURE_2D);
        glTranslated(0, 0, -1);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2d(1, 0);
        glVertex3f(screenWidth / 2, 0, 0);
        glTexCoord2d(1, 1);
        glVertex3f(screenWidth / 2, screenHeight / 2, 0);
        glTexCoord2d(0, 1);
        glVertex3f(0, screenHeight / 2, 0);


        glEnd();
        glDisable(GL_TEXTURE_2D);
    }*/
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();

}

void TAGConnector::debugRender(GLuint tex) {
    glDisable(GL_DEPTH_TEST);
    glUseProgramObjectARB(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-screenWidth / 2, screenWidth / 2, -screenHeight / 2, screenHeight / 2, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1, 1, 1, 1);
    glActiveTextureARB(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glTranslated(0, 0, -1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2d(1, 0);
    glVertex3f(screenWidth / 2, 0, 0);
    glTexCoord2d(1, 1);
    glVertex3f(screenWidth / 2, screenHeight / 2, 0);
    glTexCoord2d(0, 1);
    glVertex3f(0, screenHeight / 2, 0);


    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void TAGConnector::drawSceneTree() {
    for (int i = 0; i < TAGConnector::scene->getNumberOfChilds(); i++) {
        TAGConnector::scene->getChild(i)->draw();
    }
    //particles->prepareOpengl();
}

void TAGConnector::drawGUIElements() {

    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::vector<GUIElement *> GUI = Game::Instance()->getCurrentState()->getGUIElements();
    for (int i = 0; i < GUI.size(); i++) {
        GUI[i]->draw();
    }
}

void TAGConnector::renderPass() {
    //Render scene in scene FBO

    sceneFBO->BindForWriting();
    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    glUseProgram(renderShader.program());

    glViewport(0, 0, screenWidth, screenHeight);

    shadowMapFBO->BindForReading(1);

    float lightprojection[16];
    glGetFloatv(GL_PROJECTION_MATRIX, lightprojection);
    Matrix4 lightProjectionMatrix = Matrix4(lightprojection);
    //cout<<"Light projection: "<<endl; cout<<lightProjectionMatrix<<endl;

    float lightmodelView[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, lightmodelView);

    Matrix4 lightViewMatrix = Matrix4(lightmodelView);
    //cout<<"Light View: "<<endl; cout<<lightViewMatrix<<endl;
    Matrix4 biasMatrix = Matrix4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

    //setupMatrices(0, 4, -13, 0, 5, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) screenWidth / (float) screenHeight, 1, 40000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 4, -13, 0, 5, 0, 0, 1, 0);

    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    Matrix4 viewMatrixInverse = Matrix4((float *) modelview).invert();

    shadowMatrix = biasMatrix * lightProjectionMatrix * lightViewMatrix * viewMatrixInverse;
    //cout<<"Shadow Matrix: "<<endl; cout<<shadowMatrix<<endl;

    glUniformMatrix4fv(renderShader.UniformLocations[0], 1, GL_FALSE, shadowMatrix.get());
    glUniformMatrix4fv(renderShader.UniformLocations[3], 1, GL_FALSE, viewMatrixInverse.get());
    glUniform1i(renderShader.UniformLocations[5], 0);
    glUniform3f(renderShader.UniformLocations[6], sunPosition[0], sunPosition[1], sunPosition[2]);

    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    if (Game::Instance()->getCurrentState()->getType() == State::Game) {
        checkMouse();
        Matrix4 matrixWorld;
        matrixWorld.translate(-GameState::Instance()->getNoma()->getPosition().X, -GameState::Instance()->getNoma()->getPosition().Y, -GameState::Instance()->getNoma()->getPosition().Z);
        matrixWorld.rotateY(xrot);

        glMultMatrixf(matrixWorld.getTranspose());
    }

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // Clear previous frame values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);


    drawSceneTree();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);

    glDisable(GL_DEPTH_TEST);
}

void TAGConnector::shadowPass() {

    //mainLight->translate(cos(glutGet(GLUT_ELAPSED_TIME)/1000.0), 0, sin(glutGet(GLUT_ELAPSED_TIME)/1000.0));

    Vector3f noma = GameState::Instance()->getNoma()->getPosition();

    Vector3f previous = Vector3f(mainLight->getPosition().x, mainLight->getPosition().y, mainLight->getPosition().z);
    //mainLight->translate(noma.X - previous.X, noma.Y - previous.Y -10, noma.Z - previous.Z);
    //mainLight->translate(0, 100, 0);
    Vector3f lightPosition = Vector3f(mainLight->getPosition().x, mainLight->getPosition().y, mainLight->getPosition().z);

    //GLfloat LightPosition[] = {lightPosition.X, lightPosition.Y, lightPosition.Z, 0.0};
    //glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    shadowMapFBO->BindForWriting();

    //Set Viewport, Projection and View
    glViewport(0, 0, screenWidth * SHADOW_Q, screenHeight * SHADOW_Q);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -20, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lightPosition.X / 1000, lightPosition.Y / 1000, lightPosition.Z / 1000, 0, 0, 0, 0, 1, 0);

    //setupMatrices(lightPosition.X, lightPosition.Y, lightPosition.Z, 0,0,0);

    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    //glDisable(GL_CULL_FACE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT); //Avoid self shadowing

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    drawSceneTree();

    //setTextureMatrix();

}

void TAGConnector::postEffectsPass() {

    glDisable(GL_FOG);

    //glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


    /**** DOF Pass ****/
    if (graphicsQuality > 1) {
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, auxiliarTex, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glMatrixMode(GL_PROJECTION);
        glDisable(GL_DEPTH_TEST);
        glLoadIdentity();

        glOrtho(0, screenWidth, screenHeight, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor4f(1, 1, 1, 1);
        glDisable(GL_LIGHTING);


        glUseProgram(DOFShader.program());
        glUniform2fARB(DOFShader.UniformLocations[0], screenWidth, screenHeight);
        glUniform1iARB(DOFShader.UniformLocations[1], 0);
        glUniform1iARB(DOFShader.UniformLocations[2], 1);


        sceneFBO->BindForReading(0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthTexture);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);

        glTexCoord2d(0, 1);
        glVertex3f(0, 0, 0);

        glTexCoord2d(0, 0);
        glVertex3f(0, screenHeight, 0);

        glTexCoord2d(1, 0);
        glVertex3f(screenWidth, screenHeight, 0);

        glTexCoord2d(1, 1);
        glVertex3f(screenWidth, 0, 0);

        glEnd();

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /**** Chromatic Aberration Pass ****/

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();

    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1, 1, 1, 1);
    glDisable(GL_LIGHTING);

    if (graphicsQuality > 0) {
        glUseProgram(postShader.program());
        glUniform2fARB(postShader.UniformLocations[0], screenWidth, screenHeight);
        glUniform1iARB(postShader.UniformLocations[1], 0);

        if (graphicsQuality > 1) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, auxiliarTex);
        } else {
            sceneFBO->BindForReading(0);
        }

    } else {
        sceneFBO->BindForReading(0);
        glUseProgram(0);
    }

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2d(0, 1);
    glVertex3f(0, 0, 0);

    glTexCoord2d(0, 0);
    glVertex3f(0, screenHeight, 0);

    glTexCoord2d(1, 0);
    glVertex3f(screenWidth, screenHeight, 0);

    glTexCoord2d(1, 1);
    glVertex3f(screenWidth, 0, 0);

    glEnd();

    //Render SUN above everything

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

    glActiveTexture(GL_TEXTURE0);
    
    if(graphicsQuality > 0)
        glBindTexture(GL_TEXTURE_2D, sunTextures[3]);
    else
        glBindTexture(GL_TEXTURE_2D, sunTextures[0]);
    
    glEnable(GL_TEXTURE_2D);
    glUseProgram(0);
    glBegin(GL_QUADS);

    glTexCoord2d(0, 1);
    glVertex3f(0, 0, 0);

    glTexCoord2d(0, 0);
    glVertex3f(0, screenHeight, 0);

    glTexCoord2d(1, 0);
    glVertex3f(screenWidth, screenHeight, 0);

    glTexCoord2d(1, 1);
    glVertex3f(screenWidth, 0, 0);

    glEnd();
    glUseProgram(0);

    glDisable(GL_TEXTURE_2D);

}

void TAGConnector::skyRender() {

    Vector3 SunCDir = SunCPos;
    SunCDir.normalize();

    Vector3 SunWPos = SunCPos + Vector3(0, 4, -13);
    float RefractionFactor = (1.0f - sqrt(max(0.0f, SunCDir.y)));
    Vector3 SunColor = Vector3(0.0f, 0.5f, 1.0f) * RefractionFactor;
    SunColor = Vector3(1.0 - SunColor.x, 1.0 - SunColor.y, 1.0 - SunColor.z);

    Vector3 LightColor = Vector3(0.0f, 0.25f, 0.5f) * RefractionFactor;
    LightColor = Vector3(1.0 - LightColor.x, 1.0 - LightColor.y, 1.0 - LightColor.z);

    float AmbientIntensity = 0.0625f + 0.1875f * min(1.0f, max(0.0f, (0.375f + SunCDir.y) / 0.25f));
    float DiffuseIntensity = 0.75f * min(1.0f, max(0.0f, (0.03125f + SunCDir.y) / 0.0625f));

    glViewport(0, 0, screenWidth, screenHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) screenWidth / (float) screenHeight, 1, 40000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(1.0f, 3.0f, 1.0f);
    glTranslatef(0.0f, -203.0f, 0.0f);

    //Matrix4 matrixWorld;


    //matrixWorld.translate(0.0, -203.f, 0.0f);
    //matrixWorld.scale(1.0, 3.0, 1.0);
    //matrixWorld.rotateY(xrot);

    //glMultMatrixf(matrixWorld.getTranspose());

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glUseProgram(skyShader.program());
    glUniform1iARB(skyShader.UniformLocations[0], glutGet(GLUT_ELAPSED_TIME) / 10);

    GLfloat sunDir[] = {SunCDir.x, SunCDir.y, SunCDir.z};
    glUniform3fv(glGetUniformLocation(skyShader.program(), "v3LightPos"), 1, sunDir);
    glUniform1f(glGetUniformLocation(skyShader.program(), "cameraRotation"), xrot);
    glDrawArrays(GL_TRIANGLES, 0, 112 * 3);

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);

    ambientColor[0] = ambientColor[1] = ambientColor[2] = AmbientIntensity;
    ambientColor[3] = 1.0f;

    diffuseColor[0] = LightColor.x * DiffuseIntensity;
    diffuseColor[1] = LightColor.y * DiffuseIntensity;
    diffuseColor[2] = LightColor.z * DiffuseIntensity;
    diffuseColor[3] = 1.0f;

    sunPosition[0] = SunWPos.x;
    sunPosition[1] = SunWPos.y;
    sunPosition[2] = SunWPos.z;
    sunPosition[3] = 1.0f;

}

void TAGConnector::sunRender() {

    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, screenWidth, screenHeight);
    glBindTexture(GL_TEXTURE_2D, 0);

    Matrix4 ViewMatrix = Matrix4((float *) modelview);
    Matrix4 ProjectionMatrix = Matrix4((float *) projection);
    Matrix4 BiasMatrix = Matrix4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);
    Matrix4 VPB = BiasMatrix * ProjectionMatrix * ViewMatrix;
    Vector3 SunWPos = SunCPos + Vector3(0, 4, -13);
    Vector3 Z = Vector3(0.0, 0.0, 1.0);

    Vector3 SunCDir = SunCPos;
    SunCDir.normalize();

    Vector4 SunPosProj = VPB * Vector4(SunWPos.x, SunWPos.y, SunWPos.z, 1.0f);
    SunPosProj /= SunPosProj.w;
    static float sunPosProj[4] = {SunPosProj.x, SunPosProj.y, SunPosProj.z, SunPosProj.w};

    float RefractionFactor = (1.0f - sqrt(max(0.0f, SunCDir.y)));
    Vector3 SunColor = Vector3(0.0f, 0.5f, 1.0f) * RefractionFactor;
    SunColor = Vector3(1.0 - SunColor.x, 1.0 - SunColor.y, 1.0 - SunColor.z);

    GLfloat sunColor[3] = {SunColor.x, SunColor.y, SunColor.z};

    // render sun sphere
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[1], 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(modelview);
    double pl[] = {0.0f, 1.0f, 0.0f, 13.0};
    glClipPlane(GL_CLIP_PLANE0, pl);
    glEnable(GL_CLIP_PLANE0);
    glTranslatef(SunWPos.x, SunWPos.y, SunWPos.z);
    glColor3fv(sunColor);
    glEnable(GL_CULL_FACE);
    GLUquadric *obj = gluNewQuadric();
    gluSphere(obj, SunR, 16, 16);
    gluDeleteQuadric(obj);
    glDisable(GL_CULL_FACE);
    glDisable(GL_CLIP_PLANE0);


    //Hide if geometry is above

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[0], 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sunTextures[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glUseProgram(sunDepthTest);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
    glUseProgram(0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (graphicsQuality > 0) {
        //Low blur horizontal
        
        int lowWidth = 1;
        int highWidth = 2;
        
        if(graphicsQuality == 1){
            highWidth = 5;
        }

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[3], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTextures[0]);
        glUseProgram(blurH.program());
        glUniform1i(glGetUniformLocation(blurH.program(), "Width"), lowWidth);
        glUniform1f(glGetUniformLocation(blurH.program(), "odw"), 0.005);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        //Low blur vertical

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[1], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTextures[3]);
        glUseProgram(blurV.program());
        glUniform1i(glGetUniformLocation(blurV.program(), "Width"), lowWidth);
        glUniform1f(glGetUniformLocation(blurV.program(), "odh"), 0.005);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);


        //High blur horizontal

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[3], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTextures[1]);
        glUseProgram(blurH.program());
        glUniform1i(glGetUniformLocation(blurH.program(), "Width"), highWidth);
        glUniform1f(glGetUniformLocation(blurH.program(), "odw"), 0.01);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        //High blur vertical

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[2], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, sunTextures[3]);
        glUseProgram(blurV.program());
        glUniform1i(glGetUniformLocation(blurV.program(), "Width"), highWidth);
        glUniform1f(glGetUniformLocation(blurV.program(), "odh"), 0.01);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sunTextures[3], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
        //glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTextures[1]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sunTextures[2]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, dirtTexture->getTexture());
        glUseProgram(sunRaysLensFlareHalo.program());
        glUniform2fv(glGetUniformLocation(sunRaysLensFlareHalo.program(), "SunPosProj"), 1, sunPosProj);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glUseProgram(0);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void TAGConnector::setupMatrices(float position_x, float position_y, float position_z, float lookAt_x, float lookAt_y, float lookAt_z) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) screenWidth / (float) screenHeight, 1, 40000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position_x, position_y, position_z, lookAt_x, lookAt_y, lookAt_z, 0, 1, 0);

}

void TAGConnector::setTextureMatrix(void) {

    static double modelView[16];
    static double projection[16];

    // This is matrix transform every coordinate x,y,z
    // x = x* 0.5 + 0.5 
    // y = y* 0.5 + 0.5 
    // z = z* 0.5 + 0.5 
    // Moving from unit cube [-1,1] to [0,1]  
    const GLdouble bias[16] = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    };

    // Grab modelview and transformation matrices
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    glActiveTextureARB(GL_TEXTURE7);
    glMatrixMode(GL_TEXTURE);

    glLoadIdentity();
    glLoadMatrixd(bias);

    // concatating all matrice into one.
    glMultMatrixd(projection);
    glMultMatrixd(modelView);


    // Go back to normal matrix mode
    glMatrixMode(GL_MODELVIEW);
}
