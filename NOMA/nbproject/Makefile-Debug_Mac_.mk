#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug_Mac_
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SimpleJSON/JSON.o \
	${OBJECTDIR}/SimpleJSON/JSONValue.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sources/AudioEngine.o \
	${OBJECTDIR}/sources/BadgetState.o \
	${OBJECTDIR}/sources/BaseGameEntity.o \
	${OBJECTDIR}/sources/BlankState.o \
	${OBJECTDIR}/sources/CalmState.o \
	${OBJECTDIR}/sources/Character.o \
	${OBJECTDIR}/sources/Citizen.o \
	${OBJECTDIR}/sources/CitizenState.o \
	${OBJECTDIR}/sources/DynamicEntity.o \
	${OBJECTDIR}/sources/EnvState.o \
	${OBJECTDIR}/sources/Environment.o \
	${OBJECTDIR}/sources/EventManager.o \
	${OBJECTDIR}/sources/FlockingBehaviors.o \
	${OBJECTDIR}/sources/FlockingState.o \
	${OBJECTDIR}/sources/FollowNomaState.o \
	${OBJECTDIR}/sources/Freetype.o \
	${OBJECTDIR}/sources/GUIBackground.o \
	${OBJECTDIR}/sources/GUIButton.o \
	${OBJECTDIR}/sources/GUIElement.o \
	${OBJECTDIR}/sources/GUIOrbit.o \
	${OBJECTDIR}/sources/GUISlider.o \
	${OBJECTDIR}/sources/GUIText.o \
	${OBJECTDIR}/sources/Game.o \
	${OBJECTDIR}/sources/GameState.o \
	${OBJECTDIR}/sources/GraphicConnector.o \
	${OBJECTDIR}/sources/GraphicEngine.o \
	${OBJECTDIR}/sources/HUD.o \
	${OBJECTDIR}/sources/LoginState.o \
	${OBJECTDIR}/sources/MainMenuState.o \
	${OBJECTDIR}/sources/MapState.o \
	${OBJECTDIR}/sources/Matrices.o \
	${OBJECTDIR}/sources/MovingEntity.o \
	${OBJECTDIR}/sources/NeutralState.o \
	${OBJECTDIR}/sources/Noma.o \
	${OBJECTDIR}/sources/Object.o \
	${OBJECTDIR}/sources/OptionMenuState.o \
	${OBJECTDIR}/sources/PEdge.o \
	${OBJECTDIR}/sources/PGraph.o \
	${OBJECTDIR}/sources/PNode.o \
	${OBJECTDIR}/sources/PRoute.o \
	${OBJECTDIR}/sources/Parser.o \
	${OBJECTDIR}/sources/Path.o \
	${OBJECTDIR}/sources/PathwalkingState.o \
	${OBJECTDIR}/sources/PhysicsEngine.o \
	${OBJECTDIR}/sources/PopupState.o \
	${OBJECTDIR}/sources/RegisterState.o \
	${OBJECTDIR}/sources/ResourceManager.o \
	${OBJECTDIR}/sources/ScriptLine.o \
	${OBJECTDIR}/sources/ServerConnector.o \
	${OBJECTDIR}/sources/StandState.o \
	${OBJECTDIR}/sources/State.o \
	${OBJECTDIR}/sources/SteeringBehaviors.o \
	${OBJECTDIR}/sources/TAGConnector.o \
	${OBJECTDIR}/sources/TAnimatedMesh.o \
	${OBJECTDIR}/sources/TCamera.o \
	${OBJECTDIR}/sources/TColor.o \
	${OBJECTDIR}/sources/TEntity.o \
	${OBJECTDIR}/sources/TFBO.o \
	${OBJECTDIR}/sources/TLODMesh.o \
	${OBJECTDIR}/sources/TLight.o \
	${OBJECTDIR}/sources/TMatrix4x4.o \
	${OBJECTDIR}/sources/TMesh.o \
	${OBJECTDIR}/sources/TNode.o \
	${OBJECTDIR}/sources/TParticles.o \
	${OBJECTDIR}/sources/TResource.o \
	${OBJECTDIR}/sources/TResourceAnimatedMesh.o \
	${OBJECTDIR}/sources/TResourceAnimatedMeshContainer.o \
	${OBJECTDIR}/sources/TResourceFont.o \
	${OBJECTDIR}/sources/TResourceLODMesh.o \
	${OBJECTDIR}/sources/TResourceManager.o \
	${OBJECTDIR}/sources/TResourceMesh.o \
	${OBJECTDIR}/sources/TResourceTexture.o \
	${OBJECTDIR}/sources/TShaderProgram.o \
	${OBJECTDIR}/sources/TShadowMap.o \
	${OBJECTDIR}/sources/TTransformation.o \
	${OBJECTDIR}/sources/TalkToNomaState.o \
	${OBJECTDIR}/sources/TenseState.o \
	${OBJECTDIR}/sources/WalkToPlaceState.o \
	${OBJECTDIR}/sources/World.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations
