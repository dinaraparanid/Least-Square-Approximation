#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <optional>
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace agla {
	template <typename NumericType> concept numeric = std::is_arithmetic<NumericType>::value;

	namespace mtx {
		template <numeric T> struct matrix {

			// ########################## Matrix Row ##########################

			class matrix_row {
				std::vector<T> row;

			 public:

				// ----------------------- Iterators -----------------------

				class const_iterator;

				// ########################## Iterator ##########################

				class iterator {
				 public:
					using iterator_category = std::random_access_iterator_tag;
					using difference_type = std::ptrdiff_t;
					using value_type = T;
					using pointer = value_type*;
					using reference = value_type&;

				 private:
					friend class matrix_row;
					std::vector<T>::iterator row_it;
					explicit iterator(std::vector<T>::iterator row_it) noexcept : row_it(row_it) {}

				 public:
					~iterator() noexcept = default;

					// --------------- Dereference operators ---------------

					inline reference operator*() const noexcept { return *row_it; }
					inline pointer operator->() const noexcept { return &*row_it; }

					// --------------- Comparison operators ---------------

					[[nodiscard]] inline bool operator==(const iterator& other) const noexcept { return row_it == other.row_it; };
					[[nodiscard]] inline bool operator!=(const iterator& other) const noexcept { return row_it != other.row_it; };

					[[nodiscard]] inline bool operator==(const const_iterator& other) const noexcept { return row_it == other.row_it; };
					[[nodiscard]] inline bool operator!=(const const_iterator& other) const noexcept { return row_it != other.row_it; };

					// --------------- Movement operators ---------------

					inline iterator operator++() noexcept { ++row_it; return *this; }
					inline iterator operator--() noexcept { --row_it; return *this; }

					[[nodiscard]] inline iterator operator+(const difference_type move) const noexcept { return iterator(row_it + move); }
					[[nodiscard]] inline iterator operator-(const difference_type move) const noexcept { return iterator(row_it - move); }

					[[nodiscard]] inline difference_type operator-(const const_iterator it) const noexcept { return row_it - it.row_it; }
					[[nodiscard]] inline difference_type operator-(const iterator it) const noexcept { return row_it - it.row_it; }

					[[nodiscard]] inline iterator operator+=(const difference_type move) noexcept {
						row_it += move;
						return *this;
					}

					[[nodiscard]] inline iterator operator-=(const difference_type move) noexcept {
						row_it -= move;
						return *this;
					}
				};

				// ########################## Const Iterator ##########################

				class const_iterator {
				 public:
					using iterator_category = std::random_access_iterator_tag;
					using difference_type = std::ptrdiff_t;
					using value_type = T;
					using pointer = const value_type*;
					using reference = const value_type&;

				 private:
					friend class matrix_row;
					std::vector<T>::const_iterator row_it;
					explicit const_iterator(std::vector<T>::const_iterator row_it) noexcept : row_it(row_it) {}

				 public:
					~const_iterator() noexcept = default;

					// --------------- Dereference operators ---------------

					inline reference operator*() const noexcept { return *row_it; }
					inline pointer operator->() const noexcept { return &*row_it; }

					// --------------- Comparison operators ---------------

					[[nodiscard]] inline bool operator==(const iterator& other) const noexcept { return row_it == other.row_it; };
					[[nodiscard]] inline bool operator!=(const iterator& other) const noexcept { return row_it != other.row_it; };

					[[nodiscard]] inline bool operator==(const const_iterator& other) const noexcept { return row_it == other.row_it; };
					[[nodiscard]] inline bool operator!=(const const_iterator& other) const noexcept { return row_it != other.row_it; };

					// --------------- Movement operators ---------------

					inline const_iterator operator++() noexcept { ++row_it; return *this; }
					inline const_iterator operator--() noexcept { --row_it; return *this; }

					[[nodiscard]] inline const_iterator operator+(const difference_type move) const noexcept { return const_iterator(row_it + move); }
					[[nodiscard]] inline const_iterator operator-(const difference_type move) const noexcept { return const_iterator(row_it - move); }

					[[nodiscard]] inline difference_type operator-(const const_iterator it) const noexcept { return row_it - it.row_it; }
					[[nodiscard]] inline difference_type operator-(const iterator it) const noexcept { return row_it - it.row_it; }

					[[nodiscard]] inline const_iterator operator+=(const difference_type move) noexcept {
						row_it += move;
						return *this;
					}

					[[nodiscard]] inline const_iterator operator-=(const difference_type move) noexcept {
						row_it -= move;
						return *this;
					}
				};

				// ----------------------- Constructors -----------------------

				matrix_row() noexcept;

				explicit matrix_row(std::size_t size) noexcept;
				matrix_row(std::size_t size, const T& elem) noexcept;
				matrix_row(std::size_t size, T&& elem) noexcept;

				explicit matrix_row(const std::vector<T>& row) noexcept;
				explicit matrix_row(std::vector<T>&& row) noexcept;

				// ----------------------- Accessors -----------------------

				[[nodiscard]] inline std::size_t size() const noexcept;

				[[nodiscard]] inline T& get_unchecked(std::size_t index) noexcept;
				[[nodiscard]] inline const T& get_unchecked(std::size_t index) const noexcept;

				[[nodiscard]] inline std::optional<std::reference_wrapper<T>> operator[](std::size_t index) noexcept;

				// ----------------------- Operators -----------------------

				[[nodiscard]] inline std::optional<matrix_row> operator+(const matrix_row& other) const noexcept;
				[[nodiscard]] inline std::optional<matrix_row> operator-(const matrix_row& other) const noexcept;

				// ----------------------- Iterators -----------------------

				[[nodiscard]] inline iterator begin() noexcept { return iterator(row.begin()); }
				[[nodiscard]] inline const_iterator begin() const noexcept { return const_iterator(row.begin()); }

				[[nodiscard]] inline iterator end() noexcept { return iterator(row.end()); }
				[[nodiscard]] inline const_iterator end() const noexcept { return const_iterator(row.end()); }
			};

		 protected:
			std::vector<matrix_row> mtx;

			// ----------------------- Row Iterators -----------------------

			class const_row_iterator;

			// ########################## Row Iterator ##########################

			class row_iterator {
			 public:
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = matrix_row;
				using pointer = value_type*;
				using reference = value_type&;

			 private:
				friend class matrix;
				std::vector<matrix_row>::iterator it;
				explicit row_iterator(std::vector<matrix_row>::iterator it) noexcept : it(it) {}

			 public:
				~row_iterator() noexcept = default;

				// --------------- Dereference operators ---------------

				inline reference operator*() const noexcept { return *it; }
				inline pointer operator->() const noexcept { return &*it; }

				// --------------- Comparison operators ---------------

				[[nodiscard]] inline bool operator==(const row_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const row_iterator& other) const noexcept { return it != other.it; };

				[[nodiscard]] inline bool operator==(const const_row_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const const_row_iterator& other) const noexcept { return it != other.it; };

				// --------------- Movement operators ---------------

				inline row_iterator operator++() noexcept { ++it; return *this; }
				inline row_iterator operator--() noexcept { --it; return *this; }

				[[nodiscard]] inline row_iterator operator+(const difference_type move) const noexcept { return row_iterator(it + move); }
				[[nodiscard]] inline row_iterator operator-(const difference_type move) const noexcept { return row_iterator(it - move); }

				[[nodiscard]] inline difference_type operator-(const row_iterator iter) const noexcept { return it - iter.it; }
				[[nodiscard]] inline difference_type operator-(const const_row_iterator iter) const noexcept { return it - iter.it; }

				[[nodiscard]] inline row_iterator operator+=(const difference_type move) noexcept {
					it += move;
					return *this;
				}

				[[nodiscard]] inline row_iterator operator-=(const difference_type move) noexcept {
					it -= move;
					return *this;
				}
			};

			// ########################## Const Iterator ##########################

			class const_row_iterator {
			 public:
				using iterator_category = std::random_access_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = matrix_row;
				using pointer = const value_type*;
				using reference = const value_type&;

			 private:
				friend class matrix;
				std::vector<matrix_row>::const_iterator it;
				explicit const_row_iterator(std::vector<matrix_row>::const_iterator it) noexcept : it(it) {}

			 public:
				~const_row_iterator() noexcept = default;

				// --------------- Dereference operators ---------------

				inline reference operator*() const noexcept { return *it; }
				inline pointer operator->() const noexcept { return &*it; }

				// --------------- Comparison operators ---------------

				[[nodiscard]] inline bool operator==(const row_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const row_iterator& other) const noexcept { return it != other.it; };

				[[nodiscard]] inline bool operator==(const const_row_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const const_row_iterator& other) const noexcept { return it != other.it; };

				// --------------- Movement operators ---------------

				inline const_row_iterator operator++() noexcept { ++it; return *this; }
				inline const_row_iterator operator--() noexcept { --it; return *this; }

				[[nodiscard]] inline const_row_iterator operator+(const difference_type move) const noexcept { return const_row_iterator(it + move); }
				[[nodiscard]] inline const_row_iterator operator-(const difference_type move) const noexcept { return const_row_iterator(it - move); }

				[[nodiscard]] inline difference_type operator-(const row_iterator iter) const noexcept { return it - iter.it; }
				[[nodiscard]] inline difference_type operator-(const const_row_iterator iter) const noexcept { return it - iter.it; }

				[[nodiscard]] inline const_row_iterator operator+=(const difference_type move) noexcept {
					it += move;
					return *this;
				}

				[[nodiscard]] inline const_row_iterator operator-=(const difference_type move) noexcept {
					it -= move;
					return *this;
				}
			};

		 public:

			// ----------------------- Iterators -----------------------

			class const_iterator;

			// ########################## Iterator ##########################

			class iterator {
			 public:
				using iterator_category = std::bidirectional_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using pointer = value_type*;
				using reference = value_type&;

			 private:
				friend class matrix;
				row_iterator row_it;
				matrix_row::iterator it;

				const row_iterator rows_begin;
				const row_iterator rows_end;

				iterator(
					row_iterator row_it,
					matrix_row::iterator it,
					const row_iterator rows_begin,
					const row_iterator rows_end
				) noexcept : row_it(row_it), it(it), rows_begin(rows_begin), rows_end(rows_end) {}

			 public:
				~iterator() noexcept = default;

				// --------------- Dereference operators ---------------

				inline reference operator*() const noexcept { return *it; }
				inline pointer operator->() const noexcept { return &*it; }

				// --------------- Comparison operators ---------------

				[[nodiscard]] inline bool operator==(const iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const iterator& other) const noexcept { return it != other.it; };

				[[nodiscard]] inline bool operator==(const const_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const const_iterator& other) const noexcept { return it != other.it; };

				// --------------- Movement operators ---------------

				inline iterator operator++() noexcept {
					const auto row_end_it = row_it->end();

					if (std::next(it) == row_end_it)
						it = (row_it + 1 == rows_end) ? row_end_it : (++row_it)->begin();
					else
						++it;

					return *this;
				}

				inline iterator operator--() noexcept {
					const auto row_begin_it = row_it->begin();

					if (it == row_begin_it) {
						if (row_it != rows_begin)
							it = std::prev((--row_it)->end());
					} else { --it; }

					return *this;
				}
			};

			[[nodiscard]] inline iterator iter(row_iterator row_it, matrix_row::iterator it) noexcept;

			// ########################## Const Iterator ##########################

			class const_iterator {
			 public:
				using iterator_category = std::bidirectional_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using pointer = const value_type*;
				using reference = const value_type&;

			 private:
				friend class matrix;
				const_row_iterator row_it;
				matrix_row::const_iterator it;

				const const_row_iterator rows_begin;
				const const_row_iterator rows_end;

				const_iterator(
					const_row_iterator row_it,
					matrix_row::const_iterator it,
					const const_row_iterator rows_begin,
					const const_row_iterator rows_end
				) noexcept : row_it(row_it), it(it), rows_begin(rows_begin), rows_end(rows_end) {}

			 public:
				~const_iterator() noexcept = default;

				// --------------- Dereference operators ---------------

				inline reference operator*() const noexcept { return *it; }
				inline pointer operator->() const noexcept { return &*it; }

				// --------------- Comparison operators ---------------

				[[nodiscard]] inline bool operator==(const iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const iterator& other) const noexcept { return it != other.it; };

				[[nodiscard]] inline bool operator==(const const_iterator& other) const noexcept { return it == other.it; };
				[[nodiscard]] inline bool operator!=(const const_iterator& other) const noexcept { return it != other.it; };

				// --------------- Movement operators ---------------

				inline const_iterator operator++() noexcept {
					const auto row_end_it = row_it->end();

					if (std::next(it) == row_end_it)
						it = (row_it + 1 == rows_end) ? row_end_it : (++row_it)->begin();
					else
						++it;

					return *this;
				}

				inline const_iterator operator--() noexcept {
					const auto row_begin_it = row_it->begin();

					if (it == row_begin_it) {
						if (row_it != rows_begin)
							it = std::prev((--row_it)->end());
					} else { --it; }

					return *this;
				}
			};

			[[nodiscard]] inline const_iterator const_iter(const_row_iterator row_it, matrix_row::const_iterator it) const noexcept;

			// ----------------------- Constructors -----------------------

			explicit matrix(std::size_t size) noexcept;

			matrix(std::size_t rows, std::size_t columns) noexcept;
			matrix(std::size_t rows, const std::vector<T>& row) noexcept;
			matrix(std::size_t rows, std::vector<T>&& row) noexcept;

			explicit matrix(const std::vector<std::vector<T>>& matrix) noexcept;
			explicit matrix(std::vector<std::vector<T>>&& matrix) noexcept;

			~matrix() noexcept;

			// ----------------------- Accessors -----------------------

			[[nodiscard]] inline std::size_t rows_number() const noexcept;
			[[nodiscard]] inline std::size_t columns_number() const noexcept;

			[[nodiscard]] inline matrix_row& get_unchecked(std::size_t index) noexcept;
			[[nodiscard]] const matrix_row& get_unchecked(std::size_t index) const noexcept;

			[[nodiscard]] inline std::optional<std::reference_wrapper<matrix_row>> operator[](std::size_t index) noexcept;
			[[nodiscard]] inline std::optional<std::reference_wrapper<const matrix_row>> operator[](std::size_t index) const noexcept;

			// ----------------------- Operations -----------------------

			[[nodiscard]] inline matrix add_unchecked(const matrix& other) const noexcept;
			[[nodiscard]] inline matrix sub_unchecked(const matrix& other) const noexcept;
			[[nodiscard]] inline matrix mul_unchecked (const matrix& other) const noexcept;

			[[nodiscard]] inline std::optional<matrix> operator+(const matrix& other) const noexcept;
			[[nodiscard]] inline std::optional<matrix> operator-(const matrix& other) const noexcept;
			[[nodiscard]] inline std::optional<matrix> operator* (const matrix& other) const noexcept;

			[[nodiscard]] inline bool operator== (const matrix& other) const noexcept;
			[[nodiscard]] inline bool operator!= (const matrix& other) const noexcept;

			inline matrix& operator=(const matrix& matrix) noexcept;

			[[nodiscard]] inline matrix transposed() const noexcept;
			[[nodiscard]] inline bool diagonals_greater_than_rows() const noexcept;

			// ----------------------- Iterators -----------------------

			[[nodiscard]] inline row_iterator rows_begin() noexcept;
			[[nodiscard]] inline const_row_iterator rows_begin() const noexcept;

			[[nodiscard]] inline row_iterator rows_end() noexcept;
			[[nodiscard]] inline const_row_iterator rows_end() const noexcept;

			[[nodiscard]] inline iterator begin() noexcept;
			[[nodiscard]] inline const_iterator begin() const noexcept;

			[[nodiscard]] inline iterator end() noexcept;
			[[nodiscard]] inline const_iterator end() const noexcept;
		};

		// ----------------------- Extensions -----------------------

		template <numeric T> inline std::istream& operator >> (std::istream& in, matrix<T>& mtx) noexcept {
			for (auto& cell : mtx)
				in >> cell;

			return in;
		}

		template <numeric T> inline std::ostream& operator << (std::ostream& out, const matrix<T>& mtx) noexcept {
			for (auto row_it = mtx.rows_begin(); row_it != mtx.rows_end(); ++row_it) {
				std::copy(row_it->begin(), std::prev(row_it->end()), std::ostream_iterator<T>(out, " "));
				out << *std::prev(row_it->end()) << std::endl;
			}

			return out;
		}

		template <> inline std::ostream& operator << (std::ostream& out, const matrix<double>& mtx) noexcept {
			for (auto row_it = mtx.rows_begin(); row_it != mtx.rows_end(); ++row_it) {
				std::transform(
					row_it->begin(),
					std::prev(row_it->end()),
					std::ostream_iterator<double>(out, " "),
					[](const auto& x) { return x == 0 ? 0 : x; }
				);

				const auto last = *std::prev(row_it->end());
				out << (last == 0 ? 0 : last) << std::endl;
			}

			return out;
		}
	} // mtx
} // agla

#endif // MATRIX_HPP
