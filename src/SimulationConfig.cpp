//  SimulationConfig.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "SimulationConfig.hpp"






SimulationConfig:: ~SimulationConfig()
{
	//userInterface.exit();
}



void SimulationConfig::config(std::string simulatorTitle, std::string simulationMode, Quadtree* &rootQuadtree,  std::vector<Body *> &bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid, float &theta, double &G, float &e, float &dt)
{
	userInterface.config(simulatorTitle, simulationMode, rootQuadtree, bodies, bodiesAccelerations, vectorGrid, theta, G, e, dt);
	
	/*----------------------   2D plane coordinate system navigation  ----------------------*/
	coordinateSystem2D = {ofRectangle(-10000, -10000, 20000, 20000)};
	
	
	/*------------------------------------------------------------------   BARNES HUT, QUADTREE  ------------------------------------------------------------------*/
	bodyPool = ObjectPool<Body>(500000);
}



void SimulationConfig::setup(float &theta, double &G, float &e, float &dt)
{
	//userInterface.setup(theta, G, e, dt);
	
	/*----------------------   2D plane coordinate system navigation  ----------------------*/
	coordinateSystem2D = {ofRectangle(-10000, -10000, 20000, 20000)};
	
	
	/*------------------------------------------------------------------   BARNES HUT, QUADTREE  ------------------------------------------------------------------*/
	bodyPool = ObjectPool<Body>(500000);
}


void SimulationConfig::update(Quadtree* &rootQuadtree, float &theta, double &G, float &e, float &dt)
{
	//coordinateSystem2D.set(rootQuadtree->bounds);
	
	
	userInterface.update(theta, G, e, dt);
}



