/*
    made by griush
*/

#ifndef GEM_H
#define GEM_H

// std
#include <cmath>
#include <string>
#include <ostream>

// TODO: Review this, not all types should be precision_type 
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

    precision_type inverse(precision_type val)
    {
        return 1 / val;
    }

    precision_type max(precision_type a, precision_type b)
    {
        return a > b ? a : b;
    }

    precision_type min(precision_type a, precision_type b)
    {
        return a < b ? a : b;
    }

    precision_type clamp(precision_type val, precision_type min, precision_type max)
    {
        return min(max(val, min), max);
    }

    // Vectors
    // TODO: vector size
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

    // Matrices
    // TODO: matrix size
    // mat4
    // 4x4 matrix
    struct mat4
    {
        // Data
        union
        {
            precision_type elements[4 * 4];
            vec4 columns[4];
        };

        mat4()
        {
            for (int i = 0; i < 4 * 4; i++)
                elements[i] = 0.0f;
        }

        mat4(precision_type diagonal)
        {
            // Initialize all elements to 0
            for (int i = 0; i < 4 * 4; i++)
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
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    float sum = 0.0f;
                    for (int e = 0; e < 4; e++)
                    {
                        sum += elements[x + e * 4] * other.elements[e + y * 4];
                    }
                    elements[x + y * 4] = sum;
                }
            }
    
            return *this;
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
            result.elements[0 + 0 * 4] = inverse(a);
            result.elements[1 + 1 * 4] = inverse(b);
            result.elements[2 + 2 * 4] = c;
            result.elements[3 + 2 * 4] = d;
            result.elements[2 + 3 * 4] = 1.0f;

            return result;
        }

        static mat4 translate(const vec3& translation)
        {
            mat4 result(1.0f);
            result.elements[3 + 0 * 4] = translation.x;
            result.elements[3 + 1 * 4] = translation.y;
            result.elements[3 + 2 * 4] = translation.z;

            return result;
        }

        static mat4 rotation(const vec3& axis, precision_type angle)
        {
            mat4 result(1.0f);

            float r = toRadians(angle);
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

        static mat4 scale(const vec3& scale)
        {
            mat4 result(1.0f);
            result.elements[0 + 0 * 4] = scale.x;
            result.elements[1 + 1 * 4] = scale.y;
            result.elements[2 + 2 * 4] = scale.z;

            return result;
        }

    }; // mat4
}

#endif // GEM_H
