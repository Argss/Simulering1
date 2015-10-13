#include <iostream>
#include <string>
#include <sstream>
#include "SF_src/OpenGLStuff.h"
#include "SF_src/DemoHandler.h"
#include "physicshandler/PhysicsHandler.h"

/*#include "examples/f1_basics/DemoEnvironmentExample.h"
#include "examples/f1_basics/BouncingBall.h"
#include "examples/f2_vectorPlane/BouncingBallWithCollision.h"
#include "examples/f2_vectorPlane/ProjectPointOnLinjeThroughOrigo.h"
#include "examples/f2_vectorPlane/ProjectPointOnArbitraryLine.h"
#include "examples/f2_vectorPlane/DistanceToPlane.h"
#include "examples/f3_particlePhysics/FreeFall.h"
#include "examples/f3_particlePhysics/FirstPhysicsHandlerDemo.h"
#include "examples/f3_particlePhysics/SuperG.h"
#include "examples/f3_particlePhysics/BallAndPlane.h"
#include "examples/f3_particlePhysics/SpaceBall.h"
#include "examples/f4_springs/FirstSpring.h"
#include "examples/f4_springs/StiffSpring.h"
#include "examples/f4_springs/RestLengthSpring.h"
#include "examples/f4_springs/BallCannon.h"*/

#include "EmptyDemo.h"
#include "SpaceDemo.h"

using namespace std;


/*
 The entry point for the program.
 You need to add your demos before you call start.
 */
int main(int argc, char* argv[])
{
	DemoHandler::inst().addDemo(new SpaceDemo());
	DemoHandler::inst().addDemo(new EmptyDemo());

    
    start(argc,argv);//function in "OpenGLStuff"
    
    return 0;
};

/*
 (c)2014 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */