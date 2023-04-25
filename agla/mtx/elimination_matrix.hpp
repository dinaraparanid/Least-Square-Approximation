#ifndef ELIMINATION_MATRIX_HPP
#define ELIMINATION_MATRIX_HPP

#include "identity_matrix.hpp"

namespace agla::mtx {
	template <numeric T> struct elimination_matrix : public identity_matrix<T> {
		elimination_matrix(const square_matrix<T>& mtx, std::size_t row_ind, std::size_t column_ind) noexcept;
		inline elimination_matrix& operator=(const elimination_matrix& matrix) noexcept;
	};
} // agla::mtx

#endif //_ELIMINATION_MATRIX_HPP_
