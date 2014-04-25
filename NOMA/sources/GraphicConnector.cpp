/* 
 * File:   GraphicConnector.cpp
 * Author: laurasirventcollado
 * 
 * Created on 24 de enero de 2014, 18:10
 */

#include "../headers/GraphicConnector.h"
#include "../headers/State.h"
#include "../headers/Game.h"
#include "../headers/SteeringBehaviors.h"

GraphicConnector::GraphicConnector() {
}

GraphicConnector::GraphicConnector(const GraphicConnector& orig) {
}

GraphicConnector::~GraphicConnector() {
}

void GraphicConnector::init(int screenWidth, int screenHeight, bool fullScreen) {
    em = EventManager::Instance();
    SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
    params.DriverType = video::EDT_OPENGL;
    params.DeviceType = EIDT_BEST;
    params.AntiAlias = 0;
    params.Fullscreen = fullScreen;
    params.WindowSize = dimension2d<u32>(screenWidth, screenHeight);
    params.IgnoreInput = false;
    params.EventReceiver = em;
    params.Vsync = true;
    device = createDeviceEx(params);
    //device = createDevice(video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 16, fullScreen, false, false, em);
    device->setWindowCaption(L"NOMA");
    driver = device->getVideoDriver();
    guienv = device->getGUIEnvironment();
    smgr = device->getSceneManager();

#ifdef _IRR_OSX_PLATFORM_
    device->getFileSystem()->changeWorkingDirectoryTo("noma.app");
    device->getFileSystem()->changeWorkingDirectoryTo("Contents");
    device->getFileSystem()->changeWorkingDirectoryTo("Resources");
#else
    device->getFileSystem()->changeWorkingDirectoryTo("resources");
#endif
 

    //Environment DEMO
    mainFont = guienv->getFont("NOMA-36.bmp");
    background = driver->getTexture("fondoIA.png");
    IGUIFont * font = guienv->getFont("NOMA-18.bmp");
    IGUIFont * font2 = guienv->getFont("fontlucida.png");
    textFont = font;
    
    IGUISkin* skin = guienv->getSkin();
    skin->setFont(font);
    skin->setFont(font2, EGDF_TOOLTIP);
    skin->setColor(irr::gui::EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));

}

void GraphicConnector::resumeScene() {
    ILightSceneNode* light1 = smgr->addLightSceneNode(0, core::vector3df(0, 200, 0), video::SColorf(1, 1, 1), 100.0f, 1);
    smgr->setAmbientLight(SColor(255, 255, 255, 255));

    ICameraSceneNode * camera = smgr->addCameraSceneNode(0, core::vector3df(0.0f, 3000.0f, 0.0f), core::vector3df(0.0f, 0.0f, 0.0f), -1);
    smgr->setActiveCamera(camera);
}

void GraphicConnector::addGUIEntities(vector<MenuItem> elements) {
    for (int i = 0; i < elements.size(); i++) {

        IGUIButton * b = guienv->addButton(rect<s32>(driver->getCurrentRenderTargetSize().Width / 2 - elements[i].x2 / 2, elements[i].y1, driver->getCurrentRenderTargetSize().Width / 2 + elements[i].x2 / 2, elements[i].y2), 0, i, elements[i].title, elements[i].tooltip);
        guiElements.push_back(b);
    }
}

void GraphicConnector::deleteGUIEntities() {

    guienv->clear();
}

void GraphicConnector::setPosition(int index, Vector3f position) {

    nodes[index]->setPosition(vector3df(position.X, position.Y, position.Z));
}

void GraphicConnector::setRotation(int index, float deg) {

    nodes[index]->setRotation(vector3df(0, deg, 0));
}

void GraphicConnector::setRotation(int index, Quaternion q) {

    vector3df euler;
    quaternion irrQuat(q.X, q.Y, q.Z, q.W);
    irrQuat.toEuler(euler);
    euler *= RADTODEG;
    nodes[index]->setRotation(euler);
}

void GraphicConnector::setFollowCamera(int index) {

    smgr->getActiveCamera()->setPosition(vector3df(nodes[index]->getPosition().X, 20, nodes[index]->getPosition().Z - 30));
    smgr->getActiveCamera()->setTarget(vector3df(nodes[index]->getPosition().X, nodes[index]->getPosition().Y, nodes[index]->getPosition().Z));

}

void GraphicConnector::beginScene(float r, float g, float b) {

    driver->beginScene(true, true, SColor(100, r, g, b)); //double buffer
}

