// define GEM_DOUBLE to get double precission vecs and mats
// By default uses floats
// #define GEM_DOUBLE
// #define GEM_DISABLE_ALIASES
#include <gem_math.hpp>
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
        a += 2.0f;
        std::cout << a << std::endl;

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

        gem::vec2 f(1.0f);
        gem::vec2 s(0.0f);

        std::cout << f / s << std::endl;
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

    std::cout << "MAT4 ==============" << std::endl;
    {
        // mat4 test
        gem::mat4 ortho_camera = gem::mat4::orthographic(-1.6f, 1.6f, -0.9f, 0.9f);
        gem::mat4 perspective_camera = gem::mat4::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

        gem::mat4 scale = gem::mat4::scale({2.5f, 3.0f, 4.0f});
        std::cout << ortho_camera << std::endl;

        gem::mat4 i = gem::mat4::translate({1.0f, 2.5f, -3.0f});
        std::cout << i << std::endl;
        std::cout << gem::mat4::inverse(i) << std::endl;
        i.invert();
        std::cout << i << std::endl;
    }

    std::cout << "COLOR CONVERSIONS ==============" << std::endl;
    {
        gem::color3 red(255.0f, 130.0f, 0.0f);
        gem::color3 hsvRed = gem::rgb_to_hsv(red);
        std::cout << hsvRed << std::endl;
        red = gem::hsv_to_rgb(hsvRed);
        std::cout << red << std::endl;
    }

    std::cout << "GEOMETRY ==============" << std::endl;
    {
        gem::vec2 pointA(0.9f, 0.0f);
        gem::vec2 pointB(0.9f, 1.0f);
        std::cout << gem::point_in_circle(pointA, { 1.0f, { 0.0f, 0.0f } }) << std::endl;
    }

    std::cout << "QUATERNIONS ==============" << std::endl;
    {
        gem::vec3 euler_angles(0.0f, gem::to_radians(90.0f), 0.0f);
        gem::quaternion q(euler_angles);
        std::cout << "Quaternion components: (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl;

        gem::mat4 mat = q.to_mat4();
        std::cout << mat << std::endl;
    }

    std::cin.get();

    return 0;
}
