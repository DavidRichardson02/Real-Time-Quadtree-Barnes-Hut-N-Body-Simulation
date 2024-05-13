//  Vects.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The 'Vects' header and source files contain code that is not yet incorporated into the larger project and is still in experimental stages of development(probably no point in trying to learn how to make my own graphics thing using OpenGL when graphics won't really be a performance bottleneck for this simulation, that's just a bunch of dots, the real heavy lifting comes from the interactions between these dots and accurately approximating them to balance the insane computational complexity of direct simulations(O(N^2)) with reasonable accuracy, so these will probably find some use in some future thing, who knows, not me. So it almost definitely makes more sense to just use the existing stuff provided by OpenFrameworks.
 */


#include "Vects.hpp"






/**
 * Vec2D::Vec2D
 *
 * Default constructor for the Vec2D class.
 * Initializes a new instance of the Vec2D class with both components (x, y) set to zero.
 */
Vec2D::Vec2D() : x(0), y(0)
{
	// Both components are initialized to zero
}


/**
 * Vec2D::Vec2D
 *
 * Constructor with parameters for the Vec2D class.
 * Initializes a new instance of the Vec2D class with the specified components.
 *
 * @param _x: The x component of the vector.
 * @param _y: The y component of the vector.
 */
Vec2D::Vec2D(double _x, double _y) : x(_x), y(_y)
{
	// The components are assigned the values provided as parameters
}


/**
 * Vec2D::Vec2D
 *
 * Copy constructor for the Vec2D class.
 * Initializes a new instance of the Vec2D class, copying the components from another instance.
 *
 * @param other: The instance to copy the components from.
 */
Vec2D::Vec2D(const Vec2D &other) : x(other.x), y(other.y)
{
	// The components are copied from the other instance
}


/**
 * Vec2D::Vec2D
 *
 * Constructor with magnitude for the Vec2D class.
 * Initializes a new instance of the Vec2D class with a specified magnitude and a random direction.
 *
 * @param magnitude: The magnitude of the vector.
 */
Vec2D::Vec2D(double magnitude)
{
	/// Generate a random direction
	double theta = acos(2/sqrt(magnitude)*1);
	
	// Compute the components based on the magnitude and the generated direction
	x = magnitude * cos(theta);
	y = magnitude * sin(theta);
}


/**
 * Vec2D::~Vec2D
 *
 * Destructor for the Vec2D class.
 * Resets the components (x, y) of the Vec2D instance to zero.
 */
Vec2D::~Vec2D()
{
	// Reset the components to zero
	x = 0;
	y = 0;
}




/**
 * Vec2D::operator!=
 *
 * Not-equal-to operator overload for the Vec2D class.
 * Checks if this instance is not equal to another instance.
 *
 * @param other: The instance to compare with.
 * @return: true if the instances are not equal, false otherwise.
 */
bool Vec2D::operator!=(const Vec2D& other)
{
	// Initialize the result as false (equal)
	bool notEqual = false;
	
	/// Check if the instances are the same
	if (this == &other)
	{
		// If they are the same, set the result to true (not equal)
		notEqual = true;
	}
	
	// Return the result
	return(notEqual);
}


/**
 * Vec2D::operator=
 *
 * Assignment operator overload for the Vec2D class.
 * Assigns the components of another instance to this instance.
 *
 * @param other: The instance to copy the components from.
 * @return: A reference to this instance.
 */
Vec2D& Vec2D::operator=(const Vec2D& other)
{
	/// Check if the instances are not the same
	if (this != &other)
	{
		// If they are not the same, copy the components
		x = other.x;
		y = other.y;
	}
	
	// Return a reference to this instance
	return(*this);
}


/**
 * Vec2D::operator+
 *
 * Addition operator overload for the Vec2D class.
 * Adds the components of this instance and another instance.
 *
 * @param other: The instance to add the components from.
 * @return: A new instance with the added components.
 */
Vec2D Vec2D::operator+(const Vec2D& other) const
{
	// Create a new instance with the added components and return it
	return(Vec2D(x + other.x, y + other.y));
}


/**
 * operator-
 *
 * Subtraction operator overload for the Vec2D class.
 * Subtracts the components of another instance from this instance.
 *
 * @param other: The instance to subtract the components from.
 * @return: A new instance with the subtracted components.
 */
Vec2D Vec2D::operator-(const Vec2D& other) const
{
	// Create a new instance with the subtracted components and return it
	return(Vec2D(x - other.x, y - other.y));
}


/**
 * operator*
 *
 * Multiplication operator overload for the Vec2D class.
 * Multiplies the components of this instance by a scalar.
 *
 * @param scalar: The scalar to multiply the components by.
 * @return: A new instance with the multiplied components.
 */
Vec2D Vec2D::operator*(const double scalar) const
{
	// Create a new instance with the multiplied components and return it
	return(Vec2D(x * scalar, y * scalar));
}


