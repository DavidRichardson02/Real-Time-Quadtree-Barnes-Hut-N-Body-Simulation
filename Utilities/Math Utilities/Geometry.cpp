//  Geometry.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The 'Vects' header and source files contain code that is not yet incorporated into the larger project and is still in experimental stages of development(probably no point in trying to learn how to make my own graphics thing using OpenGL when graphics won't really be a performance bottleneck for this simulation, that's just a bunch of dots, the real heavy lifting comes from the interactions between these dots and accurately approximating them to balance the insane computational complexity of direct simulations(O(N^2)) with reasonable accuracy, so these will probably find some use in some future thing, who knows, not me. So it almost definitely makes more sense to just use the existing stuff provided by OpenFrameworks.
 */


#include "Geometry.hpp"






/**
 * Circle
 *
 * Default constructor
 * Initializes center and radius to default values
 */
Circle::Circle() : center(Vec2D()), radius(0.0) {}


/**
 * Circle
 *
 * Parameterized constructor
 * @param _center: center position of the circle
 * @param _radius: radius of the circle
 */
Circle::Circle(const Vec2D& _center, double _radius) : center(_center), radius(_radius) {}


/**
 * area
 *
 * Computes the area of the circle
 * @return: the area of the circle
 */
double Circle::area() const
{
	// Area of a circle is pi*r^2
	return M_PI * std::pow(radius, 2);
}


/**
 * circumference
 *
 * Computes the circumference of the circle
 * @return: the circumference of the circle
 */
double Circle::circumference() const
{
	// Circumference of a circle is 2*pi*r
	return 2 * M_PI * radius;
}


/**
 * containsPoint
 *
 * Checks if a point is inside the circle
 * @param point: the point to check
 * @return: true if the point is inside the circle, false otherwise
 */
bool Circle::containsPoint(const Vec2D &point) const
{
	// Distance between center and point should be less than or equal to radius for point to be inside circle
	return (center - point).vectorSquareLength() <= radius * radius;
}


/**
 * contains
 *
 * Checks if a circle is inside the circle
 * @param position: the center position of the other circle
 * @param radius: the radius of the other circle
 * @return: true if the other circle is inside the circle, false otherwise
 */
bool Circle::contains(const Vec2D& position, const double radius) const
{
	// For another circle to be completely inside, the distance between the centers + radius of the smaller circle should be <= radius of the larger circle
	return (center - position).vectorSquareLength() <= (this->radius - radius) * (this->radius - radius);
}












/**
 * Square
 *
 * Default constructor
 * Initializes center and size to default values
 */
Square::Square() : center(Vec2D(0,0)), size(0) {}


/**
 * Square
 *
 * Parameterized constructor
 * @param _center: the center position of the square
 * @param _size: the size of the square
 */
Square::Square(const Vec2D& _center, double _size) : center(_center), size(_size) {}


/**
 * operator!=
 *
 * Checks if two squares are not equal
 * @param other: the other square to compare with
 * @return: true if the squares are not equal, false otherwise
 */
bool Square::operator!=(const Square& other)
{
	// If this square and the other square are the same, they are not equal
	bool notEqual = false;
	if (this == &other)
	{
		notEqual = true;
	}
	return(notEqual);
}



/**
 * perimeter
 *
 * Computes the perimeter of the square
 * @return: the perimeter of the square
 */
double Square::perimeter() const
{
	// The perimeter of a square is 4 times its side length
	return 4 * size;
}


/**
 * area
 *
 * Computes the area of the square
 * @return: the area of the square
 */
double Square::area() const
{
	// The area of a square is the square of its side length
	return size * size;
}


/**
 * containsPoint
 *
 * Checks if a point is inside the square
 * @param point: the point to check
 * @return: true if the point is inside the square, false otherwise
 */
bool Square::containsPoint(const Vec2D& point) const
{
	// Calculate half the length of the square's side for comparison
	double halfSide = size * 0.5;
	// Check if the x and y coordinates of the point are within the square's boundaries
	return (point.x >= (center.x - halfSide) && point.x <= (center.x + halfSide)) &&
	(point.y >= (center.y - halfSide) && point.y <= (center.y + halfSide));
}


/**
 * contains
 *
 * Checks if a circle is completely inside the square
 * @param position: the center position of the circle
 * @param radius: the radius of the circle
 * @return: true if the circle is entirely inside the square, false otherwise
 */
bool Square::contains(const Vec2D& position, const double radius) const
{
	// For a circle to be completely inside the square, the farthest points of the circle
	// must be inside the square.
	return containsPoint(Vec2D(position.x - radius, position.y)) &&
	containsPoint(Vec2D(position.x + radius, position.y)) &&
	containsPoint(Vec2D(position.x, position.y - radius)) &&
	containsPoint(Vec2D(position.x, position.y + radius));
}


/**
 * intersects
 *
 * Checks if a square intersects with a circle
 * @param circle: the circle to check for intersection
 * @return: true if the square intersects with the circle, false otherwise
 */