CXXFLAGS=-m32 -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-LBullet/lib -LSOIL/lib -LFreetype/lib -LIrrklang -lstdc++.6.0.9 -lBulletCollision -lBulletDynamics -lLinearMath -lBulletFileLoader -lBulletWorldImporter -lSOIL -lfreetype -lcurl.3 -lcurl.4 -lcurl -lirrklang

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noma

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noma: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noma ${OBJECTFILES} ${LDLIBSOPTIONS} -framework IOKit -framework OpenGL -framework Cocoa -framework Carbon -framework OpenGL -framework GLUT -LIrrlicht/lib/MacOSX -lIrrlicht -lstdc++.6.0.9

${OBJECTDIR}/SimpleJSON/JSON.o: SimpleJSON/JSON.cpp 
	${MKDIR} -p ${OBJECTDIR}/SimpleJSON
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/SimpleJSON/JSON.o SimpleJSON/JSON.cpp

${OBJECTDIR}/SimpleJSON/JSONValue.o: SimpleJSON/JSONValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/SimpleJSON
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/SimpleJSON/JSONValue.o SimpleJSON/JSONValue.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/sources/AudioEngine.o: sources/AudioEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/AudioEngine.o sources/AudioEngine.cpp

${OBJECTDIR}/sources/BadgetState.o: sources/BadgetState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/BadgetState.o sources/BadgetState.cpp

${OBJECTDIR}/sources/BaseGameEntity.o: sources/BaseGameEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/BaseGameEntity.o sources/BaseGameEntity.cpp

${OBJECTDIR}/sources/BlankState.o: sources/BlankState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/BlankState.o sources/BlankState.cpp

${OBJECTDIR}/sources/CalmState.o: sources/CalmState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/CalmState.o sources/CalmState.cpp

${OBJECTDIR}/sources/Character.o: sources/Character.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Character.o sources/Character.cpp

${OBJECTDIR}/sources/Citizen.o: sources/Citizen.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Citizen.o sources/Citizen.cpp

${OBJECTDIR}/sources/CitizenState.o: sources/CitizenState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/CitizenState.o sources/CitizenState.cpp

${OBJECTDIR}/sources/DynamicEntity.o: sources/DynamicEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/DynamicEntity.o sources/DynamicEntity.cpp

${OBJECTDIR}/sources/EnvState.o: sources/EnvState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/EnvState.o sources/EnvState.cpp

${OBJECTDIR}/sources/Environment.o: sources/Environment.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Environment.o sources/Environment.cpp

${OBJECTDIR}/sources/EventManager.o: sources/EventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/EventManager.o sources/EventManager.cpp

${OBJECTDIR}/sources/FlockingBehaviors.o: sources/FlockingBehaviors.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/FlockingBehaviors.o sources/FlockingBehaviors.cpp

${OBJECTDIR}/sources/FlockingState.o: sources/FlockingState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/FlockingState.o sources/FlockingState.cpp

${OBJECTDIR}/sources/FollowNomaState.o: sources/FollowNomaState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/FollowNomaState.o sources/FollowNomaState.cpp

${OBJECTDIR}/sources/Freetype.o: sources/Freetype.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Freetype.o sources/Freetype.cpp

${OBJECTDIR}/sources/GUIBackground.o: sources/GUIBackground.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUIBackground.o sources/GUIBackground.cpp

