#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "matrix.hpp"

namespace agla::mtx {
	template <numeric T> class square_matrix : public matrix<T> {
		explicit square_matrix(const matrix<T>& mtx) noexcept;
		explicit square_matrix(matrix<T>&& mtx) noexcept;

	 public:

		// ----------------------- Constructors -----------------------

		explicit square_matrix(std::size_t size) noexcept;

		square_matrix(std::size_t size, const T& elem) noexcept;
		square_matrix(std::size_t size, T&& elem) noexcept;

		square_matrix(std::size_t rows, const std::vector<T>& row) noexcept;

		explicit square_matrix(const std::vector<std::vector<T>>& mtx) noexcept;
		explicit square_matrix(std::vector<std::vector<T>>&& mtx) noexcept;

		static inline square_matrix from_matrix_unchecked(const matrix<T>& mtx) noexcept {
			return square_matrix(mtx);
		}

		static inline square_matrix from_matrix_unchecked(matrix<T>&& mtx) noexcept {
			return square_matrix(mtx);
		}

		static inline std::optional<square_matrix> from_matrix(const matrix<T>& mtx) noexcept {
			if (mtx.rows_number() != mtx.columns_number())
				return std::nullopt;

			return std::make_optional(square_matrix(mtx));
		}

		static inline std::optional<square_matrix> from_matrix(matrix<T>&& mtx) noexcept {
			if (mtx.rows_number() != mtx.columns_number())
				return std::nullopt;

			return std::make_optional(square_matrix(mtx));
		}

		// ----------------------- Operations -----------------------

		[[nodiscard]] inline std::size_t size() const noexcept;

		[[nodiscard]] inline square_matrix add_unchecked(const square_matrix& other) const noexcept;
		[[nodiscard]] inline square_matrix sub_unchecked(const square_matrix& other) const noexcept;

		[[nodiscard]] inline std::optional<square_matrix> operator+(const square_matrix& other) const noexcept;
		[[nodiscard]] inline std::optional<square_matrix> operator-(const square_matrix& other) const noexcept;
		inline square_matrix& operator=(const square_matrix& matrix) noexcept;

		[[nodiscard]] inline T determinant() const noexcept;
		[[nodiscard]] inline square_matrix inversed_unchecked() const noexcept;
		[[nodiscard]] inline std::optional<square_matrix<T>> inversed() const noexcept;
	};
} // agla::mtx

#endif // SQUARE_MATRIX_HPP
