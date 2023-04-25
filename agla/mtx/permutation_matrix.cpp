#include "permutation_matrix.hpp"

namespace agla::mtx {
	template <numeric T> permutation_matrix<T>::permutation_matrix(
		const square_matrix<T>& mtx,
		const std::size_t row_ind,
		const std::size_t column_ind
	) noexcept : identity_matrix<T>(mtx.rows_number()) {
		this->get_unchecked(row_ind).get_unchecked(row_ind) = 0;
		this->get_unchecked(column_ind).get_unchecked(column_ind) = 0;

		this->get_unchecked(row_ind).get_unchecked(column_ind) = 1;
		this->get_unchecked(column_ind).get_unchecked(row_ind) = 1;
	}

	template <numeric T> [[nodiscard]] inline permutation_matrix<T>& permutation_matrix<T>::operator=(const permutation_matrix& matrix) noexcept {
		this->mtx = matrix.mtx;
		return *this;
	}

	template permutation_matrix<double>::permutation_matrix(const square_matrix<double>& mtx, std::size_t row_ind, std::size_t column_ind) noexcept;
	template permutation_matrix<double>& permutation_matrix<double>::operator=(const permutation_matrix& matrix) noexcept;
} // agla::mtx