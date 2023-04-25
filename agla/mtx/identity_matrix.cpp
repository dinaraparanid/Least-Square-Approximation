#include "identity_matrix.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

namespace agla::mtx {
	template <numeric T> identity_matrix<T>::identity_matrix(const square_matrix<T>& mtx) noexcept : square_matrix<T>(mtx) {}
	template <numeric T> identity_matrix<T>::identity_matrix(square_matrix<T>&& mtx) noexcept : square_matrix<T>(mtx) {}

	template <numeric T> identity_matrix<T>::identity_matrix(const std::size_t size) noexcept : square_matrix<T>(size, std::vector<T>(size, 0)) {
		for (std::size_t i = 0; i < size; ++i)
			this->get_unchecked(i).get_unchecked(i) = 1;
	}

	template <numeric T> inline identity_matrix<T>& identity_matrix<T>::operator=(const identity_matrix& matrix) noexcept {
		this->mtx = matrix.mtx;
		return *this;
	}

	template <numeric T> [[nodiscard]] inline matrix<T>::matrix_row& identity_matrix<T>::get_unchecked(const std::size_t index) noexcept {
		return this->mtx[index];
	}

	template <numeric T> [[nodiscard]] inline std::optional<std::reference_wrapper<typename matrix<T>::matrix_row>> identity_matrix<T>::operator[](const std::size_t index) noexcept {
		if (index >= this->size()) return std::nullopt;
		return std::make_optional(std::ref(get_unchecked(index)));
	}

	template identity_matrix<double>::identity_matrix(const square_matrix<double>& mtx) noexcept;
	template identity_matrix<double>::identity_matrix(square_matrix<double>&& mtx) noexcept;
	template identity_matrix<double>::identity_matrix(std::size_t size) noexcept;

	template identity_matrix<double>& identity_matrix<double>::operator=(const identity_matrix& matrix) noexcept;
	template matrix<double>::matrix_row& identity_matrix<double>::get_unchecked(std::size_t index) noexcept;
	template std::optional<std::reference_wrapper<matrix<double>::matrix_row>> identity_matrix<double>::operator[](std::size_t index) noexcept;
} // agla::mtx

#pragma clang diagnostic pop