void SimulationConfig::draw(Quadtree* &rootQuadtree, std::vector<Body *> &bodies, ofVec2f* &bodiesAccelerations, double &G, float &dt,float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy)
{
	/*-----------   Draw things in the isolated coordinate system transform   -----------*/
	userInterface.drawICST(coordinateSystem2D, rootQuadtree, bodies, bodiesAccelerations, startMouse, dt);
	
	/*-----------   Draw things out of the isolated coordinate system transform   -----------*/
	int numBodies = bodies.size();
	userInterface.draw(G, dt, numBodies, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
}


void SimulationConfig::exit()
{
	userInterface.exit();
}

void SimulationConfig::keyPressed(int key)
{
	if (key == 'z')
	{
		coordinateSystem2D.resetCoordinateSystem();
		
	}
}

//--------------------------------------------------------------
void SimulationConfig::keyReleased(int key)
{
	userInterface.keyReleased(key);
}


void SimulationConfig::mouseDragged(int x, int y, int button, Quadtree* &rootQuadtree, std::vector<Body *> &bodies, float &theta, double &G)
{
	userInterface.mouseDragged(x, y, button);
	
	if (coordinateSystem2D.isDragging && button == 2) // Update offset based on mouse movement
	{
		Vec2D mousePos(x, y);
		Vec2D dragOffset = mousePos - coordinateSystem2D.dragStartPos;
		coordinateSystem2D.offset += dragOffset;
		coordinateSystem2D.dragStartPos = mousePos;
	}
	
	
	//
	/*
	 if (userInterface.applyForces->isOn && button == 0)
	 {
	 scaledMousePos.set(x * coordinateSystem2D.inverseZoomScale - coordinateSystem2D.offset.x, y * coordinateSystem2D.inverseZoomScale - coordinateSystem2D.offset.y);
	 offsetMouse = scaledMousePos - startMouse;  // Calculate the force vector based on mouse movement
	 userForceVector += offsetMouse;
	 }
	 
	 
	 if (userInterface.attractBodies->isOn && button == 0)
	 {
	 ofVec2f mousePos(x/ coordinateSystem2D.zoomScale - coordinateSystem2D.offset.x, y * coordinateSystem2D.inverseZoomScale - coordinateSystem2D.offset.y);
	 for (auto& body : bodies)
	 {
	 float distance = body->position.distance(mousePos);
	 ofVec2f force = ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale) - body->position;
	 force.normalize();
	 force *= G;
	 ComputeTreeForce(rootQuadtree, body, force, G, theta);
	 
	 if (distance >= 100)
	 {
	 body->applyForce(force);
	 }
	 else //body is now close to mouse
	 {
	 body->dampMotion(0.01);
	 }
	 }
	 }
	 
	 
	 if (userInterface.repelBodies->isOn)
	 {
	 for (auto& body : bodies)
	 {
	 ofVec2f force = body->position - ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale);
	 force.normalize();
	 force *= G;
	 body->applyForce(force);
	 }
	 }
	 
	 
	 //*/
	
	
	
	
	
	
	
	
	
	
}



void SimulationConfig::mousePressed(int x, int y, int button, std::vector<Body *> &bodies, float &theta, double &G, double &lastG, float &e, float &dt, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy)
{
	userInterface.mousePressed(x, y, button, theta, G, lastG, e, dt);
	
	//if (userInterface.tableManager->galaxyCreationMode)
	//{
	
	
	
	//}
	
	//
	/*
	 
	 if (userInterface.coldStartCreate->isPressed)
	 {
	 userInterface.makeGalaxy = !userInterface.makeGalaxy;
	 userInterface.createGalaxy->isOn = false;
	 userInterface.placeGalaxy = true;
	 if (userInterface.makeGalaxy)
	 {
	 userInterface.keplerOrbitCreate->isPressed = false;
	 userInterface.plummerModelCreate->isPressed = false;
	 userInterface.diskGalaxyCreate->isPressed = false;
	 userInterface.collidingDiskGalaxyCreate->isPressed = false;
	 userInterface.createGalaxy->isOn = false;
	 std::vector<Body *> galaxyBodies = ColdStartInitialConditions(userInterface.numBodies, userInterface.bodiesMass, bodyPool, userInterface.anchorMass, userInterface.galaxyRadius, ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale));
	 userInterface.coldStartCreate->isPressed = false;
	 
	 for (auto& galaxyBody : galaxyBodies)
	 {
	 bodies.emplace_back(galaxyBody);
	 }
	 galaxyBodies.clear();
	 }
	 }
	 
	 
	 
	 if (userInterface.keplerOrbitCreate->isPressed)
	 {
	 userInterface.makeGalaxy = !userInterface.makeGalaxy;
	 userInterface.createGalaxy->isOn = false;
	 userInterface.placeGalaxy = true;
	 if (userInterface.makeGalaxy)
	 {
	 userInterface.coldStartCreate->isPressed = false;
	 userInterface.plummerModelCreate->isPressed = false;
	 userInterface.diskGalaxyCreate->isPressed = false;
	 userInterface.collidingDiskGalaxyCreate->isPressed = false;
	 userInterface.createGalaxy->isOn = false;
	 std::vector<Body *> galaxyBodies = KeplerOrbitInitialConditions(userInterface.numBodies, userInterface.anchorMass, userInterface.bodiesMass, bodyPool, userInterface.galaxyRadius, ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y)* coordinateSystem2D.inverseZoomScale));
	 userInterface.keplerOrbitCreate->isPressed = false;
	 for (auto& galaxyBody : galaxyBodies)
	 {
	 bodies.emplace_back(galaxyBody);
	 }
	 galaxyBodies.clear();
	 
	 }
	 
	 }
	 if (userInterface.plummerModelCreate->isPressed)
	 {
	 userInterface.makeGalaxy = !userInterface.makeGalaxy;
	 userInterface.createGalaxy->isOn = false;
	 userInterface.placeGalaxy = true;
	 if (userInterface.makeGalaxy)
	 {
	 userInterface.coldStartCreate->isPressed = false;
	 userInterface.keplerOrbitCreate->isPressed = false;
	 userInterface.diskGalaxyCreate->isPressed = false;
	 userInterface.collidingDiskGalaxyCreate->isPressed = false;
	 std::vector<Body *> galaxyBodies = PlummerModelInitialConditions(userInterface.numBodies, userInterface.bodiesMass, bodyPool, userInterface.anchorMass, 1, userInterface.galaxyRadius, ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale));
	 userInterface.plummerModelCreate->isPressed = false;
	 for (auto& galaxyBody : galaxyBodies)
	 {
	 bodies.emplace_back(galaxyBody);
	 }
	 galaxyBodies.clear();
	 }
	 }
	 if (userInterface.diskGalaxyCreate->isPressed)
	 {
	 userInterface.makeGalaxy = !userInterface.makeGalaxy;
	 userInterface.createGalaxy->isOn = false;
	 userInterface.placeGalaxy = true;
	 if (userInterface.makeGalaxy)
	 {
	 userInterface.coldStartCreate->isPressed = false;
	 userInterface.keplerOrbitCreate->isPressed = false;
	 userInterface.plummerModelCreate->isPressed = false;
	 userInterface.collidingDiskGalaxyCreate->isPressed = false;
	 userInterface.createGalaxy->isOn = false;
	 
	 std::vector<Body *> galaxyBodies = DiskModelInitialConditions(userInterface.numBodies, userInterface.bodiesMass, bodyPool, userInterface.anchorMass, userInterface.galaxyRadius, ofVec2f((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale));
	 
	 userInterface.diskGalaxyCreate->isPressed = false;
	 for (auto& galaxyBody : galaxyBodies)
	 {
	 bodies.emplace_back(galaxyBody);
	 }
	 galaxyBodies.clear();
	 }
	 
	 }
	 if (userInterface.collidingDiskGalaxyCreate->isPressed)
	 {
	 userInterface.makeGalaxy = !userInterface.makeGalaxy;
	 userInterface.createGalaxy->isOn = false;
	 userInterface.placeGalaxy = true;
	 if (userInterface.makeGalaxy)
	 {
	 userInterface.coldStartCreate->isPressed = false;
	 userInterface.keplerOrbitCreate->isPressed = false;
	 userInterface.plummerModelCreate->isPressed = false;
	 userInterface.diskGalaxyCreate->isPressed = false;
	 
	 ofVec2f galaxyAnchorPoint((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale);
	 
	 std::vector<Body *> galaxyBodies = CollidingDiskModelInitialConditions(userInterface.numBodies, userInterface.bodiesMass, bodyPool, userInterface.anchorMass, userInterface.anchorMass*0.80, userInterface.galaxyRadius, userInterface.galaxyRadius*0.80, galaxyAnchorPoint*1.20, galaxyAnchorPoint*0.20);
	 
	 userInterface.collidingDiskGalaxyCreate->isPressed = false;
	 for (auto& galaxyBody : galaxyBodies)
	 {
	 bodies.emplace_back(galaxyBody);
	 }
	 galaxyBodies.clear();
	 }
	 }
	 
	 
	 
	 
	 
	 
	 
	 
	 if (userInterface.plummerModelReset->isPressed)
	 {
	 systemKineticEnergy = 0;
	 systemPotentialEnergy = 0;
	 systemEnergy = 0;
	 ResetObjectPool(bodyPool, bodies);
	 bodies = PlummerModelInitialConditions(5555, 5, bodyPool, 138875, 1, 1500, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	 userInterface.diskGalaxyReset->isPressed = false;
	 userInterface.collidingDiskReset->isPressed = false;
	 coordinateSystem2D.resetCoordinateSystem();
	 }
	 if (userInterface.diskGalaxyReset->isPressed)
	 {
	 systemKineticEnergy = 0;
	 systemPotentialEnergy = 0;
	 systemEnergy = 0;
	 ResetObjectPool(bodyPool, bodies);
	 
	 bodies = DiskModelInitialConditions(6666, 5, bodyPool, 50, 7777, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	 
	 
	 userInterface.plummerModelReset->isPressed = false;
	 userInterface.collidingDiskReset->isPressed = false;
	 coordinateSystem2D.resetCoordinateSystem();
	 }
	 if (userInterface.collidingDiskReset->isPressed)
	 {
	 systemKineticEnergy = 0;
	 systemPotentialEnergy = 0;
	 systemEnergy = 0;
	 ResetObjectPool(bodyPool, bodies);
	 
	 bodies = CollidingDiskModelInitialConditions(10000, 10, bodyPool, 180, 140, 10000, 6000, ofVec2f(ofGetWidth() * 1.5, ofGetHeight() * 1.5), ofVec2f(ofGetWidth() * 0.25, ofGetHeight() * 0.25));
	 
	 userInterface.plummerModelReset->isPressed = false;
	 userInterface.diskGalaxyReset->isPressed = false;
	 coordinateSystem2D.resetCoordinateSystem();
	 }
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 if (userInterface.applyForces->isOn && button == 0)
	 {
	 startMouse.set((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale);
	 userForceVector.set(0, 0);
	 userInterface.placeBodies->isOn = false;
	 userInterface.repelBodies->isOn = false;
	 userInterface.attractBodies->isOn = false;
	 userInterface.dampingBodies->isOn = false;
	 }
	 if (userInterface.placeBodies->isOn && button == 0 )
	 {
	 float mass = 25;
	 float spacing = mass;
	 float scaledX = (x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale;
	 float scaledY = (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale;
	 ;
	 float startX = scaledX - (2 * spacing) - (2 * mass); // Calculate the top-left position of the grid
	 float startY = scaledY - (2 * spacing) - (2 * mass);
	 for (int row = 0; row < 5; row++)         // Insert 25 equally sized bodies in a 5x5 grid
	 {
	 for (int col = 0; col < 5; col++)
	 {
	 float bodyX = startX + (col * (mass + spacing));// Calculate the position of the current body
	 float bodyY = startY + (row * (mass + spacing));
	 auto newBody = bodyPool.acquire();
	 newBody->setParameters(ofVec2f(bodyX, bodyY), ofVec2f(0, 0), mass); //set body with the calculated position and mass
	 bodies.emplace_back(newBody);
	 }
	 }
	 userInterface.applyForces->isOn = false;
	 userInterface.attractBodies->isOn = false;
	 userInterface.repelBodies->isOn = false;
	 userInterface.dampingBodies->isOn = false;
	 }
	 
	 
	 if (userInterface.attractBodies->isOn && button == 0 )
	 {
	 userInterface.applyForces->isOn = false;
	 userInterface.placeBodies->isOn = false;
	 userInterface.repelBodies->isOn = false;
	 userInterface.dampingBodies->isOn = false;
	 }
	 if (userInterface.repelBodies->isOn && button == 0 )
	 {
	 userInterface.applyForces->isOn = false;
	 userInterface.placeBodies->isOn = false;
	 userInterface.attractBodies->isOn = false;
	 userInterface.dampingBodies->isOn = false;
	 }
	 
	 
	 
	 if (userInterface.dampingBodies->isOn && button == 0 )
	 {
	 startMouse.set((x - coordinateSystem2D.offset.x) * coordinateSystem2D.inverseZoomScale, (y - coordinateSystem2D.offset.y) * coordinateSystem2D.inverseZoomScale);
	 userDampingVector.set(0, 0);
	 userInterface.placeBodies->isOn = false;
	 userInterface.repelBodies->isOn = false;
	 userInterface.attractBodies->isOn = false;
	 userInterface.applyForces->isOn = false;
	 }
	 
	 
	 
	 
	 //*/
	
	
	
	if (button == 2) // Update offset based on mouse movement
	{
		coordinateSystem2D.isDragging = true;
		coordinateSystem2D.dragStartPos.set(x, y);
	}
}


void SimulationConfig::mouseReleased(int x, int y, int button, Quadtree* &rootQuadtree, std::vector<Body *> &bodies)
{
	//userInterface.mouseReleased(x, y, button);
	
	
	
	
	if (coordinateSystem2D.isDragging && button == 0)
	{
		coordinateSystem2D.isDragging = false;
	}
	
	
	//
	/*
	 if (userInterface.applyForces->isOn && button == 0 )
	 {
	 float magnitude = ofMap(userForceVector.length(), 0, 10000, 0, 100);  // Calculate the magnitude of the force vector
	 for (auto body : bodies)
	 {
	 float distance = body->position.distance(startMouse);
	 if (distance <= rootQuadtree->bounds.width * (0.000375 * coordinateSystem2D.inverseZoomScale))
	 {
	 ofVec2f tempForceVector;
	 tempForceVector = userForceVector.getNormalized() * magnitude;
	 body->applyForce(tempForceVector); // Scale the force vector based on the magnitude and apply it to the body
	 
	 }
	 
	 }
	 }
	 
	 
	 
	 if (userInterface.dampingBodies->isOn && button == 0 )
	 {
	 for (auto body : bodies)
	 {
	 float distance = body->position.distance(startMouse);
	 if (distance <= rootQuadtree->bounds.width * (0.000375 * coordinateSystem2D.inverseZoomScale))
	 {
	 body->dampMotion(0.01); // Scale the force vector based on the magnitude and apply it to the body
	 
	 }
	 
	 }
	 }
	 
	 //*/
}


void SimulationConfig::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	coordinateSystem2D.mouseScrolled(x, y, scrollX, scrollY);
}


//--------------------------------------------------------------
void SimulationConfig::windowResized(int w, int h)
{
	//userInterface.windowResized(w,h);
	coordinateSystem2D.windowResized(w, h);
}