${OBJECTDIR}/sources/GUIButton.o: sources/GUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUIButton.o sources/GUIButton.cpp

${OBJECTDIR}/sources/GUIElement.o: sources/GUIElement.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUIElement.o sources/GUIElement.cpp

${OBJECTDIR}/sources/GUIOrbit.o: sources/GUIOrbit.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUIOrbit.o sources/GUIOrbit.cpp

${OBJECTDIR}/sources/GUISlider.o: sources/GUISlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUISlider.o sources/GUISlider.cpp

${OBJECTDIR}/sources/GUIText.o: sources/GUIText.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GUIText.o sources/GUIText.cpp

${OBJECTDIR}/sources/Game.o: sources/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Game.o sources/Game.cpp

${OBJECTDIR}/sources/GameState.o: sources/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GameState.o sources/GameState.cpp

${OBJECTDIR}/sources/GraphicConnector.o: sources/GraphicConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GraphicConnector.o sources/GraphicConnector.cpp

${OBJECTDIR}/sources/GraphicEngine.o: sources/GraphicEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/GraphicEngine.o sources/GraphicEngine.cpp

${OBJECTDIR}/sources/HUD.o: sources/HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/HUD.o sources/HUD.cpp

${OBJECTDIR}/sources/LoginState.o: sources/LoginState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/LoginState.o sources/LoginState.cpp

${OBJECTDIR}/sources/MainMenuState.o: sources/MainMenuState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/MainMenuState.o sources/MainMenuState.cpp

${OBJECTDIR}/sources/MapState.o: sources/MapState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/MapState.o sources/MapState.cpp

${OBJECTDIR}/sources/Matrices.o: sources/Matrices.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Matrices.o sources/Matrices.cpp

${OBJECTDIR}/sources/MovingEntity.o: sources/MovingEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/MovingEntity.o sources/MovingEntity.cpp

${OBJECTDIR}/sources/NeutralState.o: sources/NeutralState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/NeutralState.o sources/NeutralState.cpp

${OBJECTDIR}/sources/Noma.o: sources/Noma.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Noma.o sources/Noma.cpp

${OBJECTDIR}/sources/Object.o: sources/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Object.o sources/Object.cpp

${OBJECTDIR}/sources/OptionMenuState.o: sources/OptionMenuState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/OptionMenuState.o sources/OptionMenuState.cpp

${OBJECTDIR}/sources/PEdge.o: sources/PEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PEdge.o sources/PEdge.cpp

${OBJECTDIR}/sources/PGraph.o: sources/PGraph.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PGraph.o sources/PGraph.cpp

${OBJECTDIR}/sources/PNode.o: sources/PNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PNode.o sources/PNode.cpp

${OBJECTDIR}/sources/PRoute.o: sources/PRoute.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PRoute.o sources/PRoute.cpp

${OBJECTDIR}/sources/Parser.o: sources/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Parser.o sources/Parser.cpp

${OBJECTDIR}/sources/Path.o: sources/Path.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/Path.o sources/Path.cpp

${OBJECTDIR}/sources/PathwalkingState.o: sources/PathwalkingState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PathwalkingState.o sources/PathwalkingState.cpp

${OBJECTDIR}/sources/PhysicsEngine.o: sources/PhysicsEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PhysicsEngine.o sources/PhysicsEngine.cpp

${OBJECTDIR}/sources/PopupState.o: sources/PopupState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/PopupState.o sources/PopupState.cpp

${OBJECTDIR}/sources/RegisterState.o: sources/RegisterState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/RegisterState.o sources/RegisterState.cpp

${OBJECTDIR}/sources/ResourceManager.o: sources/ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/ResourceManager.o sources/ResourceManager.cpp

${OBJECTDIR}/sources/ScriptLine.o: sources/ScriptLine.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/ScriptLine.o sources/ScriptLine.cpp

${OBJECTDIR}/sources/ServerConnector.o: sources/ServerConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/ServerConnector.o sources/ServerConnector.cpp

${OBJECTDIR}/sources/StandState.o: sources/StandState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/StandState.o sources/StandState.cpp

${OBJECTDIR}/sources/State.o: sources/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/State.o sources/State.cpp

