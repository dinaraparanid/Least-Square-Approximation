#include <algorithm>
#include <iterator>
#include <numeric>

#include "square_matrix.hpp"

namespace agla::mtx {

	// ########################## Matrix Row ##########################

	// ----------------------- Constructors -----------------------

	template <numeric T> matrix<T>::matrix_row::matrix_row() noexcept = default;
	template <numeric T> matrix<T>::matrix_row::matrix_row(const std::size_t size) noexcept : row(std::vector<T>(size)) {}
	template <numeric T> matrix<T>::matrix_row::matrix_row(const std::size_t size, const T& elem) noexcept : row(std::vector<T>(size, elem)) {}
	template <numeric T> matrix<T>::matrix_row::matrix_row(const std::size_t size, T&& elem) noexcept : row(std::vector<T>(size, elem)) {}
	template <numeric T> matrix<T>::matrix_row::matrix_row(const std::vector<T>& row) noexcept : row(row) {}
	template <numeric T> matrix<T>::matrix_row::matrix_row(std::vector<T>&& row) noexcept : row(row) {}

	// ----------------------- Accessors -----------------------

	template <numeric T> [[nodiscard]] inline std::size_t matrix<T>::matrix_row::size() const noexcept { return row.size(); }

	template <numeric T> [[nodiscard]] inline T& matrix<T>::matrix_row::get_unchecked(const std::size_t index) noexcept { return row[index]; }
	template <numeric T> [[nodiscard]] inline const T& matrix<T>::matrix_row::get_unchecked(const std::size_t index) const noexcept { return row[index]; }

	template <numeric T> [[nodiscard]] inline std::optional<std::reference_wrapper<T>> matrix<T>::matrix_row::operator[](const std::size_t index) noexcept {
		if (index >= row.size()) return std::nullopt;
		return std::make_optional(std::ref(get_unchecked(index)));
	}

	// ----------------------- Operators -----------------------