void GraphicConnector::draw3DElements() {
    smgr->drawAll();
}

void GraphicConnector::drawGUIElements() {
    guienv->drawAll();
}

void GraphicConnector::endScene() {
    driver->endScene();
}

void GraphicConnector::loadMesh(std::string filename) {

    IMesh* mesh = smgr->getMesh(filename.c_str());
    IMeshSceneNode *node = smgr->addMeshSceneNode(mesh);
    node->setPosition(vector3df(0, -1, 0));
    node->setMaterialFlag(EMF_LIGHTING, true);

}

void GraphicConnector::addGameEntity(BaseGameEntity* entity, std::string filename) {

    //IMesh* mesh = smgr->getMesh(filename.c_str());
    //IMeshSceneNode *node = smgr->addMeshSceneNode(mesh);   
    IAnimatedMesh* mesh = smgr->getMesh(filename.c_str());
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setPosition(vector3df(entity->getPosition().X, entity->getPosition().Y, entity->getPosition().Z));
    node->setMD2Animation("Walk");
    node->setAnimationSpeed(120);
    nodes.push_back(node);
}

void GraphicConnector::addCubeGameEntity(BaseGameEntity *entity) {

    IMeshSceneNode * node = smgr->addCubeSceneNode(2.f);
    node->setPosition(vector3df(entity->getPosition().X, entity->getPosition().Y, entity->getPosition().Z));
    //node->setMaterialFlag(EMF_LIGHTING, true);

    nodes.push_back(node);
}

void GraphicConnector::setTexture(int index, std::string filename) {

    nodes[index]->setMaterialFlag(EMF_LIGHTING, true);
    nodes[index]->setMaterialTexture(0, driver->getTexture(filename.c_str()));
}

void GraphicConnector::draw2DText(std::string text, Vector3f upperCorner, Vector3f bottomCorner, FontSize size) {

    if (size == Small)
        guienv->getBuiltInFont()->draw(stringw(text.c_str()).c_str(), rect<s32>(upperCorner.X, upperCorner.Y, bottomCorner.X, bottomCorner.Y), SColor(255, 255, 255, 255));
    else if (size == Medium)
        textFont->draw(stringw(text.c_str()).c_str(), rect<s32>(upperCorner.X, upperCorner.Y, bottomCorner.X, bottomCorner.Y), SColor(255, 255, 255, 255));
    else if (size == Large)
        mainFont->draw(stringw(text.c_str()).c_str(), rect<s32>(upperCorner.X, upperCorner.Y, bottomCorner.X, bottomCorner.Y), SColor(255, 255, 255, 255));
}

void GraphicConnector::add3DTextToEntity(std::string text) {

    ITextSceneNode * t = smgr->addTextSceneNode(guienv->getBuiltInFont(), stringw(text.c_str()).c_str(), SColor(255, 255, 255, 255), 0, vector3df(0, 0, 0));
    entitiesTexts.push_back(t);

}

void GraphicConnector::set3DTextContent(int index, std::string text) {

    entitiesTexts[index]->setText(stringw(text.c_str()).c_str());
}

void GraphicConnector::set3DTextPosition(int index, Vector3f position) {

    entitiesTexts[index]->setPosition(vector3df(position.X, position.Y + 2.5f, position.Z));
}

void GraphicConnector::addButton(std::string text, Vector3f upperCorner, Vector3f bottomCorner, int id) {
    guiElements.push_back(guienv->addButton(rect<s32>(upperCorner.X, upperCorner.Y, bottomCorner.X, bottomCorner.Y), 0, id, stringw(text.c_str()).c_str(), L""));
}

/*
 DEBUG INTERFACE FUNCTIONS
 */

