// define GEM_DOUBLE to get double precission vecs and mats
// By default uses floats
// #define GEM_DOUBLE
// #define GEM_DISABLE_ALIASES
#include <gem_math.hpp>
#include <iostream>

// TODO: Make proper example
#define MATH_TEST 1

int main()
{
#if MATH_TEST

    std::cout << "PI ==============" << std::endl;
    {
        std::cout << gem::pi<float>() << std::endl;
    }

    std::cout << "VEC2 ==============" << std::endl;
    {
        // TODO: changing order affects result (when operating with different data types)
        // Operations between different vec templates may not result in the epected result
        gem::vec2<float> a(2.5f, 4.3f);

        std::cout << a << std::endl;
    }

    std::cout << "VEC3 ==============" << std::endl;

    {
        // vec3 test
        gem::vec3<float> a;
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

    std::cout << "MAT4 ==============" << std::endl;
    {
        // mat4 test
        gem::mat4 ortho_camera = gem::mat4<float>::orthographic(-1.6f, 1.6f, -0.9f, 0.9f);
        gem::mat4 perspective_camera = gem::mat4<float>::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

        gem::mat4 scale = gem::mat4<float>::scale({2.5f, 3.0f, 4.0f});
        std::cout << ortho_camera << std::endl << std::endl;

        gem::mat4 i = gem::mat4<float>::translate<float>({1.0f, 2.5f, -3.0f});
        std::cout << i << std::endl << std::endl;
        std::cout << i.inverse() << std::endl << std::endl;
        i.invert();
        std::cout << i << std::endl << std::endl;
    }

    std::cout << "GEOMETRY ==============" << std::endl;
    {
        gem::vec2<float> pointA(0.9f, 0.0f);
        gem::vec2<float> pointB(0.9f, 1.0f);
        std::cout << gem::point_in_circle(pointA, { 1.0f, { 0.0f, 0.0f } }) << std::endl;
    }

    std::cout << "QUATERNIONS ==============" << std::endl;
    {
        gem::vec3 euler_angles(0.0f, gem::to_radians(90.0f), 0.0f);
        gem::quaternion q = gem::quaternion<float>::from_euler_angles(euler_angles);
        std::cout << q << std::endl;

        gem::mat4 mat = q.to_mat4();
        std::cout << mat << std::endl;
    }
#endif

    std::cin.get();

    return 0;
}
