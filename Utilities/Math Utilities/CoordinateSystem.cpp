//  CoordinateSystem.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "CoordinateSystem.hpp"






/**
 * CoordinateSystem2D()
 *
 * Default constructor for the CoordinateSystem2D class.
 * This constructor initializes the canvas to a square of size 2000 centered at the origin.
 * It also sets the maximum and minimum zoom scales based on the size of the canvas and the width of the window,
 * to achieve reasonable scaling. The offset and drag start position are both initialized to the origin.
 */
CoordinateSystem2D :: CoordinateSystem2D()
{
	// Set the canvas to a square of size 2000 centered at the origin
	canvas.set(-1000, -1000, 2000);
	
	/// Calculate the maximum and minimum zoom scales using the ratio of the canvas size to the window width and the ratio of the window width to the canvas size, respectively.
	maxZoomScale = canvas.size / ofGetWidth();
	minZoomScale = ofGetWidth() / canvas.size;
	
	/// Initialize the offset and drag start position to the origin
	offset = {0,0};
	dragStartPos = {0,0};
}




/**
 * CoordinateSystem2D(Square coordinateSystemBounds)
 *
 * Constructor for the CoordinateSystem2D class that takes a Square object as parameter.
 * This constructor initializes the canvas according to the provided square.
 * It also sets the maximum and minimum zoom scales based on the size of the canvas and the width of the window.
 * The offset and drag start position are both initialized to the origin.
 *
 * @param coordinateSystemBounds: The square that defines the bounds of the coordinate system.
 */
CoordinateSystem2D :: CoordinateSystem2D(Square coordinateSystemBounds)
{
	/// Set the canvas to the provided square
	canvas = coordinateSystemBounds;
	
	/// Calculate the maximum and minimum zoom scales using the ratio of the canvas size to the window width and the ratio of the window width to the canvas size, respectively.
	maxZoomScale = canvas.size / ofGetWidth();
	minZoomScale = ofGetWidth() / canvas.size;
	
	/// Initialize the offset and drag start position to the origin
	offset = {0,0};
	dragStartPos = {0,0};
}

/**
 * CoordinateSystem2D(ofRectangle coordinateSystemBounds)
 *
 * Constructor for the CoordinateSystem2D class that takes an ofRectangle object as parameter.
 * This constructor initializes the canvas according to the provided rectangle.
 * It also sets the maximum and minimum zoom scales based on the size of the canvas and the width of the window.
 * The offset and drag start position are both initialized to the origin.
 *
 * @param coordinateSystemBounds: The rectangle that defines the bounds of the coordinate system.
 */
CoordinateSystem2D :: CoordinateSystem2D(ofRectangle coordinateSystemBounds)
{
	/// Set the canvas to the provided rectangle
	canvas.set(coordinateSystemBounds.x, coordinateSystemBounds.y, coordinateSystemBounds.width);
	
	/// Calculate the maximum and minimum zoom scales using the ratio of the canvas size to the window width and the ratio of the window width to the canvas size, respectively.
	maxZoomScale = canvas.size / ofGetWidth();
	minZoomScale = ofGetWidth() / canvas.size;
	
	/// Initialize the offset and drag start position to the origin
	offset = {0,0};
	dragStartPos = {0,0};
}




/**
 * operator+(const CoordinateSystem2D& other) const
 *
 * Overloads the '+' operator to add two CoordinateSystem2D objects together.
 * This function creates a new CoordinateSystem2D object that has the sum of the zoom scales and offsets of the two CoordinateSystem2D objects being added.
 *
 * @param other: The other CoordinateSystem2D object to add.
 * @return: A new CoordinateSystem2D object that is the result of adding the two CoordinateSystem2D objects.
 */
CoordinateSystem2D CoordinateSystem2D::operator+(const CoordinateSystem2D& other) const
{
	/// Create a copy of the current object
	CoordinateSystem2D result(*this);
	
	/// Add the zoom scale and offset of the other CoordinateSystem2D object to the new object
	result.zoomScale += other.zoomScale;
	result.offset += other.offset;
	
	return result;
}




