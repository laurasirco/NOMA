#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "PGraph.h"
#include "PEdge.h"
#include "PNode.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>

class GLDebugDraw : public btIDebugDraw {
    int m_debugMode;

public:

    GLDebugDraw() : m_debugMode(0) {

    }

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
        //      if (m_debugMode > 0)
        glBegin(GL_LINES);
        //glColor3f(color.getX(), color.getY(), color.getZ());
        glColor3f(1.0,1.0,1.0);
        glVertex3d(from.getX(), from.getY(), from.getZ());
        glColor3f(1.0,1.0,1.0);
        //glColor3f(color.getX(), color.getY(), color.getZ());
        glVertex3d(to.getX(), to.getY(), to.getZ());
        glEnd();

    }

    void setDebugMode(int debugMode) {
        m_debugMode = debugMode;
    }

    void draw3dText(const btVector3& location, const char* textString) {
        //glRasterPos3f(location.x(),  location.y(),  location.z());
        //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
    }

    void reportErrorWarning(const char* warningString) {
        std::cout << warningString << std::endl;
    }

    void drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
        {
            //btVector3 to=pointOnB+normalOnB*distance;
            //const btVector3&from = pointOnB;
            //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);   

            //GLDebugDrawer::drawLine(from, to, color);

            //glRasterPos3f(from.x(),  from.y(),  from.z());
            //char buf[12];
            //sprintf(buf," %d",lifeTime);
            //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
        }
    }

    int getDebugMode() const {
        return m_debugMode;
    }

    void drawPathfindingRoutes(PGraph *waypoints) {
        for (int i = 0; i < waypoints->getNumberOfPNodes(); i++) {
            std::list<PEdge *> edges = waypoints->getPEdgeList(i);
            for (std::list<PEdge *>::iterator it = edges.begin(); it != edges.end(); ++it) {

                PEdge *e = *it;
                PNode *f = waypoints->getPNode(e->getFromNode());
                PNode *t = waypoints->getPNode(e->getToNode());
                drawLine(btVector3(f->getPosition().X, f->getPosition().Y, f->getPosition().Z), btVector3(t->getPosition().X, t->getPosition().Y, t->getPosition().Z), btVector3(1.0,1.0,1.0));
            }
        }
    }

};
#endif