	template <numeric T> [[nodiscard]] inline std::optional<typename matrix<T>::matrix_row> matrix<T>::matrix_row::operator+(const matrix_row& other) const noexcept {
		const auto sz = size();

		if (sz != other.size())
			return std::nullopt;

		matrix_row result(sz);

		for (std::size_t i = 0; i < sz; ++i)
			result.get_unchecked(i) = get_unchecked(i) + other.get_unchecked(i);

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<typename matrix<T>::matrix_row> matrix<T>::matrix_row::operator-(const matrix_row& other) const noexcept {
		const auto sz = size();

		if (sz != other.size())
			return std::nullopt;

		matrix_row result(sz);

		for (std::size_t i = 0; i < sz; ++i)
			result.get_unchecked(i) = get_unchecked(i) - other.get_unchecked(i);

		return std::make_optional(result);
	}

	// ----------------------- Constructors -----------------------

	template matrix<double>::matrix_row::matrix_row() noexcept;
	template matrix<double>::matrix_row::matrix_row(std::size_t size) noexcept;
	template matrix<double>::matrix_row::matrix_row(std::size_t size, const double& elem) noexcept;
	template matrix<double>::matrix_row::matrix_row(std::size_t size, double&& elem) noexcept;
	template matrix<double>::matrix_row::matrix_row(const std::vector<double>& row) noexcept;
	template matrix<double>::matrix_row::matrix_row(std::vector<double>&& row) noexcept;

	// ----------------------- Accessors -----------------------

	template std::size_t matrix<double>::matrix_row::size() const noexcept;
	template double& matrix<double>::matrix_row::get_unchecked(std::size_t index) noexcept;
	template const double& matrix<double>::matrix_row::get_unchecked(std::size_t index) const noexcept;
	template std::optional<std::reference_wrapper<double>> matrix<double>::matrix_row::operator[](std::size_t index) noexcept;

	// ----------------------- Operators -----------------------

	template std::optional<matrix<double>::matrix_row> matrix<double>::matrix_row::operator+(const matrix_row& other) const noexcept;
	template std::optional<matrix<double>::matrix_row> matrix<double>::matrix_row::operator-(const matrix_row& other) const noexcept;

	// ########################## Matrix ##########################

	// ----------------------- Iterators -----------------------

	template <numeric T> [[nodiscard]] inline matrix<T>::iterator matrix<T>::iter(typename matrix<T>::row_iterator row_it, typename matrix<T>::matrix_row::iterator it) noexcept {
		return iterator(row_it, it, rows_begin(), rows_end());
	}

	template <numeric T> [[nodiscard]] inline matrix<T>::const_iterator matrix<T>::const_iter(
		const_row_iterator row_it,
		matrix_row::const_iterator it
	) const noexcept {
		return const_iterator(row_it, it, rows_begin(), rows_end());
	}

	// ----------------------- Constructors -----------------------

	template <numeric T> matrix<T>::matrix(const std::size_t size) noexcept : mtx(std::vector<matrix_row>(size, matrix_row(size))) {}
	template <numeric T> matrix<T>::matrix(const std::size_t rows, const std::size_t columns) noexcept : mtx(std::vector<matrix_row>(rows, matrix_row(columns))) {}
	template <numeric T> matrix<T>::matrix(const std::size_t rows, const std::vector<T>& row) noexcept : mtx(std::vector<matrix_row>(rows, matrix_row(row))) {}
	template <numeric T> matrix<T>::matrix(const std::size_t rows, std::vector<T>&& row) noexcept : mtx(std::vector<matrix_row>(rows, matrix_row(row))) {}

	template <numeric T> matrix<T>::matrix(const std::vector<std::vector<T>>& matrix) noexcept {
		for (const auto& row : matrix)
			mtx.emplace_back(row);
	}

	template <numeric T> matrix<T>::matrix(std::vector<std::vector<T>>&& matrix) noexcept {
		for (auto&& row : matrix)
			mtx.emplace_back(row);
	}

	template <numeric T> matrix<T>::~matrix() noexcept = default;

	// ----------------------- Accessors -----------------------

	template <numeric T> [[nodiscard]] inline std::size_t matrix<T>::rows_number() const noexcept { return mtx.size(); }
	template <numeric T> [[nodiscard]] inline std::size_t matrix<T>::columns_number() const noexcept { return mtx.front().size(); }

	template <numeric T> [[nodiscard]] inline matrix<T>::matrix_row& matrix<T>::get_unchecked(const std::size_t index) noexcept { return mtx[index]; }
	template <numeric T> [[nodiscard]] const matrix<T>::matrix_row& matrix<T>::get_unchecked(const std::size_t index) const noexcept { return mtx[index]; }

	template <numeric T> [[nodiscard]] inline std::optional<std::reference_wrapper<typename matrix<T>::matrix_row>> matrix<T>::operator[](const std::size_t index) noexcept {
		if (index >= mtx.size()) return std::nullopt;
		return std::make_optional(std::ref(get_unchecked(index)));
	}

	template <numeric T> [[nodiscard]] inline std::optional<std::reference_wrapper<const typename matrix<T>::matrix_row>> matrix<T>::operator[](const std::size_t index) const noexcept {
		if (index >= mtx.size()) return std::nullopt;
		return std::make_optional(std::cref(get_unchecked(index)));
	}

	// ----------------------- Operations -----------------------

	template <numeric T> [[nodiscard]] inline matrix<T> matrix<T>::add_unchecked(const matrix& other) const noexcept {
		const auto rows = rows_number();
		const auto columns = columns_number();

		matrix result(rows, columns);

		auto this_it = begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it + *other_it;
			++this_it, ++other_it;
		}

		return std::move(result);
	}

	template <numeric T> [[nodiscard]] inline matrix<T> matrix<T>::sub_unchecked(const matrix& other) const noexcept {
		const auto rows = rows_number();
		const auto columns = columns_number();

		matrix result(rows, columns);

		auto this_it = begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it - *other_it;
			++this_it, ++other_it;
		}