/**
 * operator-(const CoordinateSystem2D& other) const
 *
 * Overloads the '-' operator to subtract a CoordinateSystem2D object from another.
 * This function creates a new CoordinateSystem2D object that has the difference of the zoom scales and offsets of the two CoordinateSystem2D objects.
 *
 * @param other: The CoordinateSystem2D object to subtract.
 * @return: A new CoordinateSystem2D object that is the result of the subtraction.
 */
CoordinateSystem2D CoordinateSystem2D::operator-(const CoordinateSystem2D& other) const
{
	// Create a copy of the current object
	CoordinateSystem2D result(*this);
	
	// Subtract the zoom scale and offset of the other CoordinateSystem2D object from the new object
	result.zoomScale -= other.zoomScale;
	result.offset -= other.offset;
	
	return result;
}




/**
 * operator*(const CoordinateSystem2D& other) const
 *
 * Overloads the '*' operator to multiply a CoordinateSystem2D object with another.
 * This function creates a new CoordinateSystem2D object that has the product of the zoom scales of the two CoordinateSystem2D objects
 * and the sum of their offsets.
 *
 * @param other: The CoordinateSystem2D object to multiply with.
 * @return: A new CoordinateSystem2D object that is the result of the multiplication.
 */
CoordinateSystem2D CoordinateSystem2D::operator*(const CoordinateSystem2D& other) const
{
	// Create a copy of the current object
	CoordinateSystem2D result(*this);
	
	// Multiply the zoom scale of the new object with the zoom scale of the other object
	result.zoomScale *= other.zoomScale;
	
	// Add the offset of the other object to the offset of the new object
	result.offset += other.offset;
	
	return result;
}

/**
 * operator/(const CoordinateSystem2D& other) const
 *
 * Overloads the '/' operator to divide a CoordinateSystem2D object by another.
 * This function creates a new CoordinateSystem2D object that has the ratio of the zoom scales of the two CoordinateSystem2D objects
 * and the difference of their offsets.
 * The function asserts that the zoom scale of the other object is not zero to avoid division by zero.
 *
 * @param other: The CoordinateSystem2D object to divide by.
 * @return: A new CoordinateSystem2D object that is the result of the division.
 */
CoordinateSystem2D CoordinateSystem2D::operator/(const CoordinateSystem2D& other) const
{
	// Avoid division by zero
	assert(other.zoomScale != 0);
	
	// Create a copy of the current object
	CoordinateSystem2D result(*this);
	
	// Divide the zoom scale of the new object by the zoom scale of the other object
	result.zoomScale /= other.zoomScale;
	
	// Subtract the offset of the other object from the offset of the new object
	result.offset -= other.offset;
	
	return result;
}


/**
 * operator=
 *
 * Assignment operator for the CoordinateSystem2D class.
 * It allows for the assignment of the values of one object to another.
 *
 * @param other: The object to assign values from.
 * @return: Reference to the object with updated values.
 */
CoordinateSystem2D &CoordinateSystem2D :: operator=(const CoordinateSystem2D &other)
{
	// Check if the other object is the same as the current object
	if (this != &other)
	{
		/// Assigning all the attributes of 'other' to the current object
		canvas = other.canvas;
		zoomScale = other.zoomScale;
		inverseZoomScale = other.inverseZoomScale;
		offset = other.offset;
		dragStartPos = other.dragStartPos;
		isDragging = other.isDragging;
		zoomIncrement = other.zoomIncrement;
		maxZoomScale = other.maxZoomScale;
		minZoomScale = other.minZoomScale;
	}
	// Return the current object
	return(*this);
}




/**
 * operator!=
 *
 * This function checks if two CoordinateSystem2D objects are not equal.
 * It does this by comparing the current object with another object.
 * If they are not equal, it returns true; otherwise, it returns false.
 *
 * @param other: The instance to compare with.
 * @return: true if the instances are not equal, false otherwise.
 */
bool CoordinateSystem2D :: operator!=(const CoordinateSystem2D &other)
{
	// Initialize a boolean variable 'notEqual' to false.
	bool notEqual = false;
	
	// Check if the current object and the other object are the same instance.
	if (this == &other)
	{
		notEqual = true;
	}
	
	// Returns the value of 'notEqual'.
	return(notEqual);
}


