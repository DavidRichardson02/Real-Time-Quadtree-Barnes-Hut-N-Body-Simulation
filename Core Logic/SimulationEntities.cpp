//  SimulationEntities.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

#include "SimulationEntities.hpp"






Body::Body()
{
	position.set(0, 0);
	velocity.set(0, 0);
	mass = 0;
}

Body::Body(ofVec2f pos, ofVec2f vel, float _mass)
{
	position = pos;
	velocity = vel;
	mass = _mass;
}



// Copy constructor
Body::Body(const Body& other) : position(other.position), velocity(other.velocity), mass(other.mass){}

Body::~Body()
{
	position = {0,0};
	velocity = {0,0};
	mass = 0;
}


// Assignment operator
Body& Body::operator=(const Body& other)
{
	if (this != &other)
	{
		position = other.position;
		velocity = other.velocity;
		mass = other.mass;
	}
	return(*this);
}



bool Body::operator!=(const Body& other)
{
	bool notEqual = false;
	if (this == &other)
	{
		notEqual = true;
	}
	return(notEqual);
}




void Body::applyForce(ofVec2f& force)
{
	ofVec2f acceleration = force / mass;
	velocity = velocity + acceleration;
}

void Body::dampMotion(float dampParameter)
{
	velocity = velocity*dampParameter;
}


void Body::setParameters(ofVec2f pos, ofVec2f vel, float _mass)
{
	position = pos;
	velocity = vel;
	mass = _mass;
}



void Body::reset()
{
	position.set(0, 0);
	velocity.set(0, 0);
	mass = 0;
}





void Body:: draw(bool colorMode)
{
	//
	/*
	 float energyNormalized = kineticEnergy / (kineticEnergy + fabs(potentialEnergy));
	 
	 
	 ofColor energyLevel(0,255,0);
	 
	 if (kineticEnergy <= fabs(potentialEnergy))
	 {
	 if(colorMode)
	 {
	 energyLevel.r = energyNormalized * 2.0 * 255;
	 energyLevel.g = 255;
	 
	 energyLevel.b = 0;
	 }
	 else if(!colorMode)
	 {
	 energyLevel.b = energyNormalized * 2.0 * 255;
	 energyLevel.r = 255;
	 energyLevel.g = 0;
	 }
	 }
	 else
	 {
	 if(colorMode)
	 {
	 energyLevel.r = 255;
	 energyLevel.g = 255 - (energyNormalized - 0.5) * 2.0 * 255;
	 
	 energyLevel.b = 0;
	 }
	 else if(!colorMode)
	 {
	 energyLevel.b = 255;
	 energyLevel.r = 255 - (energyNormalized - 0.5) * 2.0 * 255;
	 energyLevel.g = 0;
	 }
	 }
	 //*/
	
	
	
	ofFill();
	//ofSetColor(energyLevel);
	ofDrawCircle(position.x, position.y, mass);
	
	// Draw orientation line
	//ofSetColor(ofColor::white);
	//float orientationLineLength = mass * 2;  // Length of the line can be proportional to mass or some fixed value
	//ofVec2f orientationVector = ofVec2f(cos(orientation), sin(orientation)) * mass;
	//ofDrawLine(position, position + orientationVector);
}
















BodyData::BodyData(float mass)
{
	kineticEnergy = 0;
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * mass * (mass * mass); // I = 1/4 * mass * radius^2
	orientation = 0;
	angularVelocity = 0;
}


BodyData::BodyData(ofVec2f position, ofVec2f velocity, float mass)
{
	kineticEnergy = 0.5 * mass * velocity.lengthSquared();
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * mass * (mass * mass); // I = 1/4 * mass * radius^2
	angularVelocity = velocity.lengthSquared() / (mass * mass); // mass is analogous to radius for rigid 2D bodies, using squared's for efficiency
	orientation = 0 + angularVelocity;
}

BodyData::BodyData(const Body body)
{
	kineticEnergy = 0.5 * body.mass * body.velocity.lengthSquared();
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * body.mass * (body.mass * body.mass); // I = 1/4 * mass * radius^2
	angularVelocity = body.velocity.lengthSquared() / (body.mass * body.mass);
	orientation = 0 + angularVelocity;
}



// Copy constructor
BodyData::BodyData(const BodyData& other) : kineticEnergy(other.kineticEnergy), potentialEnergy(other.potentialEnergy), momentOfInertia(other.momentOfInertia), orientation(other.orientation), angularVelocity(other.angularVelocity){}


BodyData::~BodyData()
{
	kineticEnergy = 0;
	potentialEnergy = 0;
	momentOfInertia = 0;
	orientation = 0;
	angularVelocity = 0;
}




// Assignment operator
BodyData& BodyData::operator=(const BodyData& other)
{
	if (this != &other)
	{
		kineticEnergy = other.kineticEnergy;
		potentialEnergy = other.potentialEnergy;
		
		momentOfInertia = other.momentOfInertia;
		orientation = other.orientation;
		angularVelocity = other.angularVelocity;
	}
	return(*this);
}



bool BodyData::operator!=(const BodyData& other)
{
	bool notEqual = false;
	if (this == &other)
	{
		notEqual = true;
	}
	return(notEqual);
}









void BodyData:: draw(bool colorMode, const Body body)
{
	float energyNormalized = kineticEnergy / (kineticEnergy + fabs(potentialEnergy));
	
	
	ofColor energyLevel(0,255,0);
	
	if (kineticEnergy <= fabs(potentialEnergy))
	{
		if(colorMode)
		{
			energyLevel.r = energyNormalized * 2.0 * 255;
			energyLevel.g = 255;
			
			energyLevel.b = 0;
		}
		else if(!colorMode)
		{
			energyLevel.b = energyNormalized * 2.0 * 255;
			energyLevel.r = 255;
			energyLevel.g = 0;
		}
	}
	else
	{
		if(colorMode)
		{
			energyLevel.r = 255;
			energyLevel.g = 255 - (energyNormalized - 0.5) * 2.0 * 255;
			
			energyLevel.b = 0;
		}
		else if(!colorMode)
		{
			energyLevel.b = 255;
			energyLevel.r = 255 - (energyNormalized - 0.5) * 2.0 * 255;
			energyLevel.g = 0;
		}
	}
	
	
	
	
	ofFill();
	ofSetColor(energyLevel);
	ofDrawCircle(body.position.x, body.position.y, body.mass);
	
	// Draw orientation line
	ofSetColor(ofColor::white);
	float orientationLineLength = body.mass * 1;  // Length of the line can be proportional to mass or some fixed value
	ofVec2f orientationVector = ofVec2f(cos(orientation), sin(orientation)) * orientationLineLength;
	ofDrawLine(body.position, body.position + orientationVector);
}

