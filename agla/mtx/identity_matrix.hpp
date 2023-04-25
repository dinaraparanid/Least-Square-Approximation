#ifndef IDENTITY_MATRIX_HPP
#define IDENTITY_MATRIX_HPP

#include "square_matrix.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

namespace agla::mtx {
	template <numeric T> class identity_matrix : public square_matrix<T> {
		explicit identity_matrix(const square_matrix<T>& mtx) noexcept;
		explicit identity_matrix(square_matrix<T>&& mtx) noexcept;

	 public:
		explicit identity_matrix(std::size_t size) noexcept;

		inline identity_matrix& operator=(const identity_matrix& matrix) noexcept;

		static inline identity_matrix from_square_matrix(const square_matrix<T>& mtx) noexcept {
			return identity_matrix(mtx.size());
		}

		static inline std::optional<identity_matrix> from_matrix_unchecked(const matrix<T>& mtx) noexcept {
			return identity_matrix(mtx.rows_number());
		}

		static inline std::optional<identity_matrix> from_matrix(const matrix<T>& mtx) noexcept {
			auto&& square_opt = square_matrix<T>::from_matrix(mtx);
			if (!square_opt.has_value()) return std::nullopt;
			return identity_matrix(square_opt.value().size());
		}

	 protected:
		[[nodiscard]] inline matrix<T>::matrix_row& get_unchecked(std::size_t index) noexcept;
		[[nodiscard]] inline std::optional<std::reference_wrapper<typename matrix<T>::matrix_row>> operator[](std::size_t index) noexcept;
	};
} // agla::mtx

#pragma clang diagnostic pop
#endif // IDENTITY_MATRIX_HPP