/**
 * CoordinateSystem2D::operator+=
 *
 * Overloads the '+=' operator for the CoordinateSystem2D class.
 * This operator increments the zoom scale and offset of the current object by the zoom scale and offset of the other object.
 *
 * @param other: The CoordinateSystem2D object whose zoom scale and offset are added.
 */
void CoordinateSystem2D::operator+=(const CoordinateSystem2D& other)
{
	/// Increment the zoom scale and offset of the current object by the zoom scale and offset of the other object.
	zoomScale += other.zoomScale;
	offset += other.offset;
}


/**
 * CoordinateSystem2D::operator-=
 *
 * Overloads the '-=' operator for the CoordinateSystem2D class.
 * This operator decrements the zoom scale and offset of the current object by the zoom scale and offset of the other object.
 *
 * @param other: The CoordinateSystem2D object whose zoom scale and offset are subtracted.
 */
void CoordinateSystem2D::operator-=(const CoordinateSystem2D& other)
{
	/// Decrement the zoom scale and offset of the current object by the zoom scale and offset of the other object.
	zoomScale -= other.zoomScale;
	offset -= other.offset;
}


/**
 * CoordinateSystem2D::operator*=
 *
 * Overloads the '*=' operator for the CoordinateSystem2D class.
 * This operator multiplies the zoom scale of the current object by the zoom scale of the other object and increments the offset of the current object by the offset of the other object.
 *
 * @param other: The CoordinateSystem2D object whose zoom scale is multiplied and offset is added.
 */
void CoordinateSystem2D::operator*=(const CoordinateSystem2D& other)
{
	/// Multiply the zoom scale of the current object by the zoom scale of the other object and increment the offset of the current object by the offset of the other object.
	zoomScale *= other.zoomScale;
	offset += other.offset;
}


/**
 * CoordinateSystem2D::operator/=
 *
 * Overloads the '/=' operator for the CoordinateSystem2D class.
 * This operator divides the zoom scale of the current object by the zoom scale of the other object and decrements the offset of the current object by the offset of the other object.
 * It also checks if the zoom scale of the other object is not zero to avoid division by zero.
 *
 * @param other: The CoordinateSystem2D object whose zoom scale is divided and offset is subtracted.
 */
void CoordinateSystem2D::operator/=(const CoordinateSystem2D& other)
{
	/// Check if the zoom scale of the other object is not zero to avoid division by zero.
	assert(other.zoomScale != 0);
	
	/// Divide the zoom scale of the current object by the zoom scale of the other object and decrement the offset of the current object by the offset of the other object.
	zoomScale /= other.zoomScale;
	offset -= other.offset;
}



/**
 * set(Square coordinateSystemBounds)
 *
 * Sets the size of the canvas to the size of the provided square.
 * It also recalculates the maximum and minimum zoom scales.
 *
 * @param coordinateSystemBounds: The square to set the size of the canvas to.
 */
void CoordinateSystem2D :: set(Square coordinateSystemBounds)
{
	/// Set the size of the canvas to the size of the provided square
	canvas = coordinateSystemBounds;
	
	/// Recalculate the maximum and minimum zoom scales
	maxZoomScale = canvas.size / ofGetWidth();
	minZoomScale = ofGetWidth() / canvas.size;
}

/**
 * resetCoordinateSystem()
 *
 * Resets the coordinate system to the initial state.
 */
void CoordinateSystem2D :: resetCoordinateSystem()
{
	/// Reset the zoom scale and inverse zoom scale
	zoomScale = 0.125;
	inverseZoomScale = 1 / zoomScale;
	
	/// Reset the offset
	offset.set(0 + ofGetWidth()*0.5, 0 + ofGetHeight()*0.5);
}




/**
 * mouseDragged
 *
 * This function handles the event of the mouse being dragged. It updates the offset based on the mouse movement.
 * The offset is updated by subtracting the previous mouse position from the current mouse position.
 *
 * @param x: The x-coordinate of the mouse cursor.
 * @param y: The y-coordinate of the mouse cursor.
 * @param button: The mouse button that is dragged.
 */
