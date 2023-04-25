#include "elimination_matrix.hpp"

namespace agla::mtx {
	template <numeric T> elimination_matrix<T>::elimination_matrix(
		const square_matrix<T>& mtx,
		const std::size_t row_ind,
		const std::size_t column_ind
	) noexcept : identity_matrix<T>(mtx.rows_number()) {
		const auto diag = mtx.get_unchecked(column_ind).get_unchecked(column_ind);
		const auto elem = mtx.get_unchecked(row_ind).get_unchecked(column_ind);
		this->get_unchecked(row_ind).get_unchecked(column_ind) = -elem / diag;
	}

	template <numeric T> inline elimination_matrix<T>& elimination_matrix<T>::operator=(const elimination_matrix& matrix) noexcept {
		this->mtx = matrix.mtx;
		return *this;
	}

	template elimination_matrix<double>::elimination_matrix(const square_matrix<double>& mtx, std::size_t row_ind, std::size_t column_ind) noexcept;
	template elimination_matrix<double>& elimination_matrix<double>::operator=(const elimination_matrix& matrix) noexcept;
} // mtx