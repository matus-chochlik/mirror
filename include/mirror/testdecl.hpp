/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TESTDECL_HPP
#define MIRROR_TESTDECL_HPP

namespace test {

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

    auto apex() const noexcept -> const point& {
        return _apex;
    }

private:
    triangle _base;
    point _apex;
};

} // namespace test

#endif // MIRROR_TESTDECL_HPP

