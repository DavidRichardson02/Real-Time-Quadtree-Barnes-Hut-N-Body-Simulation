//  CoordinateSystem.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include <math.h>
#include <vector>
#include "Vects.hpp"
#include "Geometry.hpp"
#include "ofMain.h"




/**
 * 2D plane coordinate system navigation
 *
 * The user is able to navigate the canvas by dragging the screen and by zooming
 * in and out. The user’s navigation of the screen is accomplished by using ofPushMatrix and
 * ofPopMatrix to isolate the coordinate system transform to whatever I want to be affected
 * by it. Once the current coordinate system has been saved using ofPushMatrix, the viewport
 * of the screen is translated by the amount it was offset when the user dragged it, and then
 * the zooming in and out is accomplished by using ofScale to scale everything within the the
 * coordinate system transform to the amount zoomed. Then, after drawing the transformed
 * coordinate system, the previous coordinate system is recalled using ofPopMatrix after which
 * things can be drawn as normal.
 */
class CoordinateSystem2D
{
public:
	/// @section Constructors
	CoordinateSystem2D(); // Default constructor
	CoordinateSystem2D(Square coordinateSystemBounds); // Construct with Square bounds
	CoordinateSystem2D(ofRectangle coordinateSystemBounds); // Construct with ofRectangle bounds
	
	
	
	
	/// @section Accessor operators
	CoordinateSystem2D operator+(const CoordinateSystem2D& other) const; // Add properties of another object
	CoordinateSystem2D operator-(const CoordinateSystem2D& other) const; // Subtract properties of another object
	CoordinateSystem2D operator*(const CoordinateSystem2D& other) const; // Multiply properties by another object's
	CoordinateSystem2D operator/(const CoordinateSystem2D& other) const; // Divide properties by another object's
	
	
	
	
	/// @section Modifier operators
	CoordinateSystem2D &operator=(const CoordinateSystem2D &other); // Assign from another object
	void operator+=(const CoordinateSystem2D& other); // Add and assign properties of another object
	void operator-=(const CoordinateSystem2D& other); // Subtract and assign properties of another object
	void operator*=(const CoordinateSystem2D& other); // Multiply and assign properties by another object's
	void operator/=(const CoordinateSystem2D& other); // Divide and assign properties by another object's
	bool operator!=(const CoordinateSystem2D &other); // Check inequality with another object
	
	
	
	
	/// @section Settings and configuration
	void set(Square coordinateSystemBounds); // Set the bounds of the coordinate system
	void resetCoordinateSystem(); // Reset the coordinate system to its default state
	
	
	
	
	/// @section Event handlers
	void mouseDragged(int x, int y, int button); // Handle mouse drag event
	void mousePressed(int x, int y, int button); // Handle mouse press event
	void mouseReleased(int x, int y, int button); // Handle mouse release event
	void mouseScrolled(int x, int y, float scrollX, float scrollY); // Handle mouse scroll event (zoom in/out)
	void windowResized(int w, int h); // Handle window resize event
	
	
	
	
	/// @section Member variables
	Square canvas; // The 2D plane of the coordinate system, i.e., what is being navigated
	float maxZoomScale;  // Maximum viewable plane size
	float minZoomScale;  // Minimum viewable plane size
	float zoomScale = 1.0f;  // The current zoom scale of the coordinate system, default is 1.0, for no zoom
	float inverseZoomScale; // Used to reduce divisions throughout program
	float zoomIncrement = 0.025f;  //  Control value of each scroll wheel input, i.e, how much each scroll changes the view
	bool isDragging = false;  // Flag variable to start and stop dragging
	Vec2D dragStartPos; // Starting position of the cursor for the current mouse dragging event(if applicable)
	Vec2D offset; // The two-dimensional offset of the coordinate system's current frame of reference from the origin
};