		return std::move(result);
	}

	template <numeric T> [[nodiscard]] inline matrix<T> matrix<T>::mul_unchecked(const matrix& other) const noexcept {
		matrix result(rows_number(), other.columns_number());

		for (int i = 0; i < result.rows_number(); ++i)
			for (int q = 0; q < result.columns_number(); ++q)
				for (int j = 0; j < columns_number(); ++j)
					result.get_unchecked(i).get_unchecked(q) +=
						this->get_unchecked(i).get_unchecked(j) *
						other.get_unchecked(j).get_unchecked(q);

		return std::move(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<matrix<T>> matrix<T>::operator+(const matrix& other) const noexcept {
		const auto rows = rows_number();
		const auto columns = columns_number();

		if (rows != other.rows_number() || columns != other.columns_number())
			return std::nullopt;

		matrix result(rows, columns);

		auto this_it = begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it + *other_it;
			++this_it, ++other_it;
		}

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<matrix<T>> matrix<T>::operator-(const matrix& other) const noexcept {
		const auto rows = rows_number();
		const auto columns = columns_number();

		if (rows != other.rows_number() || columns != other.columns_number())
			return std::nullopt;

		matrix result(rows, columns);

		auto this_it = begin();
		auto other_it = other.begin();

		for (auto& elem : result) {
			elem = *this_it - *other_it;
			++this_it, ++other_it;
		}

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<matrix<T>> matrix<T>::operator* (const matrix& other) const noexcept {
		if (columns_number() != other.rows_number())
			return std::nullopt;

		matrix result(rows_number(), other.columns_number());

		for (int i = 0; i < result.rows_number(); ++i)
			for (int q = 0; q < result.columns_number(); ++q)
				for (int j = 0; j < columns_number(); ++j)
					result.get_unchecked(i).get_unchecked(q) +=
						this->get_unchecked(i).get_unchecked(j) *
						other.get_unchecked(j).get_unchecked(q);

		return std::make_optional(result);
	}

	template <numeric T> [[nodiscard]] inline bool matrix<T>::operator== (const matrix& other) const noexcept {
		if (rows_number() != other.rows_number() || columns_number() != other.columns_number())
			return false;

		return std::equal(begin(), end(), other.begin());
	}

	template <numeric T> [[nodiscard]] inline bool matrix<T>::operator!= (const matrix& other) const noexcept {
		return !(*this == other);
	}

	template <numeric T> inline matrix<T>& matrix<T>::operator=(const matrix& matrix) noexcept {
		mtx = matrix.mtx;
		return *this;
	}

	template <numeric T> [[nodiscard]] inline matrix<T> matrix<T>::transposed() const noexcept {
		matrix result(columns_number(), rows_number());

		for (int i = 0; i < result.rows_number(); ++i)
			for (int q = 0; q <result.columns_number(); ++q)
				result.get_unchecked(i).get_unchecked(q) = get_unchecked(q).get_unchecked(i);

		return result;
	}

	template <numeric T> [[nodiscard]] inline bool matrix<T>::diagonals_greater_than_rows() const noexcept {
		return std::all_of(
			rows_begin(),
			rows_end(),
			[i = std::size_t(0)](const auto& row) mutable {
				const auto diagonal_elem = std::abs(row.get_unchecked(i));

				const auto sum = std::accumulate(row.begin(), row.end(), T(0), [&i, q = std::size_t(0)](const auto& acc, const auto& x) mutable {
					return acc + (q++ != i ? std::abs(x) : 0);
				});

				++i;
				return diagonal_elem >= sum;
			}
		);
	}

	// ----------------------- Iterators -----------------------

	template <numeric T> [[nodiscard]] inline matrix<T>::row_iterator matrix<T>::rows_begin() noexcept { return row_iterator(mtx.begin()); }
	template <numeric T> [[nodiscard]] inline matrix<T>::const_row_iterator matrix<T>::rows_begin() const noexcept { return const_row_iterator(mtx.begin()); }

	template <numeric T> [[nodiscard]] inline matrix<T>::row_iterator matrix<T>::rows_end() noexcept { return row_iterator(mtx.end()); }
	template <numeric T> [[nodiscard]] inline matrix<T>::const_row_iterator matrix<T>::rows_end() const noexcept { return const_row_iterator(mtx.end()); }

	template <numeric T> [[nodiscard]] inline matrix<T>::iterator matrix<T>::begin() noexcept { return iter(rows_begin(), mtx.front().begin()); }
	template <numeric T> [[nodiscard]] inline matrix<T>::const_iterator matrix<T>::begin() const noexcept { return const_iter(rows_begin(), mtx.front().begin()); }

	template <numeric T> [[nodiscard]] inline matrix<T>::iterator matrix<T>::end() noexcept { return iter(rows_end(), mtx.back().end()); }
	template <numeric T> [[nodiscard]] inline matrix<T>::const_iterator matrix<T>::end() const noexcept { return const_iter(rows_end(), mtx.back().end()); }

	// ----------------------- Iterators -----------------------

	template matrix<double>::iterator matrix<double>::iter(matrix<double>::row_iterator row_it, matrix<double>::matrix_row::iterator it) noexcept;
	template matrix<double>::const_iterator matrix<double>::const_iter(const_row_iterator row_it, matrix_row::const_iterator it) const noexcept;

	// ----------------------- Constructors -----------------------

	template matrix<double>::matrix(std::size_t size) noexcept;
	template matrix<double>::matrix(std::size_t rows, std::size_t columns) noexcept;
	template matrix<double>::matrix(std::size_t rows, const std::vector<double>& row) noexcept;
	template matrix<double>::matrix(std::size_t rows, std::vector<double>&& row) noexcept;
	template matrix<double>::matrix(const std::vector<std::vector<double>>& matrix) noexcept;
	template matrix<double>::matrix(std::vector<std::vector<double>>&& matrix) noexcept;

	// ----------------------- Accessors -----------------------

	template std::size_t matrix<double>::rows_number() const noexcept;
	template std::size_t matrix<double>::columns_number() const noexcept;

	template matrix<double>::matrix_row& matrix<double>::get_unchecked(std::size_t index) noexcept;
	template const matrix<double>::matrix_row& matrix<double>::get_unchecked(std::size_t index) const noexcept;

	template std::optional<std::reference_wrapper<matrix<double>::matrix_row>> matrix<double>::operator[](std::size_t index) noexcept;
	template std::optional<std::reference_wrapper<const matrix<double>::matrix_row>> matrix<double>::operator[](std::size_t index) const noexcept;

	// ----------------------- Operations -----------------------

	template matrix<double> matrix<double>::add_unchecked(const matrix& other) const noexcept;
	template matrix<double> matrix<double>::sub_unchecked(const matrix& other) const noexcept;
	template matrix<double> matrix<double>::mul_unchecked(const matrix& other) const noexcept;

	template std::optional<matrix<double>> matrix<double>::operator+(const matrix& other) const noexcept;
	template std::optional<matrix<double>> matrix<double>::operator-(const matrix& other) const noexcept;
	template std::optional<matrix<double>> matrix<double>::operator* (const matrix& other) const noexcept;

	template bool matrix<double>::operator== (const matrix& other) const noexcept;
	template bool matrix<double>::operator!= (const matrix& other) const noexcept;
	template matrix<double>& matrix<double>::operator=(const matrix& matrix) noexcept;

	template matrix<double> matrix<double>::transposed() const noexcept;
	template bool matrix<double>::diagonals_greater_than_rows() const noexcept;

	// ----------------------- Iterators -----------------------

	template matrix<double>::row_iterator matrix<double>::rows_begin() noexcept;
	template matrix<double>::const_row_iterator matrix<double>::rows_begin() const noexcept;

	template matrix<double>::row_iterator matrix<double>::rows_end() noexcept;
	template matrix<double>::const_row_iterator matrix<double>::rows_end() const noexcept;

	template matrix<double>::iterator matrix<double>::begin() noexcept;
	template matrix<double>::const_iterator matrix<double>::begin() const noexcept;

	template matrix<double>::iterator matrix<double>::end() noexcept;
	template matrix<double>::const_iterator matrix<double>::end() const noexcept;
}