#include "P0953.hpp"

struct X {};

int main() {

	const auto moint = reflexpr(X);
	static_assert(moint.is_named());
	static_assert(moint.get_scope().is_scope());

	return 0;
}
