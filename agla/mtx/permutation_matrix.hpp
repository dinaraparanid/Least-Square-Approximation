#ifndef PERMUTATION_MATRIX_HPP
#define PERMUTATION_MATRIX_HPP

#include "identity_matrix.hpp"

namespace agla::mtx {
	template <numeric T> struct permutation_matrix : public identity_matrix<T> {
		explicit permutation_matrix(const square_matrix<T>& mtx, std::size_t row_ind, std::size_t column_ind) noexcept;
		inline permutation_matrix& operator=(const permutation_matrix& matrix) noexcept;
	};
} // agla::mtx

#endif // PERMUTATION_MATRIX_HPP
