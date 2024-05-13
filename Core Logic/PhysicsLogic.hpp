//  PhysicsLogic.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/*
 * PhysicsLogic Module: Utility functions for Physics Computations
 *
 * Description:
 * This file defines a collection of utility functions designed to assist with
 * the physical calculations required in an N-Body simulation, specifically
 * those related to the Barnes-Hut approximation algorithm. These include functions
 * to compute gravitational forces, accelerations, and integrate them over time.
 * It aims to achieve a balance between computational efficiency and accuracy.
 *
 */
#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "DrawingUtilities.hpp"
#include "SequenceContainers.hpp"
#include "SimulationEntities.hpp"
#include "ObjectPool.hpp"
#include "Quadtree.hpp"
#include "ofMain.h"




// ------------- Gravitational Computations -------------
/**
 * ComputeAllForces: Calculate the net gravitational forces on all bodies.
 *
 * Utilizes the quadtree to calculate the net gravitational forces acting on each body in the simulation.
 * Accelerations are stored in the passed `bodiesAccelerations` array for later integration.
 * This is a high-level function that orchestrates the traversal of the quadtree to compute the forces.
 *
 * Parameters:
 * @param rootNode            Root of the quadtree data structure
 * @param bodies              Vector containing pointers to all Body objects
 * @param bodiesAccelerations Pre-allocated array to store calculated accelerations
 * @param G                   Universal gravitational constant
 * @param theta               Barnes-Hut theta parameter for MAC
 */
static inline void ComputeAllForces(Quadtree* &rootNode,  std::vector<Body*> &bodies, ofVec2f* &bodiesAccelerations, float G, float theta);



/**
 * ComputeTreeForce: Compute the net gravitational force acting on a single body.
 *
 * This function computes the net gravitational force acting on a single body
 * by traversing the quadtree from the root node.
 *
 * @param rootNode The root node of the quadtree.
 * @param body Pointer to the body object for which the force is being calculated.
 * @param bodiesAccelerations The computed acceleration for this body.
 * @param G The gravitational constant.
 * @param theta The Barnes-Hut opening angle.
 */
static inline void ComputeTreeForce(Quadtree* &rootNode,  Body* &body, ofVec2f &bodiesAccelerations, float G, float theta);
static inline void ComputeAccelerationDueTo(Body* &body, ofVec2f &otherBodyPosition, float &otherBodyMass, ofVec2f &bodiesAccelerations, float G, float distance);








// ------------- Time Integration Schemes -------------
/**
 * IntegrationScheme: Orchestrates the integration of forces to update positions and velocities.
 *
 * Selects and executes the appropriate integration scheme based on user selection.
 * Handles different time dilation modes (slowMotionMode, fastMotionMode).
 *
 *
 * Offers two methods for updating the positions of the bodies from their force.
 * In essence, the availability of these methods in the user interface allows for adaptability
 * in approximating complex systems, enabling users to balance computational efficiency against
 * simulation accuracy.
 *
 * Although Runge Kutta is more accurate, the LeapFrog KDK will be preferable in most instances,
 * this is due to the higher computational cost of the Runge Kutta method,
 * it's unbounded energy error, and it's lack of time-symmetry.
 *
 * Parameters:
 * @param dt                  Time step
 * @param bodies              Vector containing pointers to all Body objects
 * @param bodiesAccelerations Array containing calculated accelerations
 * @param integrationScheme   Flag to select integration scheme (true for LeapFrog KDK, false for RK4)
 * @param slowMotionMode      Flag to indicate slow motion
 * @param fastMotionMode      Flag to indicate fast motion
 *
 */
static inline void IntegrationScheme(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations, bool integrationScheme, bool &slowMotionMode, bool &fastMotionMode);



/**
 * fourth-order runge-kutta, a fourth order method, generally offers greater accuracy
 * per time step at the cost of increased computational complexity. It approximates
 * the solution by taking a weighted average of four different approximations at each
 * time step, however this method does not preserve time symmetry, so errors in the
 * total energy of the system will increase without bound over time.
 */
