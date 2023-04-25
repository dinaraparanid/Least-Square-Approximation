#include <stdexcept>
#include "square_matrix.hpp"

namespace agla::mtx {

	// ----------------------- Constructors -----------------------

	template <numeric T> square_matrix<T>::square_matrix(const matrix<T>& mtx) noexcept : matrix<T>(mtx) {}
	template <numeric T> square_matrix<T>::square_matrix(matrix<T>&& mtx) noexcept : matrix<T>(mtx) {}
	template <numeric T> square_matrix<T>::square_matrix(const std::size_t size) noexcept : matrix<T>(size) {}
	template <numeric T> square_matrix<T>::square_matrix(const std::size_t size, const T& elem) noexcept : matrix<T>(size, std::vector<T>(size, elem)) {}
	template <numeric T> square_matrix<T>::square_matrix(const std::size_t size, T&& elem) noexcept : matrix<T>(size, std::vector<T>(size, elem)) {}
	template <numeric T> square_matrix<T>::square_matrix(const std::vector<std::vector<T>>& mtx) noexcept : matrix<T>(mtx) {}
	template <numeric T> square_matrix<T>::square_matrix(std::vector<std::vector<T>>&& mtx) noexcept : matrix<T>(mtx) {}

	template <numeric T> square_matrix<T>::square_matrix(const std::size_t rows, const std::vector<T>& row) noexcept : matrix<T>(rows, row) {
		if (rows != row.size())
			throw std::length_error("Number of rows does not equal to number of columns");
	}

	// ----------------------- Operations -----------------------

	template <numeric T> [[nodiscard]] inline std::size_t square_matrix<T>::size() const noexcept {
		return this->rows_number();
	}

	template <numeric T> [[nodiscard]] inline square_matrix<T> square_matrix<T>::add_unchecked(const square_matrix& other) const noexcept {
		return square_matrix(static_cast<const matrix<T>*>(this)->add_unchecked(static_cast<matrix<T>>(other)));
	}

	template <numeric T> [[nodiscard]] inline square_matrix<T> square_matrix<T>::sub_unchecked(const square_matrix& other) const noexcept {
		return square_matrix(static_cast<const matrix<T>*>(this)->sub_unchecked(static_cast<matrix<T>>(other)));
	}

	template <numeric T> [[nodiscard]] inline std::optional<square_matrix<T>> square_matrix<T>::operator+(const square_matrix& other) const noexcept {
		auto res = *static_cast<const matrix<T>*>(this) + static_cast<matrix<T>>(other);
		return res.has_value() ? std::make_optional(static_cast<square_matrix>(res.value())) : std::nullopt;
	}

	template <numeric T> [[nodiscard]] inline std::optional<square_matrix<T>> square_matrix<T>::operator-(const square_matrix& other) const noexcept {
		auto res = *static_cast<const matrix<T>*>(this) - static_cast<matrix<T>>(other);
		return res.has_value() ? std::make_optional(static_cast<square_matrix>(res.value())) : std::nullopt;
	}

	template <numeric T> inline square_matrix<T>& square_matrix<T>::operator=(const square_matrix<T>& matrix) noexcept {
		this->mtx = matrix.mtx;
		return *this;
	}

