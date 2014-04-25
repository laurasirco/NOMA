/* 
 * File:   TAGConnector.h
 * Author: iMac
 *
 * Created on 18 de febrero de 2014, 11:46
 */

#ifndef TAGCONNECTOR_H
#define	TAGCONNECTOR_H
#include <vector>
#include <string>
using namespace std;
#include "TNode.h"
#include "TResourceManager.h"
#include "TEntity.h"
#include "TTransformation.h"
#include "TCamera.h"
#include "TLight.h"
#include "TColor.h"
#include "TMesh.h"
#include "TShaderProgram.h"
#include "BaseGameEntity.h"
#include "TResourceAnimatedMesh.h"
#include "GLDebugDraw.h"
#include "TAnimatedMesh.h"
#include "TFBO.h"
#include "TShadowMap.h"

class TAGConnector {
public:
    TAGConnector();
    TAGConnector(const TAGConnector& orig);
    
    static void display();
    virtual ~TAGConnector();
    void init(int h, int w);
    TNode *createNode (TNode *parent, TEntity *entity);
    TTransformation *createTransformation() {TTransformation *transf = new TTransformation(); return transf; }
    TCamera *createCamera() {TCamera *camera = new TCamera(); return camera; }
    TLight *createLight() {TLight *light = new TLight(); return light; }
    TMesh *createMesh(std::string file);
    TAnimatedMesh *createAnimatedMesh(std::string file);
    static TNode* getScene() { return TAGConnector::scene;} 
    static void draw();
    static void redisplay() {glutPostRedisplay();}
    static void loopEvent() {glutCheckLoop();}
    static void close() { glutDestroyWindow(1); exit(0);}
    //Camera and lights
    int registerCamera(TNode *camera) { cameras.push_back(camera); return cameras.size(); }
    int registerLight(TLight *light) { lights.push_back(light); return lights.size(); }
    void setActiveCamera(int nCamera) {cameras[nCamera]->setActive(true); }
    //void setActiveLight(int nLight) {lights[nLight]->setActive(true); }
    void updateAmbientLightIntensity(float r, float g, float b, float a);
    //-----------------
    
    void addEntity(BaseGameEntity *entity, std::string meshName, std::string textureName);
    void addWorldEntity(Matrix4 transformation, std::string meshName, std::string textureName);
    void static checkMouse();
    
    static void setXRotation(float x){ xrot = x; }
    
    void clearSceneTree();
    
    static GLdouble * getModelviewMatrix(){ return modelview; }
    static GLdouble * getProjectionMatrix(){ return projection; }
    static GLint * getViewport(){ return viewport; }
    
    static void shadowPass();
    static void renderPass();
    static void postEffectsPass();
    static void skyRender();
    static void sunRender();
    static void drawGUIElements();
    static void drawSceneTree();
    static void debugRender(GLuint tex);
    static void setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z);
    static void setTextureMatrix(void);
    TResourceManager* getResourceManager() { return resourceManager; }

    static TShaderProgram getRenderShader(){ return renderShader; }
        
private:
    static TNode *scene;
    TResourceManager *resourceManager;
    static int screenHeight; static int screenWidth;
    
    //Camera and lights
    static vector<TLight *> lights;
    static vector<TNode *> cameras;
    static float xrot;
    static float yrot;
    
    static TTransformation * mainLight;
    
    //-----------------
    
    static float cont;
    static float prevMouseX;

    static GLDebugDraw * debugDraw;
    
    static GLdouble modelview[16];
    static GLdouble projection[16];
    static GLint viewport[4];
    
    //SHADOWS
    
    static TShadowMapFBO * shadowMapFBO;
    static Matrix4 shadowMatrix;
    static TShaderProgram renderShader;
    
    static TFBO * sceneFBO;
    
    //POST EFFECTS
    
    static TShaderProgram postShader;
    static TShaderProgram DOFShader;
    static GLuint auxiliarTex;
    
    //SKY
    
    static TShaderProgram skyShader;
    static float SunR;
    static Vector3 SunCPos, SunRotVec;
    static GLuint VBO;
    static GLfloat ambientColor[4];
    static GLfloat diffuseColor[4];
    static GLfloat sunPosition[4];
    
    //SUN
    
    static TShaderProgram sunDepthTest;
    static TShaderProgram blurH, blurV;
    static TShaderProgram sunRaysLensFlareHalo;
    static GLuint sunTextures[4];
    static GLuint depthTexture;
    static GLuint FBO;
    static TResourceTexture * dirtTexture;
    
    static TShaderProgram gaussianBlurH, gaussianBlurV;
    static float sunAngle;
    
    static int graphicsQuality;
    
};


#endif	/* TAGCONNECTOR_H */