void GraphicConnector::addRadiusToEntity(int index, float radius, float propagation, float mood, float trust) {

    IMeshSceneNode * rad = smgr->addSphereSceneNode(0);
    smgr->getMeshManipulator()->setVertexColors(rad->getMesh(), SColor(10, 255, 0, 0));
    rad->setMaterialFlag(video::EMF_WIREFRAME, !rad->getMaterial(0).Wireframe);
    entitiesRadius.push_back(rad);

    if (propagation > 0 && mood > 0 && trust > 0) {
        IAnimatedMesh * plane = smgr->addHillPlaneMesh("groundPlane", core::dimension2d<f32>(2, 2), core::dimension2d<u32>(1, 1), 0, 0.0f, core::dimension2d<f32>(0, 0), core::dimension2d<f32>(1, 1));

        IAnimatedMeshSceneNode * moodRadius = smgr->addAnimatedMeshSceneNode(plane);
        moodRadius->setMaterialTexture(0, driver->getTexture("moodRadius.png"));
        moodRadius->setMaterialFlag(EMF_LIGHTING, true);
        moodRadius->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

        IAnimatedMeshSceneNode * trustRadius = smgr->addAnimatedMeshSceneNode(plane);
        trustRadius->setMaterialTexture(0, driver->getTexture("trustRadius.png"));
        trustRadius->setMaterialFlag(EMF_LIGHTING, true);
        trustRadius->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

        IAnimatedMeshSceneNode * propRadius = smgr->addAnimatedMeshSceneNode(plane);
        propRadius->setMaterialTexture(0, driver->getTexture("propagationRadius.png"));
        propRadius->setMaterialFlag(EMF_LIGHTING, true);
        propRadius->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

        moodRadius->setScale(vector3df(mood, mood, mood));
        trustRadius->setScale(vector3df(trust, trust, trust));
        propRadius->setScale(vector3df(propagation, propagation, propagation));

        debugMoodCitizenRadius.push_back(moodRadius);
        debugTrustCitizenRadius.push_back(trustRadius);
        debugPropagationCitizenRadius.push_back(propRadius);
    }
}

void GraphicConnector::setRadiusPosition(int index, Vector3f position) {

    entitiesRadius[index]->setPosition(vector3df(position.X, position.Y, position.Z));
    if (index > 0 && index-1 < debugMoodCitizenRadius.size()) {
        debugMoodCitizenRadius[index-1]->setPosition(vector3df(position.X, position.Y, position.Z));
        debugTrustCitizenRadius[index-1]->setPosition(vector3df(position.X, position.Y, position.Z));
        debugPropagationCitizenRadius[index-1]->setPosition(vector3df(position.X, position.Y, position.Z));
    }
}

void GraphicConnector::setRadius(int index, float mood, float trust) {

    debugMoodCitizenRadius[index - 1]->setScale(vector3df(mood, mood, mood));
    debugTrustCitizenRadius[index - 1]->setScale(vector3df(trust, trust, trust));
}

void GraphicConnector::addWaypoints(PGraph* waypoints, float radius) {

    for (int i = 0; i < waypoints->getNumberOfPNodes(); i++) {

        IGUIFont * font = guienv->getBuiltInFont();
        ITextSceneNode * t = smgr->addTextSceneNode(font, stringw(i).c_str(), SColor(255, 255, 255, 255), 0, vector3df(waypoints->getPNode(i)->getPosition().X, waypoints->getPNode(i)->getPosition().Y - 3, waypoints->getPNode(i)->getPosition().Z));
        entitiesRadius.push_back(t);

        IMeshSceneNode * point = smgr->addSphereSceneNode(.3f);
        point->setPosition(vector3df(waypoints->getPNode(i)->getPosition().X, waypoints->getPNode(i)->getPosition().Y, waypoints->getPNode(i)->getPosition().Z));
        smgr->getMeshManipulator()->setVertexColors(point->getMesh(), SColor(255, 255, 0, 255));
        point->setMaterialFlag(EMF_LIGHTING, true);
        entitiesRadius.push_back(point);

        /*IMeshSceneNode * point2 = smgr->addSphereSceneNode(radius);
        point2->setMaterialFlag(video::EMF_WIREFRAME, !point2->getMaterial(0).Wireframe);
        point2->setPosition(vector3df(waypoints->getPNode(i)->getPosition().X, waypoints->getPNode(i)->getPosition().Y, waypoints->getPNode(i)->getPosition().Z));
        entitiesRadius.push_back(point2);*/

    }
}

void GraphicConnector::deleteEntities() {

    smgr->clear();

    /*
    for(int i = 0; i < nodes.size(); i++){
        nodes[i]->remove();
        nodes[i] = NULL;
    }
    
    for(int i = 0; i < entitiesTexts.size(); i++){
        delete(entitiesTexts[i]);
        entitiesTexts[i] = NULL;
        delete(entitiesRadius[i]);
        entitiesRadius[i] = NULL;
        delete(debugMoodCitizenRadius[i]);
        debugMoodCitizenRadius[i] = NULL;
        delete(debugTrustCitizenRadius[i]);
        debugTrustCitizenRadius[i] = NULL;
        delete(debugPropagationCitizenRadius[i]);
        debugPropagationCitizenRadius[i] = NULL;
    }*/
    guiElements.clear();
    nodes.clear();
    entitiesTexts.clear();
    entitiesRadius.clear();
    pathfindingRoutes.clear();
    debugMoodCitizenRadius.clear();
    debugTrustCitizenRadius.clear();
    debugPropagationCitizenRadius.clear();

}