static inline void IntegrateRK4Force(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations);



/**
 * LeapFrog KDK, a second order method that handles position ('Drift') and velocity ('Kick')
 * updates in a staggered manner, making it time-reversible which prevents systematic
 * build-up in error in the total energy of the system over time. This is crucial for
 * long-term simulations where errors might accumulate. slightly less accurate and
 * significantly cheaper than RK4
 */
//Helper functions to integrate forces into bodies
static inline void ResetAccelerations(std::vector<Body*> &bodies);
static inline void ComputePositionAtHalfTimeStep(float dt,std::vector<Body*> &bodies);  // Drift every body once before resetting acceleration
static inline void ComputeVelocityAndPosition(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations);   //Kick-Drift-Kick Leap-Frog integration scheme








// ------------- Energy Computations -------------
/**
 * ComputeSystemEnergy: Calculate the total energy of the system.
 *
 * Computes the total energy of the system by summing the kinetic and potential
 * energy for all bodies. Useful for system diagnostics and ensuring energy conservation.
 *
 * Parameters:
 * @param bodies                Vector containing pointers to all Body objects
 * @param systemEnergy          Variable to store total system energy
 * @param systemKineticEnergy   Variable to store total kinetic energy
 * @param systemPotentialEnergy Variable to store total potential energy
 */
static inline void ComputeSystemEnergy(std::vector<Body*> &bodies, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy);




/**
 * ComputeBodyKineticEnergies: Calculate the kinetic energy of all bodies
 *
 *
 * Parameters:
 * @param bodies                Vector containing pointers to all Body objects
 */
static inline void ComputeBodyKineticEnergies(std::vector<Body*> &bodies);



/**
 * ComputeBodyPotentialEnergies: Calculate the potential energy of all bodies
 *
 * very expensive, more than doubles workload of entire force calculation while running, avoid at all costs if possible
 * Need to find a way to pass in distances, other bodies, and bodiesAccelerations
 *
 *
 * Parameters:
 * @param bodies                Vector containing pointers to all Body objects
 */
static inline void ComputeBodyPotentialEnergies(std::vector<Body*> &bodies, double G, ofVec2f*& bodiesAccelerations);












static inline void ComputeAllForces(Quadtree* &rootNode,  std::vector<Body*> &bodies, ofVec2f* &bodiesAccelerations, float G, float theta) //use the quadtree to calculate and store the accelerations of bodies due to gravitational interactions to fill in the empty bodiesAccelerations(done this way so that the same bodiesAccelerations can be used to integrate and update bodies positions/velocities by accelerations)
{
	for(int i=0;i<bodies.size();i++)
	{
		ComputeTreeForce(rootNode, bodies[i], bodiesAccelerations[i], G, theta);
	}
}


static inline void ComputeTreeForce(Quadtree* &rootNode,  Body* &body, ofVec2f &bodiesAccelerations, float G, float theta)
{
	if(body == nullptr || rootNode == nullptr)
	{
		return;
	}
	
	
	if (rootNode->hasChildren)
	{
		float distance = rootNode->centerOfMass.distance(body->position); //distance between the center of mass and the body, add a small constant to prevent division by zero
		float size = rootNode->bounds.width;      //size of the quadrant of bodies
		
		if (size / distance < theta)  //check if the MAC is acceptable and then if it is use group force approximation
		{
			//if (rootNode->totalMass != 0)
			//{
			
			ComputeAccelerationDueTo(body, rootNode->centerOfMass, rootNode->totalMass, bodiesAccelerations, G, distance);
			
			
			//float potentialEnergy = -G * body->mass * rootNode->totalMass / distance;
			//body->potentialEnergy += potentialEnergy;// Note: using += here since potential energy is a sum over all bodies
			return;
			//}
		}
		else //MAC not satisfied, for the highest level quadrant
		{
			if (rootNode->children[0] != nullptr)
			{
				ComputeTreeForce(rootNode->children[0], body, bodiesAccelerations, G, theta);
			}
			if (rootNode->children[1] != nullptr)
			{
				ComputeTreeForce(rootNode->children[1], body, bodiesAccelerations, G, theta);
			}
			if (rootNode->children[2] != nullptr)
			{
				ComputeTreeForce(rootNode->children[2], body, bodiesAccelerations, G, theta);
			}
			if (rootNode->children[3] != nullptr)
			{
				ComputeTreeForce(rootNode->children[3], body, bodiesAccelerations, G, theta);
			}
		}
	}
	else // no hasChildren and one body
	{
		if (rootNode->nodeBody != body) //  if (rootNode->bodyCount > 0) //because this node has no children nodes, it will only have one body in it
		{
			//if (rootNode->nodeBody != body)
			//{
			float dist = rootNode->nodeBody->position.distance(body->position);
			ComputeAccelerationDueTo(body, rootNode->nodeBody->position, rootNode->nodeBody->mass, bodiesAccelerations, G, dist);
			
			
			//float potentialEnergy = -G * body->mass * rootNode->nodeBody->mass / dist;
			//body->potentialEnergy += potentialEnergy; //velocity doesn't get updated here, don't compute kinetic energy here.  // Note: using += here since potential energy is a sum over all bodies
			return;
			//}
		}
	}
}

