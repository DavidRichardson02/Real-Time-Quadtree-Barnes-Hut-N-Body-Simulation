//  SimulationEnviroment.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The 'SimulationEnviroment' header and source files contain code that is not yet incorporated into the larger project and is still in experimental stages of development
 in any meaningful capacity... pretty much work in progress, emphasis on the 'in progress' part
 */


/**
 * SimulationEnviroment Class: Defines, dictates, and maintains the simulation enviroment, i.e., 
 * the world the N-Body simulation is occuring in.
 *
 * The SimulationEnviroment class is responsible for instantiating and maintaining:
 * 			- The 2D-plane the simulation is occuring in
 * 			- The object pool of bodies
 * Instantiates the 2D-plane the simulation is occuring in, and populates the enviroment
 * Provides the object pool of bodies
 *
 *
 * The SimulationConfig class serves as the main hub for configuring and operating
 * the simulation. It holds an object pool for Body objects and initializes the
 * quadtree. It encapsulates all the core functionalities of the simulation and acts
 * as the interface for starting, updating, and rendering the simulation. It also
 * contains utility functions to generate initial conditions based on various
 * astrophysical models. These models range from cold starts with random positions to
 * more complex arrangements like the Plummer model.
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
#include "PhysicsLogic.hpp"
#include "VisualizationUtils.hpp"
#include "ofMain.h"


class SimulationEnviroment
{
	// ------------- Utility and Management -------------
	ObjectPool<Body> bodyPool; // Object pool for Body objects
	
	
	// ------------- Coordinate Systems and User Interaction -------------
	CoordinateSystem2D coordinateSystem2D; // 2D coordinate system for the simulation
};

