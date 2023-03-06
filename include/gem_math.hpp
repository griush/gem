/*
    made by griush
*/

#ifndef GEM_MATH_HPP
#define GEM_MATH_HPP

#include "gem_base.hpp"

// std
#include <cmath>
#include <string>
#include <sstream>
#include <ostream>
#include <format> // c++20

#define GEM_DEBUG 0

#if GEM_DEBUG
#include <iostream>
#define GEM_LOG(x) std::cout << x << std::endl;
#else
#define GEM_LOG(x)
#endif

#define GEM_PI 3.14159265358979

// Basic conversions
// Angles
#define GEM_DEG_TO_RAD 0.017453229252
#define GEM_RAD_TO_DEG 57.29577951

#define GEM_MILI(x) (x * 1000)

namespace gem {
    // snake_case for every name
/*
    // TODO: Review this, not all types should be precision_type 
#ifdef GEM_DOUBLE
    using precision_type = double;
#else
    using precision_type = float;
#endif
*/
    // Temporary, no double supported, always using floats, for now
    using precision_type = float;

    // General functions
    template<typename T>
    T pi()
    {
        return static_cast<T>(GEM_PI);
    }

    // TODO: once all vecotrs and matrices are changed with templates, review precision_type here
    precision_type to_radians(precision_type degrees)
    {
        return degrees * GEM_DEG_TO_RAD;
    }

    precision_type to_degrees(precision_type radians)
    {
        return radians * GEM_RAD_TO_DEG;
    }

    precision_type inverse(precision_type val)
    {
        return 1 / val;
    }

    precision_type max(precision_type a, precision_type b)
    {
        return a > b ? a : b;
    }

    precision_type max(precision_type a, precision_type b, precision_type c)
    {
        return max(max(a, b), c);
    }

    precision_type min(precision_type a, precision_type b)
    {
        return a < b ? a : b;
    }

    precision_type min(precision_type a, precision_type b, precision_type c)
    {
        return min(min(a, b), c);
    }

    precision_type clamp(precision_type val, precision_type min_val, precision_type max_val)
    {
        return min(max(val, min_val), max_val);
    }

    // Vectors
    // vec2
    // Two-component vector
    template<typename T>
    struct vec2
    {
        // Data
        union
        {
            struct
            {
                T x;
                T y;
            };
        };
        
        // Constructors
        vec2() : x(T{}), y(T{})
        {
        }

