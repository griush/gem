/*
    made by griush
*/

#ifndef GEM_HPP
#define GEM_HPP

// std
#include <cmath>
#include <string>
#include <sstream>
#include <ostream>
#include <format>

#define GEM_DEBUG 0

#if GEM_DEBUG
#include <iostream>
#define GEM_LOG(x) std::cout << x << std::endl;
#else
#define GEM_LOG(x)
#endif

#define GEM_DEG_TO_RAD 0.017453229252
#define GEM_RAD_TO_DEG 57.29577951

namespace gem {
    // snake_case for every name

    // TODO: Review this, not all types should be precision_type 
#ifdef GEM_DOUBLE
    using precision_type = double;
#else
    using precision_type = float;
#endif

    // General functions
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
            // TODO: Reniew zero division scenario
            // Check if any of the 'other' components are 0
            if (other.x != 0.0f)
                this->x /= other.x;
            if (other.y != 0.0f)
                this->y /= other.y;
            return *this;
        }

        // Operations with scalars
        vec2& add(precision_type scalar)
        {
            this->x += scalar;
            this->y += scalar;
            return *this;
        }

        vec2& substract(precision_type scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            return *this;
        }

        vec2& multiply(precision_type scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        vec2& divide(precision_type scalar)
        {
            // TODO: Reniew zero division scenario
            if (scalar == 0.0f)
                GEM_LOG("Can't divide by zero!");

            this->x /= scalar;
            this->y /= scalar;
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
        friend vec2 operator+(vec2 left, const vec2& right)
        {
            return left.add(right);
        }

        friend vec2 operator-(vec2 left, const vec2& right)
        {
            return left.substract(right);
        }

        friend vec2 operator*(vec2 left, const vec2& right)
        {
            return left.multiply(right);
        }

        friend vec2 operator/(vec2 left, const vec2& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec2 operator+(vec2 left, precision_type right)
        {
            return left.add(right);
        }

        friend vec2 operator-(vec2 left, precision_type right)
        {
            return left.substract(right);
        }

        friend vec2 operator*(vec2 left, precision_type right)
        {
            return left.multiply(right);
        }

        friend vec2 operator/(vec2 left, precision_type right)
        {
            return left.divide(right);
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

        // Scalars
        vec2& operator+=(precision_type scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec2& operator-=(precision_type scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec2& operator*=(precision_type scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec2& operator/=(precision_type scalar)
        {
            this->divide(scalar);
            return *this;
        }

        friend bool operator==(const vec2& left, const vec2& right)
        {
            return left.x == right.x and left.y == right.y;
        }

        friend bool operator!=(const vec2& left, const vec2& right)
        {
            return !(left.x == right.x and left.y == right.y);
        }

        std::string to_string() const
        {
            return std::format("({}, {})", this->x, this->y);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec2& vec) {
            os << vec.to_string();
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
            struct
            {
                precision_type h;
                precision_type s;
                precision_type v;
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

        // Operations with scalars
        vec3& add(precision_type scalar)
        {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            return *this;
        }

        vec3& substract(precision_type scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            return *this;
        }

        vec3& multiply(precision_type scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        vec3& divide(precision_type scalar)
        {
            // TODO: Reniew zero division scenario
            if (scalar == 0.0f)
                GEM_LOG("Can't divide by zero!");

            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
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
        friend vec3 operator+(vec3 left, const vec3& right)
        {
            return left.add(right);
        }

        friend vec3 operator-(vec3 left, const vec3& right)
        {
            return left.substract(right);
        }

        friend vec3 operator*(vec3 left, const vec3& right)
        {
            return left.multiply(right);
        }

        friend vec3 operator/(vec3 left, const vec3& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec3 operator+(vec3 left, precision_type right)
        {
            return left.add(right);
        }

        friend vec3 operator-(vec3 left, precision_type right)
        {
            return left.substract(right);
        }

        friend vec3 operator*(vec3 left, precision_type right)
        {
            return left.multiply(right);
        }

        friend vec3 operator/(vec3 left, precision_type right)
        {
            return left.divide(right);
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

        // Scalars
        vec3& operator+=(precision_type scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec3& operator-=(precision_type scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec3& operator*=(precision_type scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec3& operator/=(precision_type scalar)
        {
            this->divide(scalar);
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
            return std::format("({}, {}, {})", this->x, this->y, this->z);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec3& vec) {
            os << vec.to_string();
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

        // Operations with scalars
        vec4& add(precision_type scalar)
        {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            this->w += scalar;
            return *this;
        }

        vec4& substract(precision_type scalar)
        {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            this->w -= scalar;
            return *this;
        }

        vec4& multiply(precision_type scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            this->w *= scalar;
            return *this;
        }

        vec4& divide(precision_type scalar)
        {
            // TODO: Reniew zero division scenario
            if (scalar == 0.0f)
                GEM_LOG("Can't divide by zero!");

            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            this->w /= scalar;
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
        friend vec4 operator+(vec4 left, const vec4& right)
        {
            return left.add(right);
        }


        friend vec4 operator-(vec4 left, const vec4& right)
        {
            return left.substract(right);
        }

        friend vec4 operator*(vec4 left, const vec4& right)
        {
            return left.multiply(right);
        }

        friend vec4 operator/(vec4 left, const vec4& right)
        {
            return left.divide(right);
        }

        // Operators with scalars
        friend vec4 operator+(vec4 left, precision_type right)
        {
            return left.add(right);
        }


        friend vec4 operator-(vec4 left, precision_type right)
        {
            return left.substract(right);
        }

        friend vec4 operator*(vec4 left, precision_type right)
        {
            return left.multiply(right);
        }

        friend vec4 operator/(vec4 left, precision_type right)
        {
            return left.divide(right);
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

        // Scalars
        vec4& operator+=(precision_type scalar)
        {
            this->add(scalar);
            return *this;
        }

        vec4& operator-=(precision_type scalar)
        {
            this->substract(scalar);
            return *this;
        }

        vec4& operator*=(precision_type scalar)
        {
            this->multiply(scalar);
            return *this;
        }

        vec4& operator/=(precision_type scalar)
        {
            this->divide(scalar);
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
            return std::format("({}, {}, {}, {})", this->x, this->y, this->z, this->w);
        }

        friend std::ostream& operator<<(std::ostream& os, const vec4& vec) {
            os << vec.to_string();
            return os;
        }

    }; // vec4

    // Aliases
#ifndef GEM_DISABLE_ALIASES
    using color3 = vec3;
    using color4 = vec4;
#endif

    // Vector general operation
    // Geometry

    struct circle
    {
        float radius = 1.0f;
        vec2 position = vec2(0.0f);
    };

    struct sphere
    {
        float radius = 1.0f;
        vec3 position = vec3(0.0f);
    };

    precision_type distance(const vec2& a, const vec2& b)
    {
        GEM_LOG(a - b);
        return (a - b).magnitude();
    }

    precision_type distance(const vec3& a, const vec3& b)
    {
        return (a - b).magnitude();
    }

    bool point_in_circle(const vec2& point, const circle& circle)
    {
        return distance(point, circle.position) <= circle.radius;
    }

    bool point_in_sphere(const vec3& point, const sphere& sphere)
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
    color3 rgb_to_normalized(const color3& color)
    {
        vec3 c(color);
        c.r /= 255.0f;
        c.g /= 255.0f;
        c.b /= 255.0f;
        return c;
    }

    color4 rgb_to_normalized(const color4& color)
    {
        vec4 c(color);
        c.r /= 255.0f;
        c.g /= 255.0f;
        c.b /= 255.0f;
        c.a /= 255.0f;
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

            for (int i = 0; i < 4 * 4; i++)
                elements[i] = temp[i] * determinant;

            return *this;
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

        static mat4 scale(const vec3& scale)
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
            return std::string();
        }

        friend std::ostream& operator<<(std::ostream& os, const mat4& mat)
        {
            os << mat.to_string();
            return os;
        }

    }; // mat4

}

#endif // GEM_HPP
