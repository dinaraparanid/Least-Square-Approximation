#include <numeric>
#include <cmath>

#include "column_vector.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

namespace agla::mtx {
	template <numeric T> column_vector<T>::column_vector(const std::size_t size) noexcept : mtx::matrix<T>(size, 1) {}
	template <numeric T> column_vector<T>::column_vector(const mtx::matrix<T>& mtx) noexcept : mtx::matrix<T>(mtx) {}
	template <numeric T> column_vector<T>::column_vector(mtx::matrix<T>&& mtx) noexcept : mtx::matrix<T>(mtx) {}
	template <numeric T> column_vector<T>::column_vector(const std::size_t size, const T& elem) noexcept : mtx::matrix<T>(size, std::vector<T> { elem }) {}
	template <numeric T> column_vector<T>::column_vector(const std::size_t size, T&& elem) noexcept : mtx::matrix<T>(size, std::vector<T> { elem }) {}

	template <numeric T> [[nodiscard]] inline std::size_t column_vector<T>::size() const noexcept {
		return this->rows_number();
	}

	template <numeric T> [[nodiscard]] inline std::optional<column_vector<T>> column_vector<T>::operator+(const column_vector& other) const noexcept {
		const auto rows = this->rows_number();

		if (rows != other.rows_number())
			return std::nullopt;

		column_vector result(rows);

		auto this_it = this->begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it + *other_it;
			++this_it, ++other_it;
		}

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<column_vector<T>> column_vector<T>::operator-(const column_vector& other) const noexcept {
		if (size() != other.size())
			return std::nullopt;

		column_vector result(size());

		auto this_it = this->begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it - *other_it;
			++this_it, ++other_it;
		}

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline T& column_vector<T>::get_unchecked(const std::size_t index) noexcept {
		return this->mtx[index].get_unchecked(0);
	}

	template <numeric T> [[nodiscard]] inline const T& column_vector<T>::get_unchecked(const std::size_t index) const noexcept {
		return this->mtx[index].get_unchecked(0);
	}

	template <numeric T> [[nodiscard]] inline double column_vector<T>::norm() const noexcept {
		return std::sqrt(std::accumulate(this->begin(), this->end(), 0.0, [](const auto& acc, const auto& x) {
			return acc + x * x;
		}));
	}

	template column_vector<double>::column_vector(std::size_t size) noexcept;
	template column_vector<double>::column_vector(const mtx::matrix<double>& mtx) noexcept;
	template column_vector<double>::column_vector(mtx::matrix<double>&& mtx) noexcept;
	template column_vector<double>::column_vector(std::size_t size, const double& elem) noexcept;
	template column_vector<double>::column_vector(std::size_t size, double && elem) noexcept;

	template std::size_t column_vector<double>::size() const noexcept;

	template std::optional<column_vector<double>> column_vector<double>::operator+(const column_vector& other) const noexcept;
	template std::optional<column_vector<double>> column_vector<double>::operator-(const column_vector& other) const noexcept;

	template double& column_vector<double>::get_unchecked(std::size_t index) noexcept;
	template const double& column_vector<double>::get_unchecked(std::size_t index) const noexcept;

	template double column_vector<double>::norm() const noexcept;
} // agla::mtx

#pragma clang diagnostic pop