	template <numeric T> [[nodiscard]] inline T square_matrix<T>::determinant() const noexcept {
		auto copy = *this;
		const auto size = copy.size();
		T acc = 1;

		for (std::size_t i = 0; i < size; ++i) {
			auto diag = copy.get_unchecked(i).get_unchecked(i);
			auto diag_index = i;

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto cur_diag = copy.get_unchecked(q).get_unchecked(i);

				if (std::abs(cur_diag) > std::abs(diag)) {
					diag = cur_diag;
					diag_index = q;
				}
			}

			if (diag_index != i) {
				std::swap(copy.get_unchecked(i), copy.get_unchecked(diag_index));
				acc = -acc;
			}

			if (diag == 0)
				return 0;

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto ratio = copy.get_unchecked(q).get_unchecked(i) / diag;
				if (ratio == 0) continue;

				for (std::size_t k = 0; k < size; ++k)
					copy.get_unchecked(q).get_unchecked(k) -=
						copy.get_unchecked(i).get_unchecked(k) * ratio;
			}
		}

		for (std::size_t i = 0; i < size; ++i)
			acc *= copy.get_unchecked(i).get_unchecked(i);

		return acc;
	}

	template <numeric T> [[nodiscard]] inline square_matrix<T> square_matrix<T>::inversed_unchecked() const noexcept {
		const auto size = this->size();
		const auto aug_columns_num = 2 * size;
		matrix<T> aug_mtx(size, std::vector<T>(aug_columns_num, 0));

		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t q = 0; q < size; ++q)
				aug_mtx.get_unchecked(i).get_unchecked(q) = this->get_unchecked(i).get_unchecked(q);
			aug_mtx.get_unchecked(i).get_unchecked(i + size) = 1;
		}

		for (std::size_t i = 0; i < size; ++i) {
			auto diag = aug_mtx.get_unchecked(i).get_unchecked(i);
			auto diag_index = i;

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto cur_diag = aug_mtx.get_unchecked(q).get_unchecked(i);

				if (std::abs(cur_diag) > std::abs(diag)) {
					diag = cur_diag;
					diag_index = q;
				}
			}

			if (diag_index != i)
				std::swap(aug_mtx.get_unchecked(i), aug_mtx.get_unchecked(diag_index));

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto ratio = aug_mtx.get_unchecked(q).get_unchecked(i) / diag;
				if (ratio == 0) continue;

				for (std::size_t k = 0; k < aug_columns_num; ++k)
					aug_mtx.get_unchecked(q).get_unchecked(k) -=
						aug_mtx.get_unchecked(i).get_unchecked(k) * ratio;
			}
		}

		for (int i = size - 1; i >= 0; --i) {
			const auto diag = aug_mtx.get_unchecked(i).get_unchecked(i);

			for (int q = i - 1; q >= 0; --q) {
				const auto ratio = aug_mtx.get_unchecked(q).get_unchecked(i) / diag;
				if (ratio == 0) continue;

				for (std::size_t k = i; k < aug_columns_num; ++k)
					aug_mtx.get_unchecked(q).get_unchecked(k) -=
						aug_mtx.get_unchecked(i).get_unchecked(k) * ratio;
			}
		}

		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t q = size; q < aug_columns_num; ++q)
				aug_mtx.get_unchecked(i).get_unchecked(q) /=
					aug_mtx.get_unchecked(i).get_unchecked(i);
			aug_mtx.get_unchecked(i).get_unchecked(i) = 1;
		}

		square_matrix<T> result(size);

		for (std::size_t i = 0; i < size; ++i)
			for (std::size_t q = 0, qg = size; q < size; ++q, ++qg)
				result.get_unchecked(i).get_unchecked(q) =
					aug_mtx.get_unchecked(i).get_unchecked(qg);

		return std::move(result);
	}

	template <numeric T> [[nodiscard]] inline std::optional<square_matrix<T>> square_matrix<T>::inversed() const noexcept {
		const auto size = this->size();
		const auto aug_columns_num = 2 * size;
		matrix<T> aug_mtx(size, std::vector<T>(aug_columns_num, 0));

		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t q = 0; q < size; ++q)
				aug_mtx.get_unchecked(i).get_unchecked(q) = this->get_unchecked(i).get_unchecked(q);
			aug_mtx.get_unchecked(i).get_unchecked(i + size) = 1;
		}

		for (std::size_t i = 0; i < size; ++i) {
			auto diag = aug_mtx.get_unchecked(i).get_unchecked(i);
			auto diag_index = i;

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto cur_diag = aug_mtx.get_unchecked(q).get_unchecked(i);

				if (std::abs(cur_diag) > std::abs(diag)) {
					diag = cur_diag;
					diag_index = q;
				}
			}

			if (diag_index != i)
				std::swap(aug_mtx.get_unchecked(i), aug_mtx.get_unchecked(diag_index));

			if (diag == 0)
				return std::nullopt;

			for (std::size_t q = i + 1; q < size; ++q) {
				const auto ratio = aug_mtx.get_unchecked(q).get_unchecked(i) / diag;
				if (ratio == 0) continue;

				for (std::size_t k = 0; k < aug_columns_num; ++k)
					aug_mtx.get_unchecked(q).get_unchecked(k) -=
						aug_mtx.get_unchecked(i).get_unchecked(k) * ratio;
			}
		}

		for (int i = size - 1; i >= 0; --i) {
			const auto diag = aug_mtx.get_unchecked(i).get_unchecked(i);

			for (int q = i - 1; q >= 0; --q) {
				const auto ratio = aug_mtx.get_unchecked(q).get_unchecked(i) / diag;
				if (ratio == 0) continue;

				for (std::size_t k = i; k < aug_columns_num; ++k)
					aug_mtx.get_unchecked(q).get_unchecked(k) -=
						aug_mtx.get_unchecked(i).get_unchecked(k) * ratio;
			}
		}

		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t q = size; q < aug_columns_num; ++q)
				aug_mtx.get_unchecked(i).get_unchecked(q) /=
					aug_mtx.get_unchecked(i).get_unchecked(i);
			aug_mtx.get_unchecked(i).get_unchecked(i) = 1;
		}

		square_matrix<T> result(size);

		for (std::size_t i = 0; i < size; ++i)
			for (std::size_t q = 0, qg = size; q < size; ++q, ++qg)
				result.get_unchecked(i).get_unchecked(q) =
					aug_mtx.get_unchecked(i).get_unchecked(qg);

		return { std::move(result) };
	}

	// ----------------------- Constructors -----------------------

	template square_matrix<double>::square_matrix(const matrix<double>& mtx) noexcept;
	template square_matrix<double>::square_matrix(matrix<double>&& mtx) noexcept;
	template square_matrix<double>::square_matrix(std::size_t size) noexcept;
	template square_matrix<double>::square_matrix(std::size_t size, const double& elem) noexcept;
	template square_matrix<double>::square_matrix(std::size_t size, double&& elem) noexcept;
	template square_matrix<double>::square_matrix(const std::vector<std::vector<double>>& mtx) noexcept;
	template square_matrix<double>::square_matrix(std::vector<std::vector<double>>&& mtx) noexcept;
	template square_matrix<double>::square_matrix(std::size_t rows, const std::vector<double>& row) noexcept;

	// ----------------------- Operations -----------------------

	template std::size_t square_matrix<double>::size() const noexcept;

	template square_matrix<double> square_matrix<double>::add_unchecked(const square_matrix& other) const noexcept;
	template square_matrix<double> square_matrix<double>::sub_unchecked(const square_matrix& other) const noexcept;

	template std::optional<square_matrix<double>> square_matrix<double>::operator+(const square_matrix& other) const noexcept;
	template std::optional<square_matrix<double>> square_matrix<double>::operator-(const square_matrix& other) const noexcept;
	template square_matrix<double>& square_matrix<double>::operator=(const square_matrix<double>& matrix) noexcept;

	template double square_matrix<double>::determinant() const noexcept;
	template square_matrix<double> square_matrix<double>::inversed_unchecked() const noexcept;
	template std::optional<square_matrix<double>> square_matrix<double>::inversed() const noexcept;
} // agla::mtx