/**
 * operator/
 *
 * Division operator overload for the Vec2D class.
 * Divides the components of this instance by a scalar.
 *
 * @param scalar: The scalar to divide the components by.
 * @return: A new instance with the divided components.
 */
Vec2D Vec2D::operator/(const double scalar) const
{
	// Create a new instance with the divided components and return it
	return(Vec2D(x / scalar, y / scalar));
}




/**
 * operator+=
 *
 * Addition-assignment operator overload for the Vec2D class.
 * Adds the components of another instance to this instance.
 *
 * @param other: The instance to add the components from.
 */
void Vec2D::operator+=(const Vec2D& other)
{
	// Add the components
	x = x + other.x;
	y = y + other.y;
}


/**
 * operator-=
 *
 * Subtraction-assignment operator overload for the Vec2D class.
 * Subtracts the components of another instance from this instance.
 *
 * @param other: The instance to subtract the components from.
 */
void Vec2D::operator-=(const Vec2D& other)
{
	// Subtract the components
	x = x - other.x;
	y = y - other.y;
}


/**
 * operator*=
 *
 * Multiplication-assignment operator overload for the Vec2D class.
 * Multiplies the components of this instance by a scalar.
 *
 * @param scalar: The scalar to multiply the components by.
 */
void Vec2D::operator*=(const double scalar)
{
	// Multiply the components
	x = x * scalar;
	y = y * scalar;
}


/**
 * operator/=
 *
 * Division-assignment operator overload for the Vec2D class.
 * Divides the components of this instance by a scalar.
 * If the scalar is zero, no operation is performed to avoid division by zero.
 *
 * @param scalar: The scalar to divide the components by.
 */
void Vec2D::operator/=(const double scalar)
{
	// Check if scalar is not zero to avoid division by zero
	if (scalar != 0)
	{
		/// Calculate the inverse of the scalar
		double inverseScalar = 1 / scalar;
		
		// Multiply the x and y components of the Vec2D object by the inverse of the scalar
		x = x * inverseScalar;
		y = y * inverseScalar;
	}
}




/**
 * scaleVector
 *
 * Scales a vector by a given scalar.
 * First, the vector is normalized, and then it is multiplied by the scalar.
 * The function does not modify the original vector, but returns a new one.
 *
 * @param scalar: The scalar to scale the vector by.
 * @return: A new instance of the vector scaled by the scalar.
 */
Vec2D Vec2D::scaleVector(double scalar) const
{
	/// Normalize the vector and scale it
	Vec2D scaledVector = vectorGetNormalized();
	scaledVector = scaledVector * scalar;
	return(scaledVector);
}


/**
 * vectorLength
 *
 * Calculates and returns the length of the vector.
 * The length is calculated using the Pythagorean theorem.
 *
 * @return: The length of the vector.
 */
double Vec2D::vectorLength() const
{
	/// Calculate the length using the Pythagorean theorem
	return(sqrt(x * x + y * y));
}


/**
 * vectorSquareLength
 *
 * Returns the square of the length of the vector.
 * This function is more efficient than calculating the length itself,
 * especially if you only need to compare lengths.
 *
 * @return: The square of the length of the vector.
 */
double Vec2D::vectorSquareLength() const
{
	/// Calculate the square of the length
	return(x * x + y * y);
}


/**
 * vectorNormalize
 *
 * Normalizes the vector, i.e., scales it to have length 1.
 * If the length of the vector is zero, the function does nothing.
 */
void Vec2D::vectorNormalize()
{
	double length = vectorLength();
	if (length != 0)
	{
		/// Normalize the vector if its length is non-zero
		double inverseLength = 1 / length;
		x *= inverseLength;
		y *= inverseLength;
	}
}


/**
 * vectorGetNormalized
 *
 * Returns a normalized version of the vector, i.e., a vector in the same direction but with length 1.
 * If the length of the vector is zero, returns the original vector (which is the zero vector).
 *
 * @return: A new instance of the vector normalized.
 */
Vec2D Vec2D::vectorGetNormalized() const
{
	double length = vectorLength();
	if (length != 0)
	{
		/// Normalize the vector if its length is non-zero
		double inverseLength = 1 / length;
		Vec2D normalVec = { x * inverseLength , y * inverseLength };
		return(normalVec);
	}
	else
	{
		/// Return the original vector if its length is zero
		return(*this);
	}
}


/**
 * vectorDistance
 *
 * Calculates the distance between this vector and another vector.
 * The distance is calculated as the length of the difference between the two vectors.
 */
double Vec2D::vectorDistance(const Vec2D& other)
{
	/// Calculate the distance between the vectors
	return(sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)));
}




/**
 * set
 *
 * Sets the x and y components of the vector to the specified values.
 */
