#include "../../include/mathlib/Complex.hpp"
#include <variant>

class Value {
  public:
	std::variant<long long, double, Complex /*,
											 * Matrix,
											 * Vector,
											 * Rational*/>
		data;
	void print() const;
};
