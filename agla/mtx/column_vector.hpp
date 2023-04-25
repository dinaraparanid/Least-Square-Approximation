#ifndef COLUMN_VECTOR_HPP
#define COLUMN_VECTOR_HPP

#include "square_matrix.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

namespace agla::mtx {
	template <numeric T> class column_vector : public matrix<T> {
		explicit column_vector(const mtx::matrix<T>& mtx) noexcept;
		explicit column_vector(mtx::matrix<T>&& mtx) noexcept;

	 public:
		explicit column_vector(std::size_t size) noexcept;
		column_vector(std::size_t size, const T& elem) noexcept;
		column_vector(std::size_t size, T&& elem) noexcept;

		static inline column_vector<T> from_matrix_unchecked(const matrix<T>& mtx) noexcept {
			return column_vector(mtx);
		}

		static inline column_vector<T> from_matrix_unchecked(matrix<T>&& mtx) noexcept {
			return column_vector(mtx);
		}

		static inline std::optional<column_vector<T>> from_matrix(matrix<T>&& mtx) noexcept {
			if (mtx.columns_number() != 1)
				return std::nullopt;

			return std::make_optional(column_vector(mtx));
		}

		static inline std::optional<column_vector<T>> from_matrix(const matrix<T>& mtx) noexcept {
			if (mtx.columns_number() != 1)
				return std::nullopt;

			return std::make_optional(column_vector(mtx));
		}

		static inline std::optional<column_vector<T>> build_from_matrix(const matrix<T>& mtx) noexcept {
			column_vector cv(mtx.rows_number());

			for (std::size_t i = 0; i < cv.size(); ++i)
				cv.get_unchecked(i) = mtx.get_unchecked(i).get_unchecked(0);

			return cv;
		}

		[[nodiscard]] inline std::size_t size() const noexcept;

		[[nodiscard]] inline std::optional<column_vector> operator+(const column_vector& other) const noexcept;
		[[nodiscard]] inline std::optional<column_vector> operator-(const column_vector& other) const noexcept;

		[[nodiscard]] inline T& get_unchecked(std::size_t index) noexcept;
		[[nodiscard]] inline const T& get_unchecked(std::size_t index) const noexcept;

		[[nodiscard]] inline double norm() const noexcept;
	};
} // agla::mtx

#pragma clang diagnostic pop
#endif // COLUMN_VECTOR_HPP