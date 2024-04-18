#pragma once

#include <cmath>
#include <iostream>

/**
 * Class that represents a 3D vector, using doubles.
 */
class vec3 {
  public:
    double x, y, z;

    /** Construct a new vector with coordinates [0, 0, 0].*/
    vec3();

    /** Construct a new vector.
    *
    * @param x x coordinate.
    * @param y y coordinate.
    * @param z z coordinate.
    */
    vec3(double x, double y, double z);

    /** Access a value in an array-like fashion.
    *
    * @param i the index of the value. 0 for x, 1 for y, and 2 for z.
    * 
    * @returns the coordiante of the requested value, or 0 if index is out of range.
    */
    double get(int i);

    vec3 operator-() const;

    vec3& operator+=(const vec3 &v);

    vec3& operator*=(double t);

    vec3& operator/=(double t);

    /** Compute the length of the vector.
    * 
    * @returns the length of the vector.
    */
    double length() const;

    /** Compute the squared length of the vector.
    * This is faster than computing the actual length.
    * 
    * @returns the squared length of the vector.
    */
    double length_squared() const;

    /** Checks if the vector is of near zero length.
    * 
    * @returns true if all coordinates are small enough.
    */
    bool near_zero() const;

    /** Construct a vector with random coordinates between 0 and 1.*/
    static vec3 random();

    /** Construct a vector with random coordinates between the given range.
    * 
    * @param min the minimum value in the range.
    * @param max the maximum value in the range.
    */
    static vec3 random(double min, double max);
};

/**
 * Class that represents a 3D vector, using ints.
 */
class vec3i {
  public:
  int x, y, z;

  /** Construct a new vector with coordinates [0, 0, 0].*/
  vec3i();

  /** Construct a new vector.
  *
  * @param x x coordinate.
  * @param y y coordinate.
  * @param z z coordinate.
  */
  vec3i(int x, int y, int z);

  /** Access a value in an array-like fashion.
  *
  * @param i the index of the value. 0 for x, 1 for y, and 2 for z.
  * 
  * @returns the coordiante of the requested value, or 0 if index is out of range.
  */
  int get(int i);
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

std::ostream& operator<<(std::ostream &out, const vec3 &v);

vec3 operator+(const vec3 &u, const vec3 &v);

vec3 operator-(const vec3 &u, const vec3 &v);

vec3 operator*(const vec3 &u, const vec3 &v);

vec3 operator*(double t, const vec3 &v);

vec3 operator*(const vec3 &v, double t);

vec3 operator/(vec3 v, double t);

/** Calculate the dot product between the given vectors.
*
* @param u the first vector.
* @param v the second vector.
* 
* @returns the dot product between u and v.
*/
double dot(const vec3 &u, const vec3 &v);

/** Calculate the cross product between the given vectors.
*
* @param u the first vector.
* @param v the second vector.
* 
* @returns the cross product between u and v.
*/
vec3 cross(const vec3 &u, const vec3 &v);

/** Calculate the normalized vector of the given vector.
*
* @param v the vector to normalize.
* 
* @returns a vector with equal direction of v, but of length 1.
*/
vec3 unit_vector(vec3 v);

/** Construct a random vector that has length <= 1.*/
vec3 random_in_unit_sphere();

/** Construct a random unit vector.*/
vec3 random_unit_vector();

/** Construct a random unit vector that lies on the hemisphere around the given normal vector.
*
* @param normal the normal vector defining the hemisphere.
* 
* @returns a random unit vector within the hemisphere.
*/
vec3 random_on_hemisphere(const vec3& normal);

vec3 reflect(const vec3 &v, const vec3 &n);

vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);