#include "P0953.hpp"

struct X {
	struct Y {};
};

int main() {

	const auto moint = reflexpr(X::Y);
	static_assert(moint.is_named());
	static_assert(
	  downcast(moint.get_scope()).get_base_classes().is_object_sequence());

	return 0;
}
