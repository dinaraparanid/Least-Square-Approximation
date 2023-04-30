#include <random>
#include <string>
#include <algorithm>

#include "gnuplot-cpp/gnuplot_i.hpp"
#include "agla/predator_prey.hpp"

int main() {
	std::random_device random_device;
	std::mt19937 rng(random_device());
	std::uniform_int_distribution<std::size_t> int_generator(20, 50);
	std::uniform_real_distribution<long double> double_generator(0.1, 1.0);

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

	std::puts("t:");

	for (const auto& t : times)
		std::printf("%Lf ", t);

	std::putchar('\n');

	const long double k0 = killers_num - a1 / b1;
	const long double v0 = victims_num - a2 / b2;

	std::vector<long double> victims_coefficients(points + 1);

	for (std::size_t i = 0; i <= points; ++i)
		victims_coefficients[i] = predator_prey::V(times[i], a1, b1, a2, b2, v0, k0);

	std::puts("v:");

	for (const auto& v : victims_coefficients)
		std::printf("%Lf ", v);

	std::putchar('\n');

	std::vector<long double> killers_coefficients(points + 1);

	for (std::size_t i = 0; i <= points; ++i)
		killers_coefficients[i] = predator_prey::K(times[i], a1, b1, a2, b2, v0, k0);

	std::puts("k:");

	for (const auto& v : killers_coefficients)
		std::printf("%Lf ", v);


	std::putchar('\n');

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

	const auto min_v = std::min_element(victims_coefficients.begin(), victims_coefficients.end());
	const auto max_v = std::max_element(victims_coefficients.begin(), victims_coefficients.end());

	plot
		.savetops("victims")
		.set_title("Victims")
		.set_grid()
		.set_style("lines")
		.set_xlabel("time")
		.set_ylabel("victims")
		.set_style("points")
		.set_xrange(0, tl)
		.set_yrange(*min_v, *max_v)
		.plot_xy(times, victims_coefficients)
		.set_style("lines")
		.plot_equation(v_equation, "v(t)")
		.showonscreen();

	plot
		.reset_all()
		.savetops("killers")
		.set_title("Killers")
		.set_grid()
		.set_style("lines")
		.set_xlabel("time")
		.set_ylabel("killers")
		.set_style("points")
		.plot_xy(times, killers_coefficients)
		.set_style("lines")
		.plot_equation(k_equation, "k(t)")
		.showonscreen();

	return 0;
}
