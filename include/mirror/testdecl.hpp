/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TESTDECL_HPP
#define MIRROR_TESTDECL_HPP

#include <cmath>

namespace test {

class vector {
public:
    vector() noexcept = default;

    vector(float v) noexcept
      : _x{v}
      , _y{v}
      , _z{v} {}

    vector(float x, float y, float z) noexcept
      : _x{x}
      , _y{y}
      , _z{z} {}

    auto x() const noexcept {
        return _x;
    }

    auto y() const noexcept {
        return _y;
    }

    auto z() const noexcept {
        return _z;
    }

    friend auto dot(const vector& a, const vector& b) noexcept -> float {
        return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
    }

    friend auto cross(const vector& a, const vector& b) noexcept -> vector {
        return vector{
          a.y() * b.z() - a.z() * b.y(),
          a.z() * b.x() - a.x() * b.z(),
          a.x() * b.y() - a.y() * b.x()};
    }

    auto length() const noexcept {
        return std::sqrt(dot(*this, *this));
    }

private:
    float _x{0.F};
    float _y{0.F};
    float _z{0.F};
};

class point {
public:
    point() noexcept = default;

    point(float v) noexcept
      : _x{v}
      , _y{v}
      , _z{v} {}

    point(float x, float y, float z) noexcept
      : _x{x}
      , _y{y}
      , _z{z} {}

    auto x() const noexcept {
        return _x;
    }

    auto y() const noexcept {
        return _y;
    }

    auto z() const noexcept {
        return _z;
    }

    friend auto operator-(const point& a, const point& b) noexcept {
        return vector(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
    }

    auto direction() const noexcept {
        return *this - point{0.F};
    }

private:
    float _x{0.F};
    float _y{0.F};
    float _z{0.F};
};

class triangle {
public:
    triangle() noexcept = default;

    triangle(const point& a, const point& b, const point& c) noexcept
      : _a{a}
      , _b{b}
      , _c{c} {}

    auto a() const noexcept -> const point& {
        return _a;
    }

    auto b() const noexcept -> const point& {
        return _b;
    }

    auto c() const noexcept -> const point& {
        return _c;
    }

    auto area() const noexcept -> float {
        return cross(b() - a(), c() - a()).length() * 0.5F;
    }

private:
    point _a;
    point _b;
    point _c;
};

class tetrahedron {
public:
    tetrahedron() noexcept = default;
    tetrahedron(const triangle& base, const point& apex) noexcept
      : _base{base}
      , _apex{apex} {}

    auto base() const noexcept -> const triangle& {
        return _base;
    }

    auto a() const noexcept -> const point& {
        return _base.a();
    }

    auto b() const noexcept -> const point& {
        return _base.b();
    }

    auto c() const noexcept -> const point& {
        return _base.c();
    }

    auto d() const noexcept -> const point& {
        return _apex;
    }

    auto apex() const noexcept -> const point& {
        return _apex;
    }

    auto volume() const noexcept -> float {
        return std::fabs(dot(a() - d(), cross(b() - d(), c() - d()))) / 6.F;
    }

private:
    triangle _base;
    point _apex;
};

} // namespace test

#endif // MIRROR_TESTDECL_HPP

