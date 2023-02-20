/*
    made by griush
*/

#ifndef GEM_H
#define GEM_H

// std
#include <cmath>
#include <string>
#include <ostream>

#ifdef GEM_DOUBLE
using precision_type = double;
#else
using precision_type = float;
#endif

#define GEM_DEG_TO_RAD 0.017453229252
#define GEM_RAD_TO_DEG 57.29577951

namespace gem {

    precision_type to_radians(precision_type degrees)
    {
        return degrees * GEM_DEG_TO_RAD;
    }

    precision_type to_degrees(precision_type radians)
    {
        return radians * GEM_RAD_TO_DEG;
    }

    // Vectors
    // vec2
    // Two-component vector
    struct vec2
    {
        // Data
        union
        {
            struct
            {
                precision_type x;
                precision_type y;
            };
        };
        
        // Constructors
        vec2()
        {
            x = 0.0f;
            y = 0.0f;
        }

        vec2(precision_type scalar)
        {
            x = scalar;
            y = scalar;
        }

        vec2(precision_type x, precision_type y)
        {
            this->x = x;
            this->y = y;
        }

        // Operations
        vec2& add(const vec2& other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        vec2& substract(const vec2& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        vec2& multiply(const vec2& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            return *this;
        }

        // If divide by 0, this stays the same (per component)
        // To avoid components == 'inf'
        vec2& divide(const vec2& other)
        {
            // Check if any of the 'other' components are 0
            if (other.x != 0.0f)
                this->x /= other.x;
            if (other.y != 0.0f)
                this->y /= other.y;
            return *this;
        }

        precision_type magnitude() const
        {
            precision_type mag = sqrt(this->x * this->x + this->y * this->y);
            return mag;
        }

        void normalize()
        {
            precision_type mag = magnitude();
            if (mag > 0.0f) {
                this->x /= mag;
                this->y /= mag;
            }
        }

        precision_type dot(const vec2& other) const
        {
            precision_type result = this->x * other.x + this->y * other.y;
            return result;
        }

        vec2* value_ptr()
        {
            return &(*this);
        }

        // Operators
        vec2& operator+(const vec2& other)
        {
            this->add(other);
            return *this;
        }

        vec2& operator-(const vec2& other)
        {
            this->substract(other);
            return *this;
        }

        vec2& operator*(const vec2& other)
        {
            this->multiply(other);
            return *this;
        }

        vec2& operator/(const vec2& other)
        {
            this->divide(other);
            return *this;
        }

        vec2& operator+=(const vec2& other)
        {
            this->add(other);
            return *this;
        }

        vec2& operator-=(const vec2& other)
        {
            this->substract(other);
            return *this;
        }

        vec2& operator*=(const vec2& other)
        {
            this->multiply(other);
            return *this;
        }

        vec2& operator/=(const vec2& other)
        {
            this->divide(other);
            return *this;
        }

        bool operator==(const vec2& other)
        {
            return this->x == other.x and this->y == other.y;
        }

        bool operator!=(const vec2& other)
        {
            return !(this->x == other.x and this->y == other.y);
        }

        std::string to_string() const
        {
            std::string s = "(";
            s += std::to_string(this->x);
            s += ", ";
            s += std::to_string(this->y);
            s += ")";
            return s;
        }

        friend std::ostream& operator<<(std::ostream& os, const vec2& vec) {
            os << "(" << vec.x << ", " << vec.y << ")";
            return os;
        }

    }; // vec2

    // vec3
    // Three-component vector
    struct vec3
    {
        // Data
        union
        {
            struct
            {
                precision_type x;
                precision_type y;
                precision_type z;
            };
            struct
            {
                precision_type r;
                precision_type g;
                precision_type b;
            };
        };
        
        // Constructors
        vec3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        vec3(precision_type scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
        }

        vec3(precision_type x, precision_type y, precision_type z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        // Operations
        vec3& add(const vec3& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        vec3& substract(const vec3& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        vec3& multiply(const vec3& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            return *this;
        }

        // If divide by 0, this stays the same (per component)
        // To avoid components == 'inf'
        vec3& divide(const vec3& other)
        {
            // Check if any of the 'other' components are 0
            if (other.x != 0.0f)
                this->x /= other.x;
            if (other.y != 0.0f)
                this->y /= other.y;
            if (other.z != 0.0f)
                this->z /= other.z;
            return *this;
        }

        precision_type magnitude() const
        {
            precision_type mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
            return mag;
        }

        void normalize()
        {
            precision_type mag = magnitude();
            if (mag > 0.0f) {
                this->x /= mag;
                this->y /= mag;
                this->z /= mag;
            }
        }

        precision_type dot(const vec3& other) const
        {
            precision_type result = this->x * other.x + this->y * other.y + this->z * other.z;
            return result;
        }

        vec3* value_ptr()
        {
            return &(*this);
        }

        // Operators
        vec3& operator+(const vec3& other)
        {
            this->add(other);
            return *this;
        }

        vec3& operator-(const vec3& other)
        {
            this->substract(other);
            return *this;
        }

        vec3& operator*(const vec3& other)
        {
            this->multiply(other);
            return *this;
        }

        vec3& operator/(const vec3& other)
        {
            this->divide(other);
            return *this;
        }

        vec3& operator+=(const vec3& other)
        {
            this->add(other);
            return *this;
        }

        vec3& operator-=(const vec3& other)
        {
            this->substract(other);
            return *this;
        }

        vec3& operator*=(const vec3& other)
        {
            this->multiply(other);
            return *this;
        }

        vec3& operator/=(const vec3& other)
        {
            this->divide(other);
            return *this;
        }

        bool operator==(const vec3& other)
        {
            return this->x == other.x and this->y == other.y && this->z == other.z;
        }

        bool operator!=(const vec3& other)
        {
            return !(this->x == other.x and this->y == other.y && this->z == other.z);
        }

        std::string to_string() const
        {
            std::string s = "(";
            s += std::to_string(this->x);
            s += ", ";
            s += std::to_string(this->y);
            s += ", ";
            s += std::to_string(this->z);
            s += ")";
            return s;
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& vec) {
            os << "(" << vec.x << ", " << vec.y << ", "<< vec.z << ")";
            return os;
        }

    }; // vec3

    // vec4
    // Four-component vector
    struct vec4
    {
        // Data
        union
        {
            struct
            {
                precision_type x;
                precision_type y;
                precision_type z;
                precision_type w;
            };
            struct
            {
                precision_type r;
                precision_type g;
                precision_type b;
                precision_type a;
            };
        };
        
        // Constructors
        vec4()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 0.0f;
        }

        vec4(precision_type scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
            w = scalar;
        }

        vec4(precision_type x, precision_type y, precision_type z, precision_type w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        // Operations
        vec4& add(const vec4& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
            return *this;
        }

        vec4& substract(const vec4& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            this->w -= other.w;
            return *this;
        }

        vec4& multiply(const vec4& other)
        {
            this->x *= other.x;
            this->y *= other.y;
            this->z *= other.z;
            this->w *= other.w;
            return *this;
        }

        // If divide by 0, this stays the same (per component)
        // To avoid components == 'inf'
        vec4& divide(const vec4& other)
        {
            // Check if any of the 'other' components are 0
            if (other.x != 0.0f)
                this->x /= other.x;
            if (other.y != 0.0f)
                this->y /= other.y;
            if (other.z != 0.0f)
                this->z /= other.z;
            if (other.w != 0.0f)
                this->w /= other.w;
            return *this;
        }

        precision_type magnitude() const
        {
            precision_type mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
            return mag;
        }

        void normalize()
        {
            precision_type mag = magnitude();
            if (mag > 0.0f) {
                this->x /= mag;
                this->y /= mag;
                this->z /= mag;
                this->w /= mag;
            }
        }

        precision_type dot(const vec4& other) const
        {
            precision_type result = this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
            return result;
        }

        vec4* value_ptr()
        {
            return &(*this);
        }

        // Operators
        vec4& operator+(const vec4& other)
        {
            this->add(other);
            return *this;
        }

        vec4& operator-(const vec4& other)
        {
            this->substract(other);
            return *this;
        }

        vec4& operator*(const vec4& other)
        {
            this->multiply(other);
            return *this;
        }

        vec4& operator/(const vec4& other)
        {
            this->divide(other);
            return *this;
        }

        vec4& operator+=(const vec4& other)
        {
            this->add(other);
            return *this;
        }

        vec4& operator-=(const vec4& other)
        {
            this->substract(other);
            return *this;
        }

        vec4& operator*=(const vec4& other)
        {
            this->multiply(other);
            return *this;
        }

        vec4& operator/=(const vec4& other)
        {
            this->divide(other);
            return *this;
        }

        bool operator==(const vec4& other)
        {
            return this->x == other.x and this->y == other.y && this->z == other.z && this->w == other.w;
        }

        bool operator!=(const vec4& other)
        {
            return !(this->x == other.x and this->y == other.y && this->z == other.z && this->w == other.w);
        }

        std::string to_string() const
        {
            std::string s = "(";
            s += std::to_string(this->x);
            s += ", ";
            s += std::to_string(this->y);
            s += ", ";
            s += std::to_string(this->z);
            s += ", ";
            s += std::to_string(this->w);
            s += ")";
            return s;
        }

        friend std::ostream& operator<<(std::ostream& os, const vec4& vec) {
            os << "(" << vec.x << ", " << vec.y << ", "<< vec.z << ", " << vec.w << ")";
            return os;
        }

    }; // vec4

    // Aliases
#ifndef GEM_DISABLE_ALIASES
    using pos = vec3;
    using color3 = vec3;
    using color4 = vec4;
#endif

    // Vector general operation
    // vec2
    precision_type dot(const vec2& first, const vec2& second)
    {
        precision_type result = first.x * second.x + first.y * second.y;
        return result;
    }

    void normalize(vec2& vec)
    {
        vec.normalize();
    }

    precision_type angle(const vec2& first, const vec2& second)
    {
        precision_type angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }

    // vec3
    precision_type dot(const vec3& first, const vec3& second)
    {
        precision_type result = first.x * second.x + first.y * second.y + first.z * second.z;
        return result;
    }

    void normalize(vec3& vec)
    {
        vec.normalize();
    }

    precision_type angle(const vec3& first, const vec3& second)
    {
        precision_type angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }

    // vec4
    precision_type dot(const vec4& first, const vec4& second)
    {
        precision_type result = first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
        return result;
    }

    void normalize(vec4& vec)
    {
        vec.normalize();
    }

    precision_type angle(const vec4& first, const vec4& second)
    {
        precision_type angleCos = dot(first, second) / (first.magnitude() * second.magnitude());
        return acos(angleCos);
    }
}

#endif // GEM_H