        vec2(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        vec2(T scalar)
        {
            x = scalar;
            y = scalar;
        }

        // Operations
        vec2<T>& add(const vec2<T>& other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        vec2<T>& substract(const vec2<T>& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        vec2<T>& multiply(const vec2<T>& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            return *this;
        }

        vec2<T>& divide(const vec2<T>& other)
        {
            this->x /= other.x;
            this->y /= other.y;
            return *this;
        }

        // Operations with scalars
        vec2<T>& add(T scalar)
        {
            this->x += scalar;
            this->y += scalar;
            return *this;
        }

        vec2<T>& substract(T scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            return *this;
        }

        vec2<T>& multiply(T scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        vec2<T>& divide(T scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }

        float magnitude() const
        {
            float mag = sqrt(this->x * this->x + this->y * this->y);
            return mag;
        }

        vec2<T>& normalize()
        {
            float mag = magnitude();
            if (mag > 0.0f) {
                precision_type inv_mag = inverse(mag);
                this->x *= inv_mag;
                this->y *= inv_mag;
            }

            return *this;
        }

        vec2<T> normalized() const
        {
            vec2<T> vec(this->x, this->y);
            vec.normalize();

            return vec;
        }

        float dot(const vec2<T>& other) const
        {
            float result = this->x * other.x + this->y * other.y;
            return result;
        }

        vec2<T>* value_ptr()
        {
            return &(*this);
        }

        // Operators
        friend vec2<T> operator+(vec2<T> left, const vec2<T>& right)
        {
            return left.add(right);
        }

        friend vec2<T> operator-(vec2<T> left, const vec2<T>& right)
        {
            return left.substract(right);
        }

        friend vec2<T> operator*(vec2<T> left, const vec2<T>& right)
        {
            return left.multiply(right);
        }

        friend vec2<T> operator/(vec2<T> left, const vec2<T>& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec2<T> operator+(vec2<T> left, T right)
        {
            return left.add(right);
        }

        friend vec2<T> operator-(vec2<T> left, T right)
        {
            return left.substract(right);
        }

        friend vec2<T> operator*(vec2<T> left, T right)
        {
            return left.multiply(right);
        }

        friend vec2<T> operator/(vec2 left, T right)
        {
            return left.divide(right);
        }

        vec2<T>& operator+=(const vec2<T>& other)
        {
            this->add(other);
            return *this;
        }

        vec2<T>& operator-=(const vec2<T>& other)
        {
            this->substract(other);
            return *this;
        }

        vec2<T>& operator*=(const vec2<T>& other)
        {
            this->multiply(other);
            return *this;
        }

        vec2<T>& operator/=(const vec2<T>& other)
        {
            this->divide(other);
            return *this;
        }

        // Scalars
        vec2<T>& operator+=(T scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec2<T>& operator-=(T scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec2<T>& operator*=(T scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec2<T>& operator/=(T scalar)
        {
            this->divide(scalar);
            return *this;
        }

        friend bool operator==(const vec2<T>& left, const vec2<T>& right)
        {
            return left.x == right.x and left.y == right.y;
        }

        friend bool operator!=(const vec2<T>& left, const vec2<T>& right)
        {
            return !(left.x == right.x and left.y == right.y);
        }

        std::string to_string() const
        {
            return std::format("({}, {})", this->x, this->y);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec2<T>& vec) {
            os << vec.to_string();
            return os;
        }

    }; // vec2

    // vec3
    // Three-component vector
    template<typename T>
    struct vec3
    {
        // Data
        union
        {
            struct
            {
                T x;
                T y;
                T z;
            };
            struct
            {
                T r;
                T g;
                T b;
            };
            struct
            {
                T h;
                T s;
                T v;
            };
        };

        // Constructors
        vec3() : x(T{}), y(T{}), z(T{})
        {
        }

        vec3(T scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
        }

        vec3(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        // Operations
        vec3<T>& add(const vec3<T>& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        vec3<T>& substract(const vec3<T>& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        vec3<T>& multiply(const vec3<T>& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            return *this;
        }

        vec3<T>& divide(const vec3<T>& other)
        {
            this->x /= other.x;
            this->y /= other.y;
            this->z /= other.z;
            return *this;
        }

        // Operations with scalars
        vec3<T>& add(T scalar)
        {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            return *this;
        }

        vec3<T>& substract(T scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            return *this;
        }

        vec3<T>& multiply(T scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        vec3<T>& divide(T scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }

        float magnitude() const
        {
            float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
            return mag;
        }

        vec3<T>& normalize()
        {
            float mag = magnitude();
            if (mag > 0.0f) {
                float inv_mag = inverse(mag);
                this->x *= inv_mag;
                this->y *= inv_mag;
                this->z *= inv_mag;
            }

            return *this;
        }

        vec3<T> normalized() const
        {
            vec3<T> vec(this->x, this->y, this->z);
            vec.normalize();

            return vec;
        }

        float dot(const vec3<T>& other) const
        {
            float result = this->x * other.x + this->y * other.y + this->z * other.z;
            return result;
        }

        vec3<T>* value_ptr()
        {
            return &(*this);
        }

        // Operators
        friend vec3<T> operator+(vec3<T> left, const vec3<T>& right)
        {
            return left.add(right);
        }

        friend vec3<T> operator-(vec3<T> left, const vec3<T>& right)
        {
            return left.substract(right);
        }

        friend vec3<T> operator*(vec3<T> left, const vec3<T>& right)
        {
            return left.multiply(right);
        }

        friend vec3<T> operator/(vec3<T> left, const vec3<T>& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec3<T> operator+(vec3<T> left, T right)
        {
            return left.add(right);
        }

        friend vec3<T> operator-(vec3<T> left, T right)
        {
            return left.substract(right);
        }

        friend vec3<T> operator*(vec3<T> left, T right)
        {
            return left.multiply(right);
        }

        friend vec3<T> operator/(vec3<T> left, T right)
        {
            return left.divide(right);
        }

        vec3<T>& operator+=(const vec3<T>& other)
        {
            this->add(other);
            return *this;
        }

        vec3<T>& operator-=(const vec3<T>& other)
        {
            this->substract(other);
            return *this;
        }

        vec3<T>& operator*=(const vec3<T>& other)
        {
            this->multiply(other);
            return *this;
        }

        vec3<T>& operator/=(const vec3<T>& other)
        {
            this->divide(other);
            return *this;
        }

        // Scalars
        vec3<T>& operator+=(T scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec3<T>& operator-=(T scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec3<T>& operator*=(T scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec3<T>& operator/=(T scalar)
        {
            this->divide(scalar);
            return *this;
        }

        friend bool operator==(const vec3<T>& left, const vec3<T>& right)
        {
            return left.x == right.x and left.y == right.y && left.z == right.z;
        }

        friend bool operator!=(const vec3<T>& left, const vec3<T>& right)
        {
            return !(left.x == right.x and left.y == right.y && left.z == right.z);
        }

        std::string to_string() const
        {
            return std::format("({}, {}, {})", this->x, this->y, this->z);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& vec) {
            os << vec.to_string();
            return os;
        }

    }; // vec3

    // vec4
    // Four-component vector
    template<typename T>
    struct vec4
    {
        // Data
        union
        {
            struct
            {
                T x;
                T y;
                T z;
                T w;
            };
            struct
            {
                T r;
                T g;
                T b;
                T a;
            };
        };
        
        // Constructors
        vec4() : x(T{}), y(T{}), z(T{}), w(T{})
        {
        }

        vec4(T scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
            w = scalar;
        }

        vec4(T x, T y, T z, T w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        // Operations
        vec4<T>& add(const vec4<T>& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
            return *this;
        }

        vec4<T>& substract(const vec4<T>& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            this->w -= other.w;
            return *this;
        }

        vec4<T>& multiply(const vec4<T>& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            this->w *= other.w;
            return *this;
        }

        vec4<T>& divide(const vec4<T>& other)
        {
            this->x /= other.x;
            this->y /= other.y;
            this->z /= other.z;
            this->w /= other.w;
            return *this;
        }

        // Operations with scalars
        vec4<T>& add(T scalar)
        {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            this->w += scalar;
            return *this;
        }

        vec4<T>& substract(T scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            this->w -= scalar;
            return *this;
        }

        vec4<T>& multiply(T scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            this->w *= scalar;
            return *this;
        }

        vec4<T>& divide(T scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            this->w /= scalar;
            return *this;
        }

        float magnitude() const
        {
            float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
            return mag;
        }

        vec4<T>& normalize()
        {
            float mag = magnitude();
            if (mag > 0.0f) {
                float inv_mag = inverse(mag);
                this->x *= inv_mag;
                this->y *= inv_mag;
                this->z *= inv_mag;
                this->w *= inv_mag;
            }

            return *this;
        }

        vec4<T> normalized() const
        {
            vec4 vec(this->x, this->y, this->z, this->w);
            vec.normalize();

            return vec;
        }

        float dot(const vec4& other) const
        {
            float result = this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
            return result;
        }

        vec4<T>* value_ptr()
        {
            return &(*this);
        }

        // Operators
        friend vec4<T> operator+(vec4<T> left, const vec4<T>& right)
        {
            return left.add(right);
        }


        friend vec4<T> operator-(vec4<T> left, const vec4<T>& right)
        {
            return left.substract(right);
        }

        friend vec4<T> operator*(vec4<T> left, const vec4<T>& right)
        {
            return left.multiply(right);
        }

        friend vec4<T> operator/(vec4<T> left, const vec4<T>& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec4<T> operator+(vec4<T> left, T right)
        {
            return left.add(right);
        }


        friend vec4<T> operator-(vec4<T> left, T right)
        {
            return left.substract(right);
        }

        friend vec4<T> operator*(vec4<T> left, T right)
        {
            return left.multiply(right);
        }

        friend vec4<T> operator/(vec4<T> left, T right)
        {
            return left.divide(right);
        }

        vec4<T>& operator+=(const vec4<T>& other)
        {
            this->add(other);
            return *this;
        }

        vec4<T>& operator-=(const vec4<T>& other)
        {
            this->substract(other);
            return *this;
        }

        vec4<T>& operator*=(const vec4<T>& other)
        {
            this->multiply(other);
            return *this;
        }

        vec4<T>& operator/=(const vec4<T>& other)
        {
            this->divide(other);
            return *this;
        }

        // Scalars
        vec4<T>& operator+=(T scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec4<T>& operator-=(T scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec4<T>& operator*=(T scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec4<T>& operator/=(T scalar)
        {
            this->divide(scalar);
            return *this;
        }

        friend bool operator==(const vec4& left, const vec4& right)
        {
            return left.x == right.x and left.y == right.y && left.z == right.z && left.w == right.w;
        }

        friend bool operator!=(const vec4& left, const vec4& right)
        {
            return !(left.x == right.x and left.y == right.y && left.z == right.z && left.w == right.w);
        }

        std::string to_string() const
        {
            return std::format("({}, {}, {}, {})", this->x, this->y, this->z, this->w);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec4<T>& vec) {
            os << vec.to_string();
            return os;
        }

    }; // vec4

    // Vector general operation
    // Geometry

    struct circle
    {
        float radius = 1.0f;
        vec2<float> position = vec2(0.0f);
    };

    struct sphere
    {
        float radius = 1.0f;
        vec3<float> position = vec3(0.0f);
    };

    template<typename T>
    float distance(const vec2<T>& a, const vec2<T>& b)
    {
        GEM_LOG(a - b);
        return (a - b).magnitude();
    }

    template<typename T>
    float distance(const vec3<T>& a, const vec3<T>& b)
    {
        return (a - b).magnitude();
    }

    template<typename T>
    float distance(const vec4<T>& a, const vec4<T>& b)
    {
        return (a - b).magnitude();
    }

    template<typename T>
    bool point_in_circle(const vec2<T>& point, const circle& circle)
    {
        return distance(point, circle.position) <= circle.radius;
    }

    template<typename T>
    bool point_in_sphere(const vec3<T>& point, const sphere& sphere)
    {
        return distance(point, sphere.position) <= sphere.radius;
    }

    bool circle_in_circle(const circle& a, const circle& b)
    {
        return distance(a.position, b.position) <= a.radius + b.radius;
    }

    bool sphere_in_sphere(const sphere& a, const sphere& b)
    {
        return distance(a.position, b.position) <= a.radius + b.radius;
    }

    // Color conversions
    // TODO: Review (0-255 should be ivecs(ints)) -> implement ivec
    // TODO: Remake colors
#ifdef GEM_COLOR_CONV
    color3 rgb_to_normalized(const color3& color)
    {
        vec3 c(color);
        float conv = inverse(255.0f);
        c.r *= conv;
        c.g *= conv;
        c.b *= conv;
        return c;
    }

    color4 rgb_to_normalized(const color4& color)
    {
        vec4 c(color);
        float conv = inverse(255.0f);
        c.r *= conv;
        c.g *= conv;
        c.b *= conv;
        c.a *= conv;
        return c;
    }

    color3 normalized_to_rgb(const color3& color)
    {
        vec3 c(color);
        c.r *= 255.0f;
        c.g *= 255.0f;
        c.b *= 255.0f;
        return c;
    }

    color4 normalized_to_rgb(const color4& color)
    {
        vec4 c(color);
        c.r *= 255.0f;
        c.g *= 255.0f;
        c.b *= 255.0f;
        c.a *= 255.0f;
        return c;
    }

    color3 rgb_to_hsv(const color3& color)
    {
        // Convert RGB to [0, 1] range
        vec3 norm = rgb_to_normalized(color);

        // Find min and max components of RGB
        precision_type cmin = min(norm.r, norm.g, norm.b);
        precision_type cmax = max(norm.r, norm.g, norm.b);

        // Compute value (V) of HSV
        precision_type v = cmax;
        precision_type s = 0;
        precision_type h = 0;
        // Compute saturation (S) of HSV
        if (v == 0) {
            s = 0;
        } else {
            s = (v - cmin) / v;
        }

        // Compute hue (H) of HSV
        if (cmax == cmin) {
            h = 0;
        } else if (cmax == norm.r) {
            h = (norm.g - norm.b) / (cmax - cmin);
        } else if (cmax == norm.g) {
            h = 2 + (norm.b - norm.r) / (cmax - cmin);
        } else {
            h = 4 + (norm.r - norm.g) / (cmax - cmin);
        }

        h *= 60;
        if (h < 0) {
            h += 360;
        }

        return color3(h, s, v);
    }

    color3 hsv_to_rgb(const color3& color)
    {
        // From stackoverflow
        double      hh, p, q, t, ff;
        long        i;
        color3      out;

        if(color.s <= 0.0) {       // < is bogus, just shuts up warnings
            out.r = color.v;
            out.g = color.v;
            out.b = color.v;
            return out;
        }
        hh = color.h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = color.v * (1.0 - color.s);
        q = color.v * (1.0 - (color.s * ff));
        t = color.v * (1.0 - (color.s * (1.0 - ff)));

        switch(i) {
        case 0:
            out.r = color.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = color.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = color.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = color.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = color.v;
            break;
        case 5:
        default:
            out.r = color.v;
            out.g = p;
            out.b = q;
            break;
        }

        out = normalized_to_rgb(out);
        return out;
    }
#endif
    // vec2
    template<typename T>
    T dot(const vec2<T>& first, const vec2<T>& second)
    {
        T result = first.x * second.x + first.y * second.y;
        return result;
    }

    template<typename T>
    float angle(const vec2<T>& first, const vec2<T>& second)
    {
        float angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }

    // vec3
    template<typename T>
    T dot(const vec3<T>& first, const vec3<T>& second)
    {
        T result = first.x * second.x + first.y * second.y + first.z * second.z;
        return result;
    }

    template<typename T>
    float angle(const vec3<T>& first, const vec3<T>& second)
    {
        float angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }

    // vec4
    template<typename T>
    float dot(const vec4<T>& first, const vec4<T>& second)
    {
        float result = first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
        return result;
    }

    template<typename T>
    float angle(const vec4<T>& first, const vec4<T>& second)
    {
        float angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }

    // Matrices
    // mat4
    // 4x4 matrix
    struct mat4
    {
        // Data
        union
        {
            precision_type elements[4 * 4];
            // TEMP -> template
            vec4<float> columns[4];
        };

        mat4()
        {
            for (int32 i = 0; i < 4 * 4; i++)
                elements[i] = 0.0f;
        }

        mat4(precision_type diagonal)
        {
            // Initialize all elements to 0
            for (int32 i = 0; i < 4 * 4; i++)
                elements[i] = 0.0f;

            // Set the diagonal
            elements[0 + 0 * 4] = diagonal;
            elements[1 + 1 * 4] = diagonal;
            elements[2 + 2 * 4] = diagonal;
            elements[3 + 3 * 4] = diagonal;
        }

        static mat4 identiy()
        {
            return mat4(1.0f);
        }

        mat4& multiply(const mat4& other)
        {
            for (int32 y = 0; y < 4; y++)
            {
                for (int32 x = 0; x < 4; x++)
                {
                    float sum = 0.0f;
                    for (int32 e = 0; e < 4; e++)
                    {
                        sum += elements[x + e * 4] * other.elements[e + y * 4];
                    }
                    elements[x + y * 4] = sum;
                }
            }
    
            return *this;
        }

        precision_type determinant() const
        {
            precision_type a = elements[0], b = elements[1], c = elements[2], d = elements[3];
            precision_type e = elements[4], f = elements[5], g = elements[6], h = elements[7];
            precision_type i = elements[8], j = elements[9], k = elements[10], l = elements[11];
            precision_type m = elements[12], n = elements[13], o = elements[14], p = elements[15];

            precision_type det = 
                a * f * k * p + a * g * l * n + a * h * j * o
                - a * f * l * o - a * g * j * p - a * h * k * n
                - b * e * k * p - b * g * l * m - b * h * i * o
                + b * e * l * o + b * g * i * p + b * h * k * m
                + c * e * j * p + c * f * l * m + c * h * i * n
                - c * e * l * n - c * f * i * p - c * h * j * m
                - d * e * j * o - d * f * k * m - d * g * i * n
                + d * e * k * n + d * f * i * o + d * g * j * m;

            return det;
        }

        mat4& invert() // From sparky engine
        {
            float temp[16];

            temp[0] = elements[5] * elements[10] * elements[15] -
                elements[5] * elements[11] * elements[14] -
                elements[9] * elements[6] * elements[15] +
                elements[9] * elements[7] * elements[14] +
                elements[13] * elements[6] * elements[11] -
                elements[13] * elements[7] * elements[10];

            temp[4] = -elements[4] * elements[10] * elements[15] +
                elements[4] * elements[11] * elements[14] +
                elements[8] * elements[6] * elements[15] -
                elements[8] * elements[7] * elements[14] -
                elements[12] * elements[6] * elements[11] +
                elements[12] * elements[7] * elements[10];

            temp[8] = elements[4] * elements[9] * elements[15] -
                elements[4] * elements[11] * elements[13] -
                elements[8] * elements[5] * elements[15] +
                elements[8] * elements[7] * elements[13] +
                elements[12] * elements[5] * elements[11] -
                elements[12] * elements[7] * elements[9];

            temp[12] = -elements[4] * elements[9] * elements[14] +
                elements[4] * elements[10] * elements[13] +
                elements[8] * elements[5] * elements[14] -
                elements[8] * elements[6] * elements[13] -
                elements[12] * elements[5] * elements[10] +
                elements[12] * elements[6] * elements[9];

            temp[1] = -elements[1] * elements[10] * elements[15] +
                elements[1] * elements[11] * elements[14] +
                elements[9] * elements[2] * elements[15] -
                elements[9] * elements[3] * elements[14] -
                elements[13] * elements[2] * elements[11] +
                elements[13] * elements[3] * elements[10];

            temp[5] = elements[0] * elements[10] * elements[15] -
                elements[0] * elements[11] * elements[14] -
                elements[8] * elements[2] * elements[15] +
                elements[8] * elements[3] * elements[14] +
                elements[12] * elements[2] * elements[11] -
                elements[12] * elements[3] * elements[10];

            temp[9] = -elements[0] * elements[9] * elements[15] +
                elements[0] * elements[11] * elements[13] +
                elements[8] * elements[1] * elements[15] -
                elements[8] * elements[3] * elements[13] -
                elements[12] * elements[1] * elements[11] +
                elements[12] * elements[3] * elements[9];

            temp[13] = elements[0] * elements[9] * elements[14] -
                elements[0] * elements[10] * elements[13] -
                elements[8] * elements[1] * elements[14] +
                elements[8] * elements[2] * elements[13] +
                elements[12] * elements[1] * elements[10] -
                elements[12] * elements[2] * elements[9];

            temp[2] = elements[1] * elements[6] * elements[15] -
                elements[1] * elements[7] * elements[14] -
                elements[5] * elements[2] * elements[15] +
                elements[5] * elements[3] * elements[14] +
                elements[13] * elements[2] * elements[7] -
                elements[13] * elements[3] * elements[6];

            temp[6] = -elements[0] * elements[6] * elements[15] +
                elements[0] * elements[7] * elements[14] +
                elements[4] * elements[2] * elements[15] -
                elements[4] * elements[3] * elements[14] -
                elements[12] * elements[2] * elements[7] +
                elements[12] * elements[3] * elements[6];

            temp[10] = elements[0] * elements[5] * elements[15] -
                elements[0] * elements[7] * elements[13] -
                elements[4] * elements[1] * elements[15] +
                elements[4] * elements[3] * elements[13] +
                elements[12] * elements[1] * elements[7] -
                elements[12] * elements[3] * elements[5];

            temp[14] = -elements[0] * elements[5] * elements[14] +
                elements[0] * elements[6] * elements[13] +
                elements[4] * elements[1] * elements[14] -
                elements[4] * elements[2] * elements[13] -
                elements[12] * elements[1] * elements[6] +
                elements[12] * elements[2] * elements[5];

            temp[3] = -elements[1] * elements[6] * elements[11] +
                elements[1] * elements[7] * elements[10] +
                elements[5] * elements[2] * elements[11] -
                elements[5] * elements[3] * elements[10] -
                elements[9] * elements[2] * elements[7] +
                elements[9] * elements[3] * elements[6];

            temp[7] = elements[0] * elements[6] * elements[11] -
                elements[0] * elements[7] * elements[10] -
                elements[4] * elements[2] * elements[11] +
                elements[4] * elements[3] * elements[10] +
                elements[8] * elements[2] * elements[7] -
                elements[8] * elements[3] * elements[6];

            temp[11] = -elements[0] * elements[5] * elements[11] +
                elements[0] * elements[7] * elements[9] +
                elements[4] * elements[1] * elements[11] -
                elements[4] * elements[3] * elements[9] -
                elements[8] * elements[1] * elements[7] +
                elements[8] * elements[3] * elements[5];

            temp[15] = elements[0] * elements[5] * elements[10] -
                elements[0] * elements[6] * elements[9] -
                elements[4] * elements[1] * elements[10] +
                elements[4] * elements[2] * elements[9] +
                elements[8] * elements[1] * elements[6] -
                elements[8] * elements[2] * elements[5];

            float determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
            determinant = 1.0f / determinant;

            for (int32 i = 0; i < 4 * 4; i++)
                elements[i] = temp[i] * determinant;

            return *this;
        }

        mat4 inverse() const
        {
            mat4 mat = mat4::inverse(*this);
            return mat;
        }

        static mat4 inverse(const mat4& mat)
        {
            mat4 result = mat;
            result.invert();
            return result;
        }

        mat4& operator*(const mat4& other)
        {
            this->multiply(other);
            return *this;
        }

        mat4& operator*=(const mat4& other)
        {
            this->multiply(other);
            return *this;
        }

        // Templates
        static mat4 orthographic(precision_type left, precision_type right, precision_type bottom, precision_type top, precision_type near = -1.0f, precision_type far = 1.0f)
        {
            mat4 result(1.0f);
            result.elements[0 + 0 * 4] = 2 / (right - left);
            result.elements[1 + 1 * 4] = 2 / (top - bottom);
            result.elements[2 + 2 * 4] = -2 / (far - near);

            result.elements[3 + 0 * 4] = - (right + left) / (right - left);
            result.elements[3 + 1 * 4] = - (top + bottom) / (top - bottom);
            result.elements[3 + 2 * 4] = - (far + near) / (far - near);

            return result;
        }

        // FOV in degrees
        static mat4 perspective(precision_type fov, precision_type aspect_ratio, precision_type zNear, precision_type zFar)
        {
            precision_type a = aspect_ratio * tan(to_radians(fov * 0.5f));
            precision_type b = tan(to_radians(fov * 0.5f));

            precision_type c = (-zNear - zFar) / (zNear - zFar);
            precision_type d = (2 * zNear * zFar) / (zNear - zFar);

            mat4 result(0.0f);
            result.elements[0 + 0 * 4] = gem::inverse(a);
            result.elements[1 + 1 * 4] = gem::inverse(b);
            result.elements[2 + 2 * 4] = c;
            result.elements[3 + 2 * 4] = d;
            result.elements[2 + 3 * 4] = 1.0f;

            return result;
        }

        template<typename T>
        static mat4 translate(const vec3<T>& translation)
        {
            mat4 result(1.0f);
            result.elements[3 + 0 * 4] = translation.x;
            result.elements[3 + 1 * 4] = translation.y;
            result.elements[3 + 2 * 4] = translation.z;

            return result;
        }

        template<typename T>
        static mat4 rotation(const vec3<T>& axis, float angle)
        {
            mat4 result(1.0f);

            float r = to_radians(angle);
            float c = cos(r);
            float s = sin(r);
            float omc = 1.0f - c;

            float x = axis.x;
            float y = axis.y;
            float z = axis.z;

            result.elements[0 + 0 * 4] = x * x * omc + c;
            result.elements[0 + 1 * 4] = y * x * omc + z * s;
            result.elements[0 + 2 * 4] = x * z * omc - y * s;

            result.elements[1 + 0 * 4] = x * y * omc - z * s;
            result.elements[1 + 1 * 4] = y * y * omc + c;
            result.elements[1 + 2 * 4] = y * z * omc + x * s;

            result.elements[2 + 0 * 4] = x * z * omc + y * s;
            result.elements[2 + 1 * 4] = y * z * omc - x * s;
            result.elements[2 + 2 * 4] = z * z * omc + c;

            return result;
        }

        template<typename T>
        static mat4 scale(const vec3<T>& scale)
        {
            mat4 result(1.0f);
            result.elements[0 + 0 * 4] = scale.x;
            result.elements[1 + 1 * 4] = scale.y;
            result.elements[2 + 2 * 4] = scale.z;

            return result;
        }

        std::string to_string() const
        {
            return std::format("{}\n{}\n{}\n{}", columns[0].to_string(), columns[1].to_string(), columns[2].to_string(), columns[3].to_string());
        }

        friend std::ostream& operator<<(std::ostream& os, const mat4& mat)
        {
            os << mat.to_string();
            return os;
        }

    }; // mat4

    // Quaternions
    struct quaternion
    {
        precision_type x, y, z, w;
        
        quaternion()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 0.0f;
        }

        quaternion(precision_type x, precision_type y, precision_type z, precision_type w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        template<typename T>
        quaternion(const vec3<T>& axis, float angle)
        {
            // Calculate the sine and cosine of half the angle
            float sin_half_angle = sin(angle * 0.5f);
            float cos_half_angle = cos(angle * 0.5f);

            // Create a normalized quaternion from the axis of rotation and half-angle
            vec3<T> normalized_axis = axis.normalized();
            this->x = normalized_axis.x * sin_half_angle;
            this->y = normalized_axis.y * sin_half_angle;
            this->z = normalized_axis.z * sin_half_angle;
            this->w = cos_half_angle;
        }

        template<typename T>
        quaternion(const vec3<T>& euler_angles)
        {
            // Compute half angles
            float hx = euler_angles.x * 0.5f;
            float hy = euler_angles.y * 0.5f;
            float hz = euler_angles.z * 0.5f;

            // Compute sin and cos of half angles
            float cx = cos(hx);
            float cy = cos(hy);
            float cz = cos(hz);
            float sx = sin(hx);
            float sy = sin(hy);
            float sz = sin(hz);

            // Compute the quaternion components
            this->x = sx * cy * cz - cx * sy * sz;
            this->y = cx * sy * cz + sx * cy * sz;
            this->z = cx * cy * sz - sx * sy * cz;
            this->w = cx * cy * cz + sx * sy * sz;
        }

        template<typename T>
        static quaternion from_euler_angles(const vec3<T>& euler_angles)
        {
            // Compute half angles
            float hx = euler_angles.x * 0.5f;
            float hy = euler_angles.y * 0.5f;
            float hz = euler_angles.z * 0.5f;

            // Compute sin and cos of half angles
            float cx = cos(hx);
            float cy = cos(hy);
            float cz = cos(hz);
            float sx = sin(hx);
            float sy = sin(hy);
            float sz = sin(hz);

            quaternion q;
            // Compute the quaternion components
            q.x = sx * cy * cz - cx * sy * sz;
            q.y = cx * sy * cz + sx * cy * sz;
            q.z = cx * cy * sz - sx * sy * cz;
            q.w = cx * cy * cz + sx * sy * sz;
            return q;
        }

        static const quaternion RotationX(precision_type radians)
        {
            float angle = radians * 0.5f;
            return quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
        }

        static const quaternion RotationY(precision_type radians)
        {
            float angle = radians * 0.5f;
            return quaternion(0.0f, sin(angle), 0.0f, cos(angle));
        }

        static const quaternion RotationZ(precision_type radians)
        {
            float angle = radians * 0.5f;
            return quaternion(0.0f, 0.0f, sin(angle), cos(angle));
        }

        quaternion& add(const quaternion& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
            return *this;
        }

        quaternion& substract(const quaternion& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            this->w -= other.w;
            return *this;
        }

        quaternion& multiply(const quaternion& other)
        {
            this->x = x * other.x - y * other.y - z * other.z - w * other.w;
            this->y = y * other.x + x * other.y - w * other.z + z * other.w;
            this->z = z * other.x + w * other.y - x * other.z + y * other.w;
            this->w = w * other.x + z * other.y - y * other.z + x * other.w;

            return *this;
        }

        precision_type magnitude() const
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        // Normalize the quaternion
        quaternion& normalize()
        {
            precision_type mag = magnitude();
            if (mag > 0.0f)
            {
                precision_type inverse_magnitude = inverse(mag);
                x *= inverse_magnitude;
                y *= inverse_magnitude;
                z *= inverse_magnitude;
                w *= inverse_magnitude;
            }

            return *this;
        }

        quaternion normalized() const
        {
            precision_type mag = magnitude();
            quaternion q(this->x, this->y, this->z, this->w);
            q.normalize();

            return q;
        }

        quaternion& conjugate()
        {
            x = -x;
            y = -y;
            z = -z;

            return *this;
        }

        quaternion conjugated() const
        {
            return quaternion(-x, -y, -z, w);
        }

        mat4 to_mat4() const
        {
            // Normalize the quaternion first
            quaternion q = *this;
            q.normalize();

            // Extract the components of the quaternion
            float x = q.x;
            float y = q.y;
            float z = q.z;
            float w = q.w;

            // Compute the elements of the matrix
            float xx = x * x;
            float xy = x * y;
            float xz = x * z;
            float xw = x * w;
            float yy = y * y;
            float yz = y * z;
            float yw = y * w;
            float zz = z * z;
            float zw = z * w;

            // Construct the matrix
            mat4 mat(1.0f);
            mat.elements[0 + 0 * 4] = 1 - 2 * (yy + zz);
            mat.elements[0 + 1 * 4] = 2 * (xy - zw);
            mat.elements[0 + 2 * 4] = 2 * (xz + yw);
            mat.elements[1 + 0 * 4] = 2 * (xy + zw);
            mat.elements[1 + 1 * 4] = 1 - 2 * (xx + zz);
            mat.elements[1 + 2 * 4] = 2 * (yz - xw);
            mat.elements[2 + 0 * 4] = 2 * (xz - yw);
            mat.elements[2 + 1 * 4] = 2 * (yz + xw);
            mat.elements[2 + 2 * 4] = 1 - 2 * (xx + yy);

            return mat;
        }

        template<typename T>
        vec3<T> to_euler_angles() const 
        {
            vec3<T> euler;

            // roll (x-axis rotation)
            float sinr_cosp = 2.0f * (w * x + y * z);
            float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
            euler.x = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            float sinp = 2.0f * (w * y - z * x);
            if (std::abs(sinp) >= 1.0f) {
              euler.y = std::copysign(GEM_PI * 0.5f, sinp); // use 90 degrees if out of range
            } else {
                euler.y = std::asin(sinp);
            }

            // yaw (z-axis rotation)
            float siny_cosp = 2.0f * (w * z + x * y);
            float cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
            euler.z = std::atan2(siny_cosp, cosy_cosp);

            return euler;
        }

        // Operators
        friend quaternion operator+(quaternion left, const quaternion& right)
        {
            return left.add(right);
        }


        friend quaternion operator-(quaternion left, const quaternion& right)
        {
            return left.substract(right);
        }

        friend quaternion operator*(quaternion left, const quaternion& right)
        {
            return left.multiply(right);
        }

        std::string to_string() const
        {
            return std::format("({}, {}, {}, {})", this->x, this->y, this->z, this->w);
        }

        friend std::ostream& operator<<(std::ostream& os, const quaternion& quat)
        {
            os << quat.to_string();
            return os;
        }
    };

}

#endif // GEM_MATH_HPP
