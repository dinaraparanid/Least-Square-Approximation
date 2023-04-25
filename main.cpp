#include <random>
#include <sstream>

#include "gnuplot-cpp/gnuplot_i.hpp"
#include "agla/mtx/column_vector.hpp"

int main() {
	std::random_device random_device;
	std::mt19937 rng(random_device());
	std::uniform_real_distribution<double> double_generator(-10.0, 10.0);

	const auto rand_double = [&double_generator, &rng]() {
		return double_generator(rng);
	};

	const auto m = 10;

	agla::mtx::column_vector<double> b(m);
	std::vector<double> a_buf(m);

	for (std::size_t i = 0; i < m; ++i) {
		auto ti = rand_double(), bi = rand_double();
		a_buf[i] = ti;
		b.get_unchecked(i) = bi;
	}

	std::size_t n = 5;

	agla::mtx::matrix<double> a(m, std::vector<double>(n + 1, 1));

	for (std::size_t i = 1; i <= n; ++i)
		for (std::size_t q = 0; q < m; ++q)
			a.get_unchecked(q).get_unchecked(i) = std::pow(a_buf[q], i);

	std::puts("A:");
	std::cout << a;

	std::puts("B:");
	std::cout << b;

	const auto at = a.transposed();
	const auto at_a = agla::mtx::square_matrix<double>::from_matrix_unchecked(at.mul_unchecked(a));

	std::puts("A_T*A:");
	std::cout << at_a;

	const auto at_a_inv = at_a.inversed_unchecked();
	std::puts("(A_T*A)^-1:");
	std::cout << at_a_inv;

	const auto at_b = at.mul_unchecked(b);
	std::puts("A_T*b:");
	std::cout << at_b;

	const auto x = agla::mtx::column_vector<double>::from_matrix_unchecked(at_a_inv.mul_unchecked(at_b));
	std::puts("x~:");
	std::cout << x;

	std::stringstream equation;

	for (const auto& e : x) {
		static std::size_t i = 0;
		equation << e << " * x**" << i++ << " + ";
	}

	equation << '0';
	std::printf("Equation: %s", equation.str().c_str());

	std::vector<double> b_buf(b.size());
	std::copy(b.begin(), b.end(), b_buf.begin());

	Gnuplot()
		.reset_all()
		.savetops("output_graph")
		.set_title("Least Square Approximation")
		.set_grid()
		.set_style("lines")
		.set_xlabel("X")
		.set_ylabel("Y")
		.set_style("lines")
		.plot_equation(equation.str(), "f(x)")
		.set_style("points")
		.plot_xy(a_buf, b_buf)
		.showonscreen();

	return 0;
}
