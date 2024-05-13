//  DrawingUtilities.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "ofMain.h"






///
static inline ofRectangle GetNestedRectangles(ofRectangle mainRectangle, int numNestedRectangles);










// ------------- Visualize Relative Potential Energy Field ------------------
/// \{

/**
 * MapPotentialToUnitRange: Normalize the potential energy to [0,1] range.
 *
 * * This function scales the potential energy into a unit range, facilitating visualization and analysis.
 *
 * @param minPotential The minimum potential energy in the system.
 * @param maxPotential The maximum potential energy in the system.
 * @param potential The specific potential energy value to be mapped.
 *
 * @return The normalized potential energy.
 */
static inline float MapPotentialToUnitRange(float minPotential, float maxPotential, float potential); // Function to map the potential to the [0,1] range








/**
 * GetColorFromPotential: Generate a color based on the potential energy value.
 *
 * This function uses the Viridis color map to convert the computed gravitational potential energy value at a grid point to a corresponding color
 * that signifies the magnitude of the potential.This provides a perceptually uniform visualization of energy states.
 * The color map is particularly useful for indicating regions of different potential energy with background color fields.
 *
 * @param minPotential The minimum potential energy in the system.
 * @param maxPotential The maximum potential energy in the system.
 * @param potential The specific potential energy value.
 *
 * ISSUES:
 * 		- how are minPotential and maxPotential parsed from live and dynamic simulation paramerers to develop a reasonable range to define them
 *
 * @return ofColor object representing the mapped color.
 */
static inline ofColor GetColorFromPotential(float minPotential, float maxPotential, float potential);












// Function to map the potential to the [0,1] range
static inline float MapPotentialToUnitRange(float minPotential, float maxPotential, float potential)
{
	return (potential - minPotential) / (maxPotential - minPotential);
}




// Implementation of GetColorFromPotential function
static inline ofColor GetColorFromPotential(float minPotential, float maxPotential, float potential)
{
	// Normalize the potential to [0, 1]
	float normalizedPotential = MapPotentialToUnitRange(minPotential, maxPotential, potential);
	
	// Viridis color map coefficients for R, G, and B
	float viridis[3][4] =
	{
		{ 0.267004, 1.269930,  0.319920,  1.611848 },
		{ 0.003745, 0.038922, -0.072153,  1.992608 },
		{ 1.101980, 0.055709,  1.118520, -0.313205 }
	};
	
	// Compute the R,G,B values using the viridis color map
	float R = viridis[0][0] + viridis[0][1] * std::exp(-normalizedPotential / viridis[0][2]) + viridis[0][3] * std::exp(-normalizedPotential / viridis[0][4]);
	float G = viridis[1][0] + viridis[1][1] * std::exp(-normalizedPotential / viridis[1][2]) + viridis[1][3] * std::exp(-normalizedPotential / viridis[1][4]);
	float B = viridis[2][0] + viridis[2][1] * std::exp(-normalizedPotential / viridis[2][2]) + viridis[2][3] * std::exp(-normalizedPotential / viridis[2][4]);
	
	return ofColor(R * 255, G * 255, B * 255);
}




























// ------------- Inline Function to Return the Bounding Box of Text ------------------
/// \{



// Width of a character in the bitmap font
const float CHAR_WIDTH = 8;
// Height of a character in the bitmap font
const float CHAR_HEIGHT = 11;


/**
 * This function calculates and returns the bounding box of a given string.
 * The bounding box is calculated based on the position of the string (_x, _y),
 * the scale factors (scaleX, scaleY), and the dimensions of a character (CHAR_WIDTH, CHAR_HEIGHT).
 * The function has two implementations, one that assumes all lines in the string have the same width,
 * and another that calculates the width of each line separately.
 * The second implementation is currently in use.
 */
static inline ofRectangle GetBoundingBox(std::string& str, float _x, float _y, float scaleX, float scaleY)
{
	
	
	//  Reviews the width of each new line(from '\n') and takes the largest of the widths as the bounding box of the string
	
	
	// Initialize maximum width and number of lines
	float maxWidth = 0;
	int lines = 1 * scaleY;
	float currentWidth = 0;
	
	// Iterate over each character in the string
	for(char c : str)
	{
		// If the character is a newline, increment the number of lines and update the maximum width
		if(c == '\n')
		{
			lines++;
			
			// Update maximum width if the current width is larger
			if(currentWidth > maxWidth)
			{
				maxWidth = currentWidth;
			}
			// Reset current width for the new line
			currentWidth = 0;
		}
		else
		{
			// If the character is not a newline, increment the current width
			currentWidth += CHAR_WIDTH * scaleX;
		}
	}
	
	// In case the string doesn't end with a newline, update the maximum width if necessary
	if(currentWidth > maxWidth)
	{
		maxWidth = currentWidth;
	}
	
	// Return the bounding box of the string
	return{_x, _y, maxWidth, lines * CHAR_HEIGHT};
	//*/
}



/// \}












/**
 *  NOTE: this function exists only to streamline the drawing of interface elements
 *
 */
static inline ofRectangle GetNestedRectangles(ofRectangle mainRect, int numNestedRectangles)
{
	ofRectangle nestedRect;
	nestedRect.x = mainRect.x;
	nestedRect.y = mainRect.y;
	
	if(numNestedRectangles <= 2) //intialize the rect so that they can fit side by side
	{
		nestedRect.height = mainRect.height;
		nestedRect.width = (mainRect.width * 0.5) - (mainRect.width * 0.1);
	}
	else //intialize the rect so that they will fit in a list
	{
		nestedRect.height = mainRect.height * 0.5;
		nestedRect.width = mainRect.width;
	}
	
	
	
	
	//each nested rectangle will be the same size but their positions within the main rect will depend on the number of nested
	//rectangles within the main rectangle and the width/height of the main rectangle.
	//But the idea is to return a single rectangle positioned in the top left of main rect that can be easily reused by the
	//function caller to populate the main rectangle with the nested ones by simply multiplying the starting x,y position of
	//the nestedRect and drawing it accordingly.
	
	
	return nestedRect;
}
