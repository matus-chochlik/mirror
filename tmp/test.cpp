#include "P0953.hpp"

int main() {

	const auto moint = reflexpr(int);
	static_assert(moint.is_named());

	return 0;
}