${OBJECTDIR}/sources/SteeringBehaviors.o: sources/SteeringBehaviors.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/SteeringBehaviors.o sources/SteeringBehaviors.cpp

${OBJECTDIR}/sources/TAGConnector.o: sources/TAGConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TAGConnector.o sources/TAGConnector.cpp

${OBJECTDIR}/sources/TAnimatedMesh.o: sources/TAnimatedMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TAnimatedMesh.o sources/TAnimatedMesh.cpp

${OBJECTDIR}/sources/TCamera.o: sources/TCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TCamera.o sources/TCamera.cpp

${OBJECTDIR}/sources/TColor.o: sources/TColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TColor.o sources/TColor.cpp

${OBJECTDIR}/sources/TEntity.o: sources/TEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TEntity.o sources/TEntity.cpp

${OBJECTDIR}/sources/TFBO.o: sources/TFBO.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TFBO.o sources/TFBO.cpp

${OBJECTDIR}/sources/TLODMesh.o: sources/TLODMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TLODMesh.o sources/TLODMesh.cpp

${OBJECTDIR}/sources/TLight.o: sources/TLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TLight.o sources/TLight.cpp

${OBJECTDIR}/sources/TMatrix4x4.o: sources/TMatrix4x4.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TMatrix4x4.o sources/TMatrix4x4.cpp

${OBJECTDIR}/sources/TMesh.o: sources/TMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TMesh.o sources/TMesh.cpp

${OBJECTDIR}/sources/TNode.o: sources/TNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TNode.o sources/TNode.cpp

${OBJECTDIR}/sources/TParticles.o: sources/TParticles.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TParticles.o sources/TParticles.cpp

${OBJECTDIR}/sources/TResource.o: sources/TResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResource.o sources/TResource.cpp

${OBJECTDIR}/sources/TResourceAnimatedMesh.o: sources/TResourceAnimatedMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceAnimatedMesh.o sources/TResourceAnimatedMesh.cpp

${OBJECTDIR}/sources/TResourceAnimatedMeshContainer.o: sources/TResourceAnimatedMeshContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceAnimatedMeshContainer.o sources/TResourceAnimatedMeshContainer.cpp

${OBJECTDIR}/sources/TResourceFont.o: sources/TResourceFont.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceFont.o sources/TResourceFont.cpp

${OBJECTDIR}/sources/TResourceLODMesh.o: sources/TResourceLODMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceLODMesh.o sources/TResourceLODMesh.cpp

${OBJECTDIR}/sources/TResourceManager.o: sources/TResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceManager.o sources/TResourceManager.cpp

${OBJECTDIR}/sources/TResourceMesh.o: sources/TResourceMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceMesh.o sources/TResourceMesh.cpp

${OBJECTDIR}/sources/TResourceTexture.o: sources/TResourceTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TResourceTexture.o sources/TResourceTexture.cpp

${OBJECTDIR}/sources/TShaderProgram.o: sources/TShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TShaderProgram.o sources/TShaderProgram.cpp

${OBJECTDIR}/sources/TShadowMap.o: sources/TShadowMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TShadowMap.o sources/TShadowMap.cpp

${OBJECTDIR}/sources/TTransformation.o: sources/TTransformation.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TTransformation.o sources/TTransformation.cpp

${OBJECTDIR}/sources/TalkToNomaState.o: sources/TalkToNomaState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TalkToNomaState.o sources/TalkToNomaState.cpp

${OBJECTDIR}/sources/TenseState.o: sources/TenseState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/TenseState.o sources/TenseState.cpp

${OBJECTDIR}/sources/WalkToPlaceState.o: sources/WalkToPlaceState.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/WalkToPlaceState.o sources/WalkToPlaceState.cpp

${OBJECTDIR}/sources/World.o: sources/World.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} $@.d
	$(COMPILE.cc) -g -IBullet/src -ISOIL/include -IFreetype/include -m32 -arch i386 -IIrrlicht/include -IIrrklang/include -Wdeprecated-declarations -MMD -MP -MF $@.d -o ${OBJECTDIR}/sources/World.o sources/World.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noma

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