void CoordinateSystem2D::mouseDragged(int x, int y, int button)
{
	/// If the left mouse button is dragged, update the offset
	if (button == 0)
	{
		// The offset is updated by subtracting the previous mouse position from the current mouse position
		offset -= Vec2D(x - ofGetPreviousMouseX(), y - ofGetPreviousMouseY());
	}
}


/**
 * mousePressed(int x, int y, int button)
 *
 * This function handles the event when the mouse button is pressed.
 * Specifically, it checks if the left mouse button is pressed.
 * If it is, it sets the 'isDragging' field to true, indicating that the canvas is being dragged.
 *
 * @param x: The x-coordinate of the mouse cursor.
 * @param y: The y-coordinate of the mouse cursor.
 * @param button: The mouse button that is pressed.
 */
void CoordinateSystem2D::mousePressed(int x, int y, int button)
{
	/// Check if the left mouse button is pressed (if button parameter is 0)
	if (button == 0)
	{
		// Set 'isDragging' to true, indicating that the canvas is being dragged
		isDragging = true;
	}
}


/**
 * mouseReleased(int x, int y, int button)
 *
 * Handles the mouse released event.
 * If the left mouse button is released, it stops dragging the canvas.
 *
 * @param x: The x-coordinate of the mouse cursor.
 * @param y: The y-coordinate of the mouse cursor.
 * @param button: The mouse button that is released.
 */
void CoordinateSystem2D::mouseReleased(int x, int y, int button)
{
	/// If the left mouse button is released, stop dragging the canvas
	if (isDragging && button == 0)
	{
		isDragging = false;
	}
}

/**
 * mouseScrolled(int x, int y, float scrollX, float scrollY)
 *
 * This function handles the event of the mouse scroll. It updates the zoom scale based on the scroll amount.
 * The scroll amount is calculated by multiplying the scrollY with zoomIncrement. The zoom scale is then updated
 * by adding the scroll amount to the current zoom scale. The zoom scale is then clamped to ensure it stays within
 * the valid range defined by the minimum and maximum zoom scales. The inverse zoom scale is then updated by taking
 * the reciprocal of the zoom scale. Finally, the offset is updated to allow the user to zoom into the position of the mouse.
 *
 * @param x: The x-coordinate of the mouse cursor.
 * @param y: The y-coordinate of the mouse cursor.
 * @param scrollX: The amount of horizontal scroll.
 * @param scrollY: The amount of vertical scroll.
 */
void CoordinateSystem2D::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	// Store the last zoom scale
	float lastZoomScale = zoomScale;
	
	// Calculate the scroll amount
	float scrollAmount = scrollY * zoomIncrement;  // The amount scrolled is controlled by the arbitrarily defined zoomIncrement
	
	// Update zoomScale
	zoomScale += scrollAmount;   // Add the scroll amount to the current zoom scale
	
	
	/// Recalculate the maximum and minimum zoom scales
	maxZoomScale = canvas.size / ofGetWidth();
	minZoomScale = ofGetWidth() / canvas.size;
	
	
	// Clamp the zoom scale to ensure it is within a valid range
	zoomScale = ofClamp(zoomScale, minZoomScale, maxZoomScale);    // The zoom scale must be between the minimum and maximum zoom scales
	
	
	// Update the inverse zoom scale
	inverseZoomScale = 1 / zoomScale;
	
	
	
	// Update the offset to allow the user to zoom into the position of the mouse
	offset -= (Vec2D(x - offset.x, y - offset.y) * (zoomScale - lastZoomScale)) / lastZoomScale; // The offset is updated relative to the position of the mouse
}


/**
 * windowResized
 *
 * This function is called when the window is resized. It recalculates the maximum and minimum zoom scales
 * based on the new window size. The maximum zoom scale is calculated by dividing the size of the canvas by the
 * new window width. The minimum zoom scale is calculated by dividing the new window width by the size of the canvas.
 *
 * @param w: The new width of the window.
 * @param h: The new height of the window.
 */
void CoordinateSystem2D::windowResized(int w, int h)
{
	/// Recalculate the maximum and minimum zoom scales
	maxZoomScale = canvas.size / w; // The maximum zoom scale is the size of the canvas divided by the new window width
	minZoomScale = w / canvas.size; // The minimum zoom scale is the new window width divided by the size of the canvas
}
