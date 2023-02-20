// define GEM_DOUBLE to get double precission vecs and mats
// By default uses floats
// #define GEM_DOUBLE
// #define GEM_DISABLE_ALIASES
#include <gem.hpp>
#include <iostream>

// TODO: Make proper example

int main()
{
    std::cout << "VEC2 ==============" << std::endl;
    {
        // vec2 test
        gem::vec2 a;
        gem::vec2 b(1.0f);
        gem::vec2 c(2.0f, 1.5f);

        a = b + c - gem::vec2(2.0f, -5.0f);
        a += gem::vec2(1.0f, -5.0f);

        // vec2::magnitude
        std::cout << a.magnitude() << std::endl;
        gem::normalize(a);
        std::cout << a.magnitude() << std::endl;

        // Two alternatives for dot products
        std::cout << a.dot(b) << std::endl;
        std::cout << gem::dot(a, b) << std::endl;

        std::cout << a << " " << b << " " << c << std::endl;

        gem::vec2 horz(1.0f, 0.0f);
        gem::vec2 vert(0.0f, 1.0f);
        std::cout << gem::to_degrees(gem::angle(horz, vert)) << std::endl;

        if (a != b)
        {
            std::cout << "a and b are different" << std::endl;
        }
        else
        {
            std::cout << "a and b are equal" << std::endl;
        }

        gem::vec2* a_ptr = a.value_ptr();
        a_ptr->add(b);
        std::cout << a_ptr->to_string() << std::endl;
    }

    std::cout << "VEC3 ==============" << std::endl;

    {
        // vec3 test
        gem::vec3 a;
        gem::vec3 b(1.0f);
        gem::vec3 c(2.0f, 1.5f, 4.25f);

        a = b + c - gem::vec3(2.0f, -5.0f, 1.0f);
        a += gem::vec3(1.0f, -5.0f, 3.0f);

        // vec3::magnitude
        std::cout << a.magnitude() << std::endl;

        // Two alternatives for dot products
        std::cout << a.dot(b) << std::endl;
        std::cout << gem::dot(a, b) << std::endl;

        std::cout << a << " " << b << " " << c << std::endl;
    }

    {
        // mat4 test
        gem::mat4 ortho_camera = gem::mat4::orthographic(-1.6f, 1.6f, -0.9f, 0.9f);
        gem::mat4 perspective_camera = gem::mat4::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    }

    return 0;
}