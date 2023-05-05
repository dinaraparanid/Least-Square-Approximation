#include <random>
#include <string>
#include <algorithm>

#include "gnuplot-cpp/gnuplot_i.hpp"
#include "agla/predator_prey.hpp"

int main() {
	std::random_device random_device;
	std::mt19937 rng(random_device());
	std::uniform_int_distribution<std::size_t> int_generator(20, 30);
	std::uniform_real_distribution<long double> double_generator(0.5, 1.0);

	const auto rand_int = [&int_generator, &rng]() {
		return int_generator(rng);
	};

	const auto rand_double = [&double_generator, &rng]() {
		return double_generator(rng);
	};

	const auto victims_num = rand_int();
	const auto killers_num = rand_int();

	const auto a1 = rand_double();
	const auto b1 = rand_double();
	const auto a2 = rand_double();
	const auto b2 = rand_double();

	const auto tl = rand_int();
	const auto points = rand_int();

	const auto time_step = tl / points;
	std::vector<long double> times(points + 1, 0);

	for (std::size_t i = 1; i <= points; ++i)
		times[i] = time_step * i;

	const long double k0 = killers_num - a1 / b1;
	const long double v0 = victims_num - a2 / b2;

	std::vector<long double> victims_coefficients(points + 1);

	for (std::size_t i = 0; i <= points; ++i)
		victims_coefficients[i] = predator_prey::V(times[i], a1, b1, a2, b2, v0, k0);

	std::vector<long double> killers_coefficients(points + 1);

	for (std::size_t i = 0; i <= points; ++i)
		killers_coefficients[i] = predator_prey::K(times[i], a1, b1, a2, b2, v0, k0);

	std::puts("Time | V(T) | K(T)");

	for (std::size_t i = 0; i <= points; ++i)
		std::printf("%.2Lf %.2Lf %.2Lf\n", times[i], victims_coefficients[i], killers_coefficients[i]);

	char v_eq_buf[1000]; std::sprintf(
		v_eq_buf,
			"%Lf * cos(sqrt(%Lf * %Lf) * x) - %Lf * (sqrt(%Lf) * %Lf / (%Lf * sqrt(%Lf))) * sin(sqrt(%Lf * %Lf) * x) + %Lf / %Lf",
		v0, a1, a2, k0, a2, b1, b2, a1, a1, a2, a2, b2
	);

	const std::string v_equation(v_eq_buf);
	std::printf("Victims Equation: %s\n", v_eq_buf);

	char k_eq_buf[1000]; std::sprintf(
		k_eq_buf,
		"%Lf * (sqrt(%Lf) * %Lf / (%Lf * sqrt(%Lf))) * sin(sqrt(%Lf * %Lf) * x) + %Lf * cos(sqrt(%Lf * %Lf) * x) + %Lf / %Lf",
		v0, a1, b2, b1, a2, a1, a2, k0, a1, a2, a1, b1
	);

	const std::string k_equation(k_eq_buf);
	std::printf("Killers Equation: %s\n", k_eq_buf);

	Gnuplot plot;

	std::vector<long double> y_coordinates((points + 1) * 2);
	std::copy(victims_coefficients.begin(), victims_coefficients.end(), y_coordinates.begin());
	std::copy(killers_coefficients.begin(), killers_coefficients.end(), y_coordinates.begin() + (points + 1));

	plot
		.savetops("victims and killers")
		.set_title("Victims")
		.set_grid()
		.set_style("lines")
		.set_xlabel("time")
		.set_ylabel("victims/killers")
		.set_style("points")
		.plot_xy(times, victims_coefficients)
		.plot_xy(times, killers_coefficients)
		.set_style("lines")
		.plot_equation(v_equation, "v(t)")
		.plot_equation(k_equation, "k(t)")
		.showonscreen();

	// How to construct the equation
	//
	// x1^2 / a^2 + y1^2 / b^2 = 1
	// x2^2 / a^2 + y2^2 / b^2 = 1
	//
	// x1^2 * b^2 + y1^2 * a^2 = (ab)^2
	// x2^2 * b^2 + y2^2 * a^2 = (ab)^2
	//
	// (x1^2 - x2^2) * b^2 = (y2^2 - y1^2) * a^2
	// b^2 = (y2^2 - y1^2) * a^2 / (x1^2 - x2^2)
	//
	// b = sqrt((y2^2 - y1^2) * a^2 / (x1^2 - x2^2))
	//
	// x1^2 / a^2 + y1^2 / (y2^2 - y1^2) / a^2 * (x1^2 - x2^2) = 1
	// x1^2 + y1^2 * (x1^2 - x2^2) / (y2^2 - y1^2) = a^2
	//
	// a = sqrt(x1^2 + y1^2 * (x1^2 - x2^2) / (y2^2 - y1^2))
	//
	// y = sqrt((1 - x**2 / a**2) * b**2)

	const auto x1 = victims_coefficients[0];
	const auto y1 = killers_coefficients[0];

	const auto x2 = victims_coefficients[1];
	const auto y2 = killers_coefficients[1];

	const auto a = std::sqrt(x1 * x1 + y1 * y1 * (x1 * x1 - x2 * x2) / (y2 * y2 - y1 * y1));
	const auto b = std::sqrt((y2 * y2 - y1 * y1) * a * a / (x1 * x1 - x2 * x2));

	plot
		.reset_all()
		.savetops("killers_to_victims")
		.set_title("Killers to Victims")
		.set_grid()
		.set_style("points")
		.set_xlabel("victims")
		.set_ylabel("killers");

	std::stringstream eq;
	eq << "plot \"<( echo 0 0 " << a << " " << b << " 0 )\" w ellipses title \"k(v)\"";
	plot << eq.str();

	return 0;
}
