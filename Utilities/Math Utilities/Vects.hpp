//  Vects.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The 'Vects' header and source files contain code that is not yet incorporated into the larger project and is still in experimental stages of development(probably no point in trying to learn how to make my own graphics thing using OpenGL when graphics won't really be a performance bottleneck for this simulation, that's just a bunch of dots, the real heavy lifting comes from the interactions between these dots and accurately approximating them to balance the insane computational complexity of direct simulations(O(N^2)) with reasonable accuracy, so these will probably find some use in some future thing, who knows, not me. So it almost definitely makes more sense to just use the existing stuff provided by OpenFrameworks.
 */

/**
 * Vec2D and Vec3D Classes: Provide an abstraction for two-dimensional and three-dimensional Euclidean vectors, encapsulating the vector's components (x, y) and (x, y, z) respectively
 *
 * These classes encapsulates a vector's components and provide methods
 * to perform basic vector operations and manipulate vector data.
 */


#pragma once
#include <math.h>




/// Vec2D class representing a 2D Vector
class Vec2D
{
public:
	/// @section Constructors and Destructor
	Vec2D(); // Default constructor
	Vec2D(double _x, double _y); // Construct with provided x and y values
	Vec2D(const Vec2D &other); // Construct by copying another Vec2D object
	Vec2D(double magnitude); // Construct with provided magnitude
	~Vec2D(); // Destructor
	
	
	
	/// @section Comparison operators
	bool operator!=(const Vec2D& other); // Checks inequality with another Vec2D object
	
	
	
	/// @section Accessor operators (Return new Vec2D based on current one)
	Vec2D operator+(const Vec2D& other) const; // Adds this vector with another
	Vec2D operator-(const Vec2D& other) const; // Subtracts another vector from this vector
	Vec2D operator*(const double scalar) const; // Multiplies this vector by a scalar
	Vec2D operator/(const double scalar) const; // Divides this vector by a scalar
	
	
	
	/// @section Modifier operators (Modify the current Vec2D and return reference)
	Vec2D& operator=(const Vec2D& other); // Assigns this vector the values of another
	void operator+=(const Vec2D& other); // Adds another vector to this vector and assigns the result to this vector
	void operator-=(const Vec2D& other); // Subtracts another vector from this vector and assigns the result to this vector
	void operator*=(const double scalar); // Multiplies this vector by a scalar and assigns the result to this vector
	void operator/=(const double scalar); // Divides this vector by a scalar and assigns the result to this vector
	
	
	
	
	/// @section Vector operations
	Vec2D scaleVector(double scalar) const; // Returns a new vector that is this vector scaled by a scalar
	double vectorLength() const; // Returns the length of this vector
	double vectorSquareLength() const; // Returns the square of the length of this vector
	void vectorNormalize(); // Normalizes this vector
	Vec2D vectorGetNormalized() const; // Returns a new vector that is a normalized version of this vector
	double vectorDistance(const Vec2D& other); // Returns the distance between this vector and another vector
	void set(double _x, double _y); // Sets the x and y values of this vector
	void reset(); // Resets this vector to the zero vector
	
	
	/// @section Member variables
	double x; // The x component of this vector
	double y; // The y component of this vector
};




/// Vec3D class representing a 3D Vector
class Vec3D
{
public:
	/// @section Constructors and Destructor
	Vec3D(); // Default constructor
	Vec3D(double _x, double _y, double _z); // Construct with provided x, y, and z values
	Vec3D(const Vec3D &other); // Construct by copying another Vec3D object
	Vec3D(double magnitude); // Construct with provided magnitude
	~Vec3D(); // Destructor
	
	
	
	/// @section Comparison operators
	bool operator!=(const Vec3D& other); // Checks inequality with another Vec3D object
	
	
	
	/// @section Accessor operators (Return new Vec2D based on current one)
	Vec3D operator+(const Vec3D& other) const; // Adds this vector with another
	Vec3D operator-(const Vec3D& other) const; // Subtracts another vector from this vector
	Vec3D operator*(const double scalar) const; // Multiplies this vector by a scalar
	Vec3D operator/(const double scalar) const; // Divides this vector by a scalar
	
	
	
	/// @section Modifier operators  (Modify the current Vec3D and return reference)
	Vec3D& operator=(const Vec3D& other); // Assigns this vector the values of another
	void operator+=(const Vec3D& other); // Adds another vector to this vector and assigns the result to this vector
	void operator-=(const Vec3D& other); // Subtracts another vector from this vector and assigns the result to this vector
	void operator*=(const double scalar); // Multiplies this vector by a scalar and assigns the result to this vector
	void operator/=(const double scalar); // Divides this vector by a scalar and assigns the result to this vector
	
	
	
	/// @section Vector operations
	Vec3D scaleVector(double scalar) const; // Returns a new vector that is this vector scaled by a scalar
	double vectorLength() const; // Returns the length of this vector
	double vectorSquareLength() const; // Returns the square of the length of this vector
	void vectorNormalize(); // Normalizes this vector
	Vec3D vectorGetNormalized() const; // Returns a new vector that is a normalized version of this vector
	double vectorDistance(const Vec3D& other); // Returns the distance between this vector and another vector
	void set(double _x, double _y, double _z); // Sets the x, y, and z values of this vector
	
	
	
	/// @section Member variables
	double x; // The x component of this vector
	double y; // The y component of this vector
	double z; // The z component of this vector
};
