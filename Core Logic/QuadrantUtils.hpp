//  QuadrantUtils.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 * dev NOTE: 
 * check out the 'Quadtree.hpp' file for more info for now, the documentation for this file, and it's specific purpose(s) will have to wait for now.
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
#include "ofMain.h"




enum QuadrantEnum
{
	NW = 0, // North-West
	NE = 1, // North-East
	SW = 2, // South-West
	SE = 3, // South-East
};


// Lookup table for quadrant directions
///   00----10
///   |     |
///   |     |
///   01----11
static const float QuadrantDir[] =
{
	0.0, 0.0, //NW quadrant,
	1.0, 0.0, //NEquadrant
	0.0, 1.0, //SE quadrant
	1.0, 1.0, //SW quadrant
};








static inline QuadrantEnum DetermineQuadrant(ofRectangle &nodeBounds, ofVec2f& bodyPosition); //returns the quadrant in which a body lies
static inline ofVec2f DetermineQuadrantDirection(QuadrantEnum quadrant); // Retrieves the direction for a given octant based on the lookup table.








static inline QuadrantEnum DetermineQuadrant(ofRectangle &nodeBounds, ofVec2f& bodyPosition) //returns the quadrant in which a body lies
{
	float halfWidth = nodeBounds.width * 0.5;
	float midX = nodeBounds.x + halfWidth;
	float midY = nodeBounds.y + halfWidth;
	
	
	if (bodyPosition.y <= midY) //either in NE or NW quad
	{
		return (bodyPosition.x <= midX) ? QuadrantEnum::NW : QuadrantEnum::NE;
	}
	else  //either in SE or SW quad
	{
		return (bodyPosition.x <= midX) ? QuadrantEnum::SW : QuadrantEnum::SE;
	}
}



/**
 * DetermineQuadrantDirection
 *
 * This function retrieves the direction for a given quadrant based on the lookup table(QuadrantDir).
 * The lookup table is a static constant array that contains the direction values for each quadrant.
 * The function uses the quadrant value as an index to access the corresponding direction values in the lookup table.
 * The direction values are then used to set the x and y coordinates of a 2D vector, which is returned by the function.
 *
 * @param quadrant The quadrant for which to determine the direction.
 */
static inline ofVec2f DetermineQuadrantDirection(QuadrantEnum quadrant)
{
	// Create a 2D vector to store the direction
	ofVec2f quadrantDir;
	
	// Use the quadrant value to index into the lookup table and retrieve the x coordinate
	quadrantDir.x = QuadrantDir[2 * quadrant];
	
	// Use the quadrant value to index into the lookup table and retrieve the y coordinate
	quadrantDir.y = QuadrantDir[2 * quadrant + 1];
	
	// Return the 2D vector containing the direction
	return(quadrantDir);
}
