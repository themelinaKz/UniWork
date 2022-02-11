#ifndef _Vec3_
#define _Vec3_

#include <cstddef>

namespace math {

	template <typename S>
	class Vec3 {
		private:
			static S zero;

		public:
			union { S x, r; }; 
			union { S y, g; };
			union { S z, b; }; 

			Vec3<S> clampToLowerBound(S val) const {
				Vec3<S> v;
				v.x = x < val ? val : x;
				v.y = y < val ? val : y;
				v.z = z < val ? val : z;
				return v;
			}

			Vec3<S> clampToUpperBound(S val) const {
				Vec3<S> v;
				v.x = x > val ? val : x;
				v.y = y > val ? val : y;
				v.z = z > val ? val : z;
				return v;
			}

			
			S & operator [] (size_t index) {
				return *((S*)this + index);
			}

			
			Vec3<S> operator + (const Vec3<S> & right) {
				Vec3<S> left;
				left.x = x + right.x;
				left.y = y + right.y;
				left.z = z + right.z;
				return left;
			}

			
			Vec3<S> operator - (const Vec3<S> & right) {
				Vec3<S> left;
				left.x = x - right.x;
				left.y = y - right.y;
				left.z = z - right.z;
				return left;
			}
			
			Vec3<S> operator * (const Vec3<S> & right) {
				Vec3<S> left;
				left.x = x * right.x;
				left.y = y * right.y;
				left.z = z * right.z;
				return left;
			}
			
			Vec3<S> operator * (S right) {
				Vec3<S> left;
				left.x = x * right;
				left.y = y * right;
				left.z = z * right;
				return left;
			}
			
			Vec3<S> operator / (S right) {
				Vec3<S> left;
				left.x = x / right;
				left.y = y / right;
				left.z = z / right;
				return left;
			}

			Vec3<S> operator / (const Vec3<S> & right) {
				Vec3<S> left;
				left.x = x / right.x;
				left.y = y / right.y;
				left.z = z / right.z;
				return left;
			}
			
			Vec3<S> & operator += (const Vec3<S> & right) {
				x += right.x;
				y += right.y;
				z += right.z;
				return *this;
			}
			
			Vec3<S> & operator -= (const Vec3<S> & right) {
				x -= right.x;
				y -= right.y;
				z -= right.z;
				return *this;
			}
			
			Vec3<S> & operator /= (const Vec3<S> & right) {
				x /= right.x;
				y /= right.y;
				z /= right.z;
				return *this;
			}
			
			Vec3<S> & operator *= (const Vec3<S> & right) {
				x *= right.x;
				y *= right.y;
				z *= right.z;
				return *this;
			}
			
			Vec3<S> & operator *= (S right) {
				x *= right;
				y *= right;
				z *= right;
				return *this;
			}

			Vec3<S> & operator /= (S right) {
				x /= right;
				y /= right;
				z /= right;
				return *this;
			}

			Vec3<S>(S x, S y, S z) : x(x), y(y), z(z) {}
			
			Vec3<S>(S val) : x(val), y(val), z(val) {}
			
			Vec3<S>() : x(), y(), z() {}

			Vec3<S>(const Vec3<S> & right) : x(right.x), y(right.y), z(right.z) {}

			Vec3<S> & operator = (const Vec3<S> & right) {
				x = right.x;
				y = right.y;
				z = right.z;
				return *this;
			}

			bool operator == (const Vec3<S> & right) const {
				return x == right.x && y == right.y && z == right.z;
			}

			bool operator != (const Vec3<S> & right) const {
				return x != right.x || y != right.y || z != right.z;
			}
	};

	/*! Scalar-vector multiplication.
	*
	* \param a is the left-hand-side scalar multiplier.
	* \param v is the right-hand-side vector multiplicand.
	*
	* \return a new vector whose elements are the elements of the vector v multiplied with the scalar a.
	*/
	template<typename S>
	Vec3<S> operator * (S a, Vec3<S> v) {
		return v*a;
	}

	/*! Scalar-vector multiplication with scalar promotion to typename S.
	*
	* \param a is the left-hand-side scalar multiplier.
	* \param v is the right-hand-side vector multiplicand.
	*
	* \return a new vector whose elements are the elements of the vector v multiplied with the scalar a.
	*/
	template<typename S>
	Vec3<S> operator * (int a, Vec3<S> v) {
		return v*S(a);
	}

	/*! Vector-scalar multiplication with scalar promotion to typename S.
	*
	* \param v is the left-hand-side vector multiplicand.
	* \param a is the right-hand-side scalar multiplier.
	*
	* \return a new vector whose elements are the elements of the vector v multiplied with the scalar a.
	*/
	template<typename S>
	Vec3<S> operator * (Vec3<S> v, int a) {
		return v*S(a);
	}

	/*! Vector division by a scalar, using scalar promotion to typename S.
	*
	* \param v is the vector divident.
	* \param a is the scalar divisor.
	*
	* \return a new vector whose elements are the elements of the vector v divided by the scalar a.
	*/
	template<typename S>
	Vec3<S> operator / (Vec3<S> v, int a) {
		return v/S(a);
	}

	template <typename S> S Vec3<S>::zero = S(0);

} // namespace math

#endif