static inline void ComputeAccelerationDueTo(Body* &body, ofVec2f &otherBodyPosition, float &otherBodyMass, ofVec2f &bodiesAccelerations, float G, float distance)
{
	ofVec2f gForce;
	if (distance < epsilon)
	{
		gForce = (otherBodyPosition - body->position) * (G * otherBodyMass / ((distance + epsilon) * (distance + epsilon) * (distance + epsilon)));
	}
	else
	{
		gForce = (otherBodyPosition - body->position) * (G * otherBodyMass / (distance * distance * distance));
	}
	bodiesAccelerations += gForce;
}








inline void IntegrationScheme(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations, bool integrationScheme, bool &slowMotionMode, bool &fastMotionMode)
{
	
	if(slowMotionMode)
	{
		fastMotionMode = false;
		dt = 0.001;
	}
	else if(fastMotionMode)
	{
		slowMotionMode = false;
		dt = 0.1;
	}
	else //if(!fastMotionMode && !slowMotionMode)
	{
		dt = 0.01;
	}
	
	
	
	
	if(integrationScheme) //do LeapFrog KDK
	{
		ComputeVelocityAndPosition(dt, bodies, bodiesAccelerations);
	}
	else //do fourth-order runge-kutta
	{
		IntegrateRK4Force(dt, bodies, bodiesAccelerations);
	}
	
}




inline void IntegrateRK4Force(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		ofVec2f k1v = dt * bodiesAccelerations[i];
		
		ofVec2f k1x = dt * bodies[i]->velocity;
		
		ofVec2f k2v = dt * (bodiesAccelerations[i] + 0.5 * k1v);
		ofVec2f k2x = dt * (bodies[i]->velocity + 0.5 * k1x);
		
		ofVec2f k3v = dt * (bodiesAccelerations[i] + 0.5 * k2v);
		ofVec2f k3x = dt * (bodies[i]->velocity + 0.5 * k2x);
		
		ofVec2f k4v = dt * (bodiesAccelerations[i] + k3v);
		ofVec2f k4x = dt * (bodies[i]->velocity + k3x);
		
		
		bodies[i]->velocity = bodies[i]->velocity + (k1v + 2 * k2v + 2 * k3v + k4v) / 6;
		bodies[i]->position = bodies[i]->position + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
		
		
		//bodies[i]->kineticEnergy = 0.5 * bodies[i]->mass * bodies[i]->velocity.lengthSquared();
		
		//
		/*
		 float d = 0.5 * bodies[i]->mass;  // off-center distance
		 
		 // Assume a radius vector from center to the point where the force is applied.
		 // This is a simplification; in a real scenario, you'll need to determine this based on the physical situation.
		 ofVec2f radialVector(d, 0);  // Example: assuming d(force applied) is along x-axis, you can rotate this based on body orientation
		 
		 // Calculate torque due to gravitational forces (using 2D cross product, which yields a scalar)
		 float torque = radialVector.x * bodiesAccelerations[i].y * bodies[i]->mass - radialVector.y * bodiesAccelerations[i].x * bodies[i]->mass;
		 
		 
		 // Calculate angular acceleration
		 float angularAcceleration = torque / bodies[i]->momentOfInertia;
		 
		 // Update angular velocity (using Euler integration)
		 bodies[i]->angularVelocity += angularAcceleration * dt;
		 
		 
		 // Update orientation (angle), assuming it starts from an initial angle of 0
		 // (assuming no external torques for simplicity)
		 bodies[i]->orientation += bodies[i]->angularVelocity * dt;
		 
		 
		 // Update kinetic energy to include rotational component (1/2 * I * w^2)
		 bodies[i]->kineticEnergy += 0.5 * bodies[i]->momentOfInertia * bodies[i]->angularVelocity * bodies[i]->angularVelocity;
		 //*/
	}
}