void GraphicConnector::drawWayroutes(PGraph* waypoints) {

    SMaterial m;
    m.Lighting = false;
    driver->setMaterial(m);
    driver->setTransform(video::ETS_WORLD, core::matrix4());
    for (int i = 0; i < waypoints->getNumberOfPNodes(); i++) {
        std::list<PEdge *> edges = waypoints->getPEdgeList(i);
        for (std::list<PEdge *>::iterator it = edges.begin(); it != edges.end(); ++it) {

            PEdge *e = *it;
            PNode *f = waypoints->getPNode(e->getFromNode());
            PNode *t = waypoints->getPNode(e->getToNode());
            driver->draw3DLine(vector3df(f->getPosition().X, f->getPosition().Y, f->getPosition().Z), vector3df(t->getPosition().X, t->getPosition().Y, t->getPosition().Z), SColor(255, 0, 255, 255));
        }
    }
}

void GraphicConnector::setDebugInterfaceVisible(bool visible) {

    int j = 0;
    int k = 0;

    for (int i = 0; i < entitiesRadius.size(); i++) {

        entitiesRadius[i]->setVisible(visible);
        entitiesTexts[j]->setVisible(visible);
        debugMoodCitizenRadius[k]->setVisible(visible);
        debugTrustCitizenRadius[k]->setVisible(visible);
        debugPropagationCitizenRadius[k]->setVisible(visible);

        if (j < entitiesTexts.size() - 1) j++;
        if (k < debugMoodCitizenRadius.size() - 1) k++;
    }

}

void GraphicConnector::updatePathfindingRoutes(std::string route) {

    pathfindingRoutes.push_back(stringw(route.c_str()).c_str());
}

void GraphicConnector::printPathfindingRoutes() {

    SMaterial m;
    m.Lighting = false;
    driver->setMaterial(m);
    driver->setTransform(video::ETS_WORLD, core::matrix4());
    for (int i = 0; i < pathfindingRoutes.size(); i++) {
        guienv->getBuiltInFont()->draw(pathfindingRoutes[i], rect<s32>(10, 50 + 10 * i, 100, 90 + 10 * i), SColor(255, 255, 255, 255));
    }
}

void GraphicConnector::moveCameraControl(IMeshSceneNode* ch) {

    core::position2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
    scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    core::vector3df cameraPos = camera->getAbsolutePosition();

    float change_x = (cursorPos.X - 0.5) * 256.0f;
    float change_y = (cursorPos.Y - 0.5) * 256.0f;
    direction += change_x;
    zdirection -= change_y;
    if (zdirection <-90)
        zdirection = -90;
    else

        if (zdirection > 90)
        zdirection = 90;
    device->getCursorControl()->setPosition(0.5f, 0.5f);

    core::vector3df playerPos = ch->getPosition();

    float xf = playerPos.X - cos(direction * irr::core::PI / 180.0f) * 64.0f;
    float yf = playerPos.Y - sin(zdirection * irr::core::PI / 180.0f) * 64.0f;
    float zf = playerPos.Z + sin(direction * irr::core::PI / 180.0f) * 64.0f;

    camera->setPosition(core::vector3df(xf, yf, zf));
    camera->setTarget(core::vector3df(playerPos.X, playerPos.Y + 25.0f, playerPos.Z));
    ch->setRotation(core::vector3df(0, direction, 0));
}

void GraphicConnector::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {

    //cout<<from.getX()<<","<<from.getY()<<","<<from.getZ()<<endl;
    SMaterial m;
    m.Lighting = false;
    driver->setMaterial(m);
    driver->setTransform(video::ETS_WORLD, core::matrix4());
    irr::video::SColor newColor(255, (irr::u32)color[0], (irr::u32)color[1], (irr::u32)color[2]);
    if (color[0] <= 1.0 && color[0] > 0.0)
        newColor.setRed((irr::u32)(color[0]*255.0));
    if (color[1] <= 1.0 && color[1] > 0.0)
        newColor.setGreen((irr::u32)(color[1]*255.0));
    if (color[2] <= 1.0 && color[2] > 0.0)
        newColor.setBlue((irr::u32)(color[2]*255.0));

    this->driver->draw3DLine(irr::core::vector3df(from[0], from[1], from[2]), irr::core::vector3df(to[0], to[1], to[2]), newColor);
}