#ifndef PREDATOR_PREY_HPP
#define PREDATOR_PREY_HPP

#include <cmath>

namespace predator_prey {
	constexpr inline long double k(
		const long double time,
		const long double a1,
		const long double b1,
		const long double a2,
		const long double b2,
		const long double v0,
		const long double k0
	) noexcept {
		return v0 * (std::sqrt(a1) * b2 / (b1 * std::sqrt(a2))) * std::sin(std::sqrt(a1 * a2) * time)
			   + k0 * std::cos(std::sqrt(a1 * a2) * time);
	}

	constexpr inline long double K(
		const long double time,
		const long double a1,
		const long double b1,
		const long double a2,
		const long double b2,
		const long double v0,
		const long double k0
	) noexcept { return k(time, a1, b1, a2, b2, v0, k0) + a1 / b1; }

	constexpr inline long double v(
		const long double time,
		const long double a1,
		const long double b1,
		const long double a2,
		const long double b2,
		const long double v0,
		const long double k0
	) noexcept {
		return v0 * std::cos(std::sqrt(a1 * a2) * time) -
			   k0 * (std::sqrt(a2) * b1 / (b2 * std::sqrt(a1))) * std::sin(std::sqrt(a1 * a2) * time);
	}

	constexpr inline long double V(
		const long double time,
		const long double a1,
		const long double b1,
		const long double a2,
		const long double b2,
		const long double v0,
		const long double k0
	) noexcept { return v(time, a1, b1, a2, b2, v0, k0) + a2 / b2; }
}

#endif // PREDATOR_PREY_HPP