void Vec2D::set(double _x, double _y)
{
	/// Assign the new values to the x and y components
	x = _x;
	y = _y;
}



void Vec2D::reset()
{
	/// Reset the x and y components to zero
	x = 0;
	y = 0;
}








/**
 * Vec3D
 *
 * Default constructor for the Vec3D class.
 * Initializes a new instance of the Vec3D class with all components (x, y, z) set to zero.
 */
Vec3D::Vec3D() : x(0), y(0), z(0)
{
	// x, y, z are initialized to zero
}


/**
 * Vec3D
 *
 * Constructor with parameters for the Vec3D class.
 * Initializes a new instance of the Vec3D class with the specified components.
 *
 * @param _x: The x component of the vector.
 * @param _y: The y component of the vector.
 * @param _z: The z component of the vector.
 */
Vec3D::Vec3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
{
	// x, y, z are assigned the values provided as parameters
}


/**
 * Vec3D
 *
 * Copy constructor for the Vec3D class.
 * Initializes a new instance of the Vec3D class, copying the components from another instance.
 *
 * @param other: The instance to copy the components from.
 */
Vec3D::Vec3D(const Vec3D &other) : x(other.x), y(other.y), z(other.z)
{
	// x, y, z are copied from the other instance
}


/**
 * Vec3D
 *
 * Constructor with magnitude for the Vec3D class.
 * Initializes a new instance of the Vec3D class with a specified magnitude and a random direction.
 *
 * @param magnitude: The magnitude of the vector.
 */
Vec3D::Vec3D(double magnitude)
{
	/// Generate a random direction
	double theta = acos(3/sqrt(magnitude)*1);
	
	// Compute the components based on the magnitude and the generated direction
	x = magnitude * cos(theta);
	y = magnitude * sin(theta);
	z = cos(theta) * sin(theta);
}


/**
 * ~Vec3D
 *
 * Destructor for the Vec3D class.
 * Resets the components (x, y, z) of the Vec3D instance to zero.
 */
Vec3D::~Vec3D()
{
	// Reset the components to zero
	x = 0;
	y = 0;
	z = 0;
}


/**
 * operator!=
 *
 * Not-equal-to operator overload for the Vec3D class.
 * Checks if this instance is not equal to another instance.
 *
 * @param other: The instance to compare with.
 * @return: true if the instances are not equal, false otherwise.
 */
bool Vec3D::operator!=(const Vec3D& other)
{
	// Return true if any of the components are not equal, false otherwise
	return(x != other.x || y != other.y || z != other.z);
}


/**
 * operator=
 *
 * Assignment operator overload for the Vec3D class.
 * Assigns the components of another instance to this instance.
 *
 * @param other: The instance to copy the components from.
 * @return: A reference to this instance.
 */
Vec3D& Vec3D::operator=(const Vec3D& other)
{
	/// Check if the instances are not the same
	if (this != &other)
	{
		// If they are not the same, copy the components
		x = other.x;
		y = other.y;
		z = other.z;
	}
	
	// Return a reference to this instance
	return(*this);
}


/**
 * operator+
 *
 * Addition operator overload for the Vec3D class.
 * Adds the components of this instance and another instance.
 *
 * @param other: The instance to add the components from.
 * @return: A new instance with the added components.
 */
Vec3D Vec3D::operator+(const Vec3D& other) const
{
	// Create a new instance with the added components and return it
	return(Vec3D(x + other.x, y + other.y, z + other.z));
}


/**
 * operator-
 *
 * Subtraction operator overload for the Vec3D class.
 * Subtracts the components of another instance from this instance.
 *
 * @param other: The instance to subtract the components from.
 * @return: A new instance with the subtracted components.
 */
Vec3D Vec3D::operator-(const Vec3D& other) const
{
	// Create a new instance with the subtracted components and return it
	return(Vec3D(x - other.x, y - other.y, z - other.z));
}


/**
 * operator*
 *
 * Multiplication operator overload for the Vec3D class.
 * Multiplies the components of this instance by a scalar.
 *
 * @param scalar: The scalar to multiply the components by.
 * @return: A new instance with the multiplied components.
 */
Vec3D Vec3D::operator*(const double scalar) const
{
	// Create a new instance with the multiplied components and return it
	return(Vec3D(x * scalar, y * scalar, z * scalar));
}


/**
 * operator/
 *
 * Division operator overload for the Vec3D class.
 * Divides the components of this instance by a scalar.
 *
 * @param scalar: The scalar to divide the components by.
 * @return: A new instance with the divided components.
 */
Vec3D Vec3D::operator/(const double scalar) const
{
	// Create a new instance with the divided components and return it
	return(Vec3D(x / scalar, y / scalar, z / scalar));
}


/**
 * operator+=
 *
 * Addition-assignment operator overload for the Vec3D class.
 * Adds the components of another instance to this instance.
 *
 * @param other: The instance to add the components from.
 */
