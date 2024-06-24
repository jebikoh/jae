#pragma once

#include "./assert.hpp"
#include "./constants.hpp"
#include "./numerical.hpp"
#include <cmath>
#include <algorithm>

namespace jtx {
    template<typename T, typename U, typename V>
    constexpr
    std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U> && std::is_arithmetic_v<V>, T>
    clamp(T val, U lo, V hi) {
        if (val < lo) return T(lo);
        else if (val > hi) return T(hi);
        else return val;
    }

    inline float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    inline float clampAsin(float theta) {
        ASSERT(theta >= -1.0001f && theta <= 1.0001f);
        return std::asin(std::clamp(theta, -1.0f, 1.0f));
    }

    inline float clampAcos(float theta) {
        ASSERT(theta >= -1.0001f && theta <= 1.0001f);
        return std::acos(std::clamp(theta, -1.0f, 1.0f));
    }

    inline double clampAsin(double theta) {
        ASSERT(theta >= -1.0001f && theta <= 1.0001);
        return std::asin(std::clamp(theta, -1.0, 1.0));
    }

    inline double clampAcos(double theta) {
        ASSERT(theta >= -1.0001 && theta <= 1.0001);
        return std::acos(std::clamp(theta, -1.0, 1.0));
    }

    inline float radians(float deg) {
        return deg * PI_F / 180.0f;
    }

    inline float degrees(float rad) {
        return rad * 180.0f / PI_F;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline
    T
    fma(T a, T b, T c) {
        return a * b + c;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_floating_point_v<T>, T>
    dop(T a, T b, T c, T d) {
        auto cd = c * d;
        auto alpha = jtx::fma(a, b, -cd);
        auto beta = jtx::fma(-c, d, cd);
        return alpha + beta;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_integral_v<T>, T>
    dop(T a, T b, T c, T d) {
        return a * b - c * d;
    }

    JTX_NUM_ONLY_T
    inline
    T sqrt(T v) {
        return std::sqrt(std::max(0.0f, v));
    }

    template<typename T, typename C, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<C>>>
    inline
    constexpr T evalPolynomial(T t, C c) {
        return c;
    }

    template<typename T, typename C, typename... Coeffs,
            typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<C>>>
    inline
    constexpr T evalPolynomial(T t, C c, Coeffs... coeffs) {
        return jtx::fma(t, evalPolynomial(t, coeffs...), c);
    }
}