//
/*
 static inline void IntegrateRK4Angular(float dt, std::vector<Body*> &bodies, float*& bodiesAngularAccelerations)
 {
 for (size_t i = 0; i < bodies.size(); i++)
 {
 // We assume that angularMomentum is in the form ofVec2f(omega, omega) for simplicity
 float old_omega = bodies[i]->angularMomentum.x;
 
 float k1_alpha = dt * bodiesAngularAccelerations[i];
 float k1_omega = dt * old_omega;
 
 float k2_alpha = dt * (bodiesAngularAccelerations[i] + 0.5 * k1_alpha);
 float k2_omega = dt * (old_omega + 0.5 * k1_omega);
 
 float k3_alpha = dt * (bodiesAngularAccelerations[i] + 0.5 * k2_alpha);
 float k3_omega = dt * (old_omega + 0.5 * k2_omega);
 
 float k4_alpha = dt * (bodiesAngularAccelerations[i] + k3_alpha);
 float k4_omega = dt * (old_omega + k3_omega);
 
 float new_omega = old_omega + (k1_alpha + 2 * k2_alpha + 2 * k3_alpha + k4_alpha) / 6;
 
 // Update the angular momentum and orientation
 bodies[i]->angularMomentum = bodies[i]->I_body * ofVec2f(new_omega, new_omega);
 bodies[i]->orientation += new_omega * dt;  // Assuming small time steps
 }
 }
 //*/



inline void ResetAccelerations(std::vector<Body*> &bodies)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		//bodies[i]->kineticEnergy = 0;
		//bodies[i]->potentialEnergy = 0;
	}
}

inline void ComputePositionAtHalfTimeStep(float dt, std::vector<Body*> &bodies)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		bodies[i]->position = bodies[i]->position + bodies[i]->velocity * (dt * 0.5);
	}
}

inline void ComputeVelocityAndPosition(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		//KDK Leap Frog
		bodies[i]->velocity = bodies[i]->velocity + bodiesAccelerations[i] * (dt); // Kick
		
		bodies[i]->position = bodies[i]->position + bodies[i]->velocity * (dt * 0.5); // Drift
																					  //bodies[i]->kineticEnergy = 0.5 * bodies[i]->mass * bodies[i]->velocity.lengthSquared();
	}
}








static inline void ComputeSystemEnergy(std::vector<Body*> &bodies, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy)
{
	systemKineticEnergy = 0;
	systemPotentialEnergy = 0;
	systemEnergy = 0;
	for (size_t i = 0; i < bodies.size(); i++)
	{
		//systemKineticEnergy += bodies[i]->kineticEnergy;//(0.5 * bodies[i]->mass * bodies[i]->velocity.lengthSquared());
		//systemPotentialEnergy += bodies[i]->potentialEnergy;
		systemEnergy = systemKineticEnergy + fabs(systemPotentialEnergy);
	}
	systemEnergy = systemKineticEnergy + fabs(systemPotentialEnergy);
}