bool Square::intersects(const Circle& circle) const {
	// 1. Check if any corner of the square is inside the circle
	double halfSide = size * 0.5;
	std::vector<Vec2D> corners = {
		{center.x - halfSide, center.y - halfSide},
		{center.x + halfSide, center.y - halfSide},
		{center.x - halfSide, center.y + halfSide},
		{center.x + halfSide, center.y + halfSide}
	};
	
	for (const Vec2D& corner : corners) {
		if (circle.containsPoint(corner)) return true;
	}
	
	// 2. Check if the circle is entirely inside the square
	if (this->contains(circle.center, circle.radius)) return true;
	
	return false;
}



/**
 * set
 *
 * Sets the center position and size of the square
 * @param _x: the x-coordinate of the center
 * @param _y: the y-coordinate of the center
 * @param _size: the size of the square
 */
void Square::set(double _x, double _y, double _size)
{
	// Set the center coordinates and the size of the square
	center.x = _x;
	center.y = _y;
	size = _size;
}












/**
 * Sphere
 *
 * Default constructor
 * Initializes center and radius to default values
 */
Sphere::Sphere() : center(Vec3D()), radius(0.0) {}


/**
 * Sphere
 *
 * Parameterized constructor
 * @param _center: the center position of the sphere
 * @param _radius: the radius of the sphere
 */
Sphere::Sphere(const Vec3D& _center, double _radius) : center(_center), radius(_radius) {}


/**
 * volume
 *
 * Computes the volume of the sphere
 * @return: the volume of the sphere
 */
double Sphere::volume() const
{
	// The volume of a sphere is (4/3) * pi * r^3
	return (4.0 / 3.0) * M_PI * std::pow(radius, 3);
}


/**
 * surfaceArea
 *
 * Computes the surface area of the sphere
 * @return: the surface area of the sphere
 */
double Sphere::surfaceArea() const
{
	// The surface area of a sphere is 4 * pi * r^2
	return 4 * M_PI * std::pow(radius, 2);
}


/**
 * containsPoint
 *
 * Checks if a point is inside the sphere
 * @param point: the point to check
 * @return: true if the point is inside the sphere, false otherwise
 */
bool Sphere::containsPoint(const Vec3D& point) const
{
	//double distanceSquared = std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2) + std::pow(point.z - center.z, 2);
	//return distanceSquared <= radius * radius;
	
	
	
	
	// Distance between center and point should be less than or equal to radius for point to be inside sphere
	return (center - point).vectorSquareLength() <= radius * radius;
}


/**
 * contains
 *
 * Checks if a sphere is completely inside the sphere
 * @param position: the center position of the other sphere
 * @param _radius: the radius of the other sphere
 * @return: true if the other sphere is entirely inside the sphere, false otherwise
 */
bool Sphere::contains(const Vec3D& position, const double _radius) const
{
	//double distanceSquared = std::pow(position.x - center.x, 2) + std::pow(position.y - center.y, 2) + std::pow(position.z - center.z, 2);
	//return distanceSquared <= std::pow(radius - _radius, 2);
	
	
	
	
	// For another sphere to be completely inside, the distance between the centers +
	// radius of the smaller sphere should be <= radius of the larger sphere
	return (center - position).vectorSquareLength() <= (radius - _radius) * (radius - _radius);
}












/**
 * Cube
 *
 * Default constructor
 * Initializes center and size to default values
 */
Cube::Cube() : center(0, 0, 0), size(0) {}


/**
 * Cube
 *
 * Parameterized constructor
 * @param _center: the center position of the cube
 * @param _size: the size of the cube
 */
Cube::Cube(const Vec3D& _center, double _size) : center(_center), size(_size) {}



/**
 * surfaceArea
 *
 * Computes the surface area of the cube
 * @return: the surface area of the cube
 */
double Cube::surfaceArea() const
{
	// The surface area of a cube is 6 * side_length^2
	return 6 * size * size;
}


/**
 * volume
 *
 * Computes the volume of the cube
 * @return: the volume of the cube
 */
double Cube::volume() const
{
	// The volume of a cube is side_length^3
	return size * size * size;
}



/**
 * containsPoint
 *
 * Checks if a point is inside the cube
 * @param point: the point to check
 * @return: true if the point is inside the cube, false otherwise
 */
bool Cube::containsPoint(const Vec3D& point) const
{
	double halfSide = size * 0.5;
	return (point.x >= (center.x - halfSide) && point.x <= (center.x + halfSide)) &&
	(point.y >= (center.y - halfSide) && point.y <= (center.y + halfSide)) &&
	(point.z >= (center.z - halfSide) && point.z <= (center.z + halfSide));
}


/**
 * contains
 *
 * Checks if a sphere is completely inside the cube
 * @param position: the center position of the sphere
 * @param radius: the radius of the sphere
 * @return: true if the sphere is entirely inside the cube, false otherwise
 */
bool Cube::contains(const Vec3D& position, const double radius) const
{
	// For a sphere to be completely inside the cube, the farthest points of the sphere must be inside the cube.
	return containsPoint(Vec3D(position.x - radius, position.y, position.z)) &&
	containsPoint(Vec3D(position.x + radius, position.y, position.z)) &&
	containsPoint(Vec3D(position.x, position.y - radius, position.z)) &&
	containsPoint(Vec3D(position.x, position.y + radius, position.z)) &&
	containsPoint(Vec3D(position.x, position.y, position.z - radius)) &&
	containsPoint(Vec3D(position.x, position.y, position.z + radius));
}


