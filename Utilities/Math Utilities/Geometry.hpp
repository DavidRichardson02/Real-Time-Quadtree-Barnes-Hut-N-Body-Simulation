//  Geometry.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include <math.h>
#include <vector>
#include "Vects.hpp"


/**
 dev NOTE:
 The 'Geometry' header and source files contain code that is not yet incorporated into the larger project and is still in experimental stages of development(probably no point in trying to learn how to make my own graphics thing using OpenGL when graphics won't really be a performance bottleneck for this simulation, that's just a bunch of dots, the real heavy lifting comes from the interactions between these dots and accurately approximating them to balance the insane computational complexity of direct simulations(O(N^2)) with reasonable accuracy, so these will probably find some use in some future thing, who knows, not me. So it almost definitely makes more sense to just use the existing stuff provided by OpenFrameworks.
 */




/**
 * Circle class representing 2D circle.
 *
 * The Circle class represents a circle in a 2D plane with a center point and a radius.
 * It provides geometric computations for the area and circumference of the circle.
 *
 * All computations and checks are based on the Euclidean geometry of the circle.
 */
class Circle
{
public:
	/// @section Constructors
	Circle(); // Default constructor
	Circle(const Vec2D& _center, double _radius); // Construct with provided center and radius
	
	
	
	/// @section Geometry computations
	double area() const; // Computing area
	double circumference() const; // Computing circumference
	
	
	
	/// @section Containment checks
	bool containsPoint(const Vec2D& point) const; // Check if a point is inside the circle
	bool contains(const Vec2D& position, const double radius) const; // Check if a two-D position with a radius is inside the circle
	
	
	
	/// @section Member variables
	Vec2D center; // The center of the circle
	double radius; // The radius of the circle
};








/**
 * Square class representing a 2D square.
 *
 * The Square class represents a square in a 2D plane with a center point and a size.
 * Provides containment checks to determine if a point or another square
 * with a specified position and size is within the bounds of the square.
 * It provides geometric computations for the area and perimeter of the square.
 * The square's center, size, and inequality with another Square object can be set and checked
 * using its constructors and other member functions.
 *
 * All computations and checks are based on the Euclidean geometry of the square.
 */
class Square
{
public:
	/// @section Constructors
	Square(); // Default constructor
	Square(const Vec2D& _center, double _size); // Construct with provided center and size
	
	
	
	/// @section Comparison operators
	bool operator!=(const Square& other); // Checks inequality with another Square object
	
	
	
	/// @section Geometry computations
	double perimeter() const; // Compute Perimeter
	double area() const; // Compute Area
	
	
	
	/// @section Containment and Intersection checks
	bool containsPoint(const Vec2D& point) const; // Check if a point is inside the square
	bool contains(const Vec2D& position, const double radius) const; // Check if a two-D position with a radius is inside the square
	bool intersects(const Circle& circle) const; // Check if the square intersects with a circle
	
	
	
	/// @section Configurations
	void set(double _x, double _y, double _size); // Set the center and size of the square
	
	
	
	/// @section Member variables
	Vec2D center; // The center of the square
	double size; // The size of the square
};









/**
 * Sphere class representing a 3D sphere.
 *
 * The Sphere class represents a sphere in a 3D space with a center point and a radius.
 * It provides geometric computations for the volume and surface area of the sphere.
 * The Sphere class provides containment checks to determine if a point or another sphere
 * with a specified position and radius is within the bounds of the sphere.
 * All computations and checks are based on the Euclidean geometry of the sphere.
 */
class Sphere
{
public:
	/// @section Constructors
	Sphere(); // Default constructor
	Sphere(const Vec3D& _center, double _radius); // Construct with provided center and radius
	
	
	
	/// @section Geometry computations
	double volume() const; // Computing volume
	double surfaceArea() const; // Computing surface area
	
	
	
	/// @section Containment checks
	bool containsPoint(const Vec3D& point) const; // Check if a 3D point is inside the sphere
	bool contains(const Vec3D& position, const double _radius) const; // Check if a 3D position with a radius is inside the Sphere
	
	
	
	
	/// @section Member variables
	Vec3D center; // The position of the center of the sphere
	double radius; // The radius of the sphere
};








/**
 * Cube class representing a 3D cube.
 *
 * The Cube class represents a cube in a 3D space with a center point and a size (length of one side).
 * It provides geometric computations for the volume and surface area of the cube.
 * The Cube class provides containment checks to determine if a point or another cube
 * with a specified position and size is within the bounds of the cube.
 * All computations and checks are based on the Euclidean geometry of the cube.
 */
class Cube
{
public:
	/// @section Constructors
	Cube(); // Default constructor
	Cube(const Vec3D& _center, double _size); // Construct with provided center and size
	
	
	
	/// @section Geometry computations
	double surfaceArea() const; // Compute Surface Area
	double volume() const; // Compute Volume
	
	
	
	/// @section Containment checks
	bool containsPoint(const Vec3D& point) const; // Check if a 3D point is inside the cube
	bool contains(const Vec3D& position, const double radius) const; // Check if a 3D position with a radius is inside the cube
	
	
	
	
	/// @section Member variables
	Vec3D center; // The center of the cube
	double size; // The size of the cube
};