void Vec3D::operator+=(const Vec3D& other)
{
	// Add the components
	x = x + other.x;
	y = y + other.y;
	z = z + other.z;
}


/**
 * operator-=
 *
 * Subtraction-assignment operator overload for the Vec3D class.
 * Subtracts the components of another instance from this instance.
 *
 * @param other: The instance to subtract the components from.
 */
void Vec3D::operator-=(const Vec3D& other)
{
	// Subtract the components
	x = x - other.x;
	y = y - other.y;
	z = z - other.z;
}


/**
 * operator*=
 *
 * Multiplication-assignment operator overload for the Vec3D class.
 * Multiplies the components of this instance by a scalar.
 *
 * @param scalar: The scalar to multiply the components by.
 */
void Vec3D::operator*=(const double scalar)
{
	// Multiply the components
	x = x * scalar;
	y = y * scalar;
	z = z * scalar;
}


/**
 * operator/=
 *
 * Division-assignment operator overload for the Vec3D class.
 * Divides the components of this instance by a scalar.
 * If the scalar is zero, no operation is performed to avoid division by zero.
 *
 * @param scalar: The scalar to divide the components by.
 */
void Vec3D::operator/=(const double scalar)
{
	// Check if scalar is not zero to avoid division by zero
	if (scalar != 0)
	{
		/// Calculate the inverse of the scalar
		double inverseScalar = 1 / scalar;
		
		/// Update the components of the Vec3D instance, each component is multiplied by the inverse of the scalar
		x = x * inverseScalar;
		y = y * inverseScalar;
		z = z * inverseScalar;
	}
}




/**
 * Vec3D::scaleVector
 *
 * Returns a new vector that is a scaled version of this vector.
 * The scaling operates uniformly on all components.
 *
 * @param scalar: The factor by which to scale the vector.
 * @return: A new instance of the vector scaled.
 */
Vec3D Vec3D::scaleVector(double scalar) const
{
	// Create a new vector with components scaled by the scalar and return it
	Vec3D scaledVector = { x * scalar, y * scalar ,z * scalar };
	return(scaledVector);
}


/**
 * Vec3D::vectorLength
 *
 * Computes the length (magnitude) of the vector.
 * The length is computed as the square root of the sum of the squares of the components.
 *
 * @return: The length of the vector.
 */
double Vec3D::vectorLength() const
{
	// Compute and return the length of the vector
	return(sqrt(x * x + y * y + z * z));
}


/**
 * Vec3D::vectorSquareLength
 *
 * Computes the square of the length (magnitude) of the vector.
 * The square of the length is computed as the sum of the squares of the components.
 *
 * @return: The square of the length of the vector.
 */
double Vec3D::vectorSquareLength() const
{
	// Compute and return the square of the length of the vector
	return(x * x + y * y + z * z);
}


/**
 * Vec3D::vectorNormalize
 *
 * Normalizes the vector by dividing each component by the vector's length.
 * If the length of the vector is zero, no operation is performed.
 */
void Vec3D::vectorNormalize()
{
	// Compute the length of the vector
	double length = vectorLength();
	
	if (length != 0)
	{
		/// Normalize the vector if its length is non-zero
		// Compute the inverse of the length
		double inverseLength = 1 / length;
		
		// Scale the components by the inverse of the length
		x *= inverseLength;
		y *= inverseLength;
		z *= inverseLength;
	}
	else
	{
		/// Do nothing if the length is zero
		return;
	}
}


/**
 * Vec3D::vectorGetNormalized
 *
 * Returns a new vector that is a normalized version of this vector.
 * The returned vector has the same direction as this vector but a length of 1.
 * If the length of this vector is zero, returns this vector.
 *
 * @return: A new instance of the vector normalized.
 */
Vec3D Vec3D::vectorGetNormalized() const
{
	// Compute the length of the vector
	double length = vectorLength();
	
	if (length != 0)
	{
		/// Normalize the vector if its length is non-zero
		// Compute the inverse of the length
		double inverseLength = 1 / length;
		
		// Create a new vector with components scaled by the inverse of the length and return it
		Vec3D normalVec = { x * inverseLength , y * inverseLength , z * inverseLength };
		return(normalVec);
	}
	else
	{
		/// Return the original vector if its length is zero
		return(*this);
	}
}


/**
 * Vec3D::vectorDistance
 *
 * Computes the Euclidean distance between this vector and another vector.
 * The distance is computed as the length of the difference between the two vectors.
 *
 * @param other: The other vector to compute the distance to.
 * @return: The distance between the vectors.
 */
double Vec3D::vectorDistance(const Vec3D& other)
{
	/// Compute and return the distance between the vectors
	// The distance is the square root of the sum of the squared differences of the components
	return(sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z)));
}
