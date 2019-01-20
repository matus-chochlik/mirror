constexpr auto eval_type@ = reflexpr(Dummy).get_scope().is_type();
constexpr auto eval_named@ = reflexpr(Dummy).get_scope().is_named();
constexpr auto eval_scope@ = reflexpr(Dummy).get_scope().is_scope();
