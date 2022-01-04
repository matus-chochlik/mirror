/// @example mirror/fake_rpc.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/hash.hpp>
#include <mirror/interface.hpp>
#include <mirror/make_tuple.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/serialize/read_rapidjson.hpp>
#include <mirror/serialize/write_rapidjson.hpp>
#include <iostream>
#include <sstream>

struct fake_rpc_skeleton : mirror::interface<fake_rpc_skeleton> {
    virtual void dispatch(
      std::istream& request_header,
      std::istream& request_data,
      std::ostream& response_header,
      std::ostream& response_data) = 0;
};

class fake_rpc_stub_impl {
private:
    std::uint64_t _invocation_id{0};
    fake_rpc_skeleton& _skeleton;

    void _begin_fake_rpc(
      std::ostream& header,
      std::ostream& data,
      auto mo,
      auto&... args) {
        mirror::serialize::write_rapidjson_stream(
          std::make_tuple(get_hash(mo), _invocation_id++), header);
        mirror::serialize::write_rapidjson_stream(
          std::make_tuple(args...), data);
    }

    template <typename R>
    auto _finish_fake_rpc(
      std::istream& header,
      std::istream& data,
      std::type_identity<R>) {
        std::uint64_t invocation_id{};
        mirror::serialize::read_rapidjson_stream(invocation_id, header);
        R result{};
        mirror::serialize::read_rapidjson_stream(result, data);
        return result;
    }

public:
    fake_rpc_stub_impl(fake_rpc_skeleton& skel) noexcept
      : _skeleton{skel} {}

    auto make_call(mirror::metaobject auto mo, auto&... args) {
        std::stringstream request_header;
        std::stringstream request_data;

        _begin_fake_rpc(request_header, request_data, mo, args...);

        std::stringstream response_header;
        std::stringstream response_data;
        _skeleton.dispatch(
          request_header, request_data, response_header, response_data);

        return _finish_fake_rpc(
          response_header,
          response_data,
          get_reflected_type(get_type(get_callable(get_subexpression(mo)))));
    }
};

template <typename Intf>
class fake_rpc_skeleton_impl : public fake_rpc_skeleton {
private:
    Intf& _impl;

    template <typename Metaobject, typename Tup, size_t... I>
    auto _apply(Metaobject mo, Tup& tup, std::index_sequence<I...>) {
        return (_impl.*get_pointer(mo))(std::get<I>(tup)...);
    }

public:
    fake_rpc_skeleton_impl(Intf& impl) noexcept
      : _impl{impl} {}

    void dispatch(
      std::istream& request_header,
      std::istream& request_data,
      std::ostream& response_header,
      std::ostream& response_data) final {
        mirror::hash_t rpc_id{};
        std::uint64_t invocation_id{};
        auto header = std::tie(rpc_id, invocation_id);
        mirror::serialize::read_rapidjson_stream(header, request_header);

        for_each(get_member_functions(mirror(Intf)), [&](auto mf) {
            if(get_hash(mf) == rpc_id) {
                auto params = make_value_tuple(
                  transform(get_parameters(mf), get_type(mirror::_1)));
                mirror::serialize::read_rapidjson_stream(params, request_data);
                mirror::serialize::write_rapidjson_stream(
                  invocation_id, response_header);
                auto result = _apply(
                  mf,
                  params,
                  std::make_index_sequence<
                    std::tuple_size_v<decltype(params)>>{});
                mirror::serialize::write_rapidjson_stream(
                  result, response_data);
            }
        });
    }
};

struct calculator : mirror::interface<calculator> {
    virtual float add(float, float) = 0;
    virtual float subtract(float, float) = 0;
    virtual float multiply(float, float) = 0;
    virtual float divide(float, float) = 0;
    virtual float negate(float) = 0;
    virtual float invert(float) = 0;
};

class calculator_stub : public calculator {
private:
    fake_rpc_stub_impl _impl;

public:
    calculator_stub(fake_rpc_skeleton& skel) noexcept
      : _impl{skel} {}

    float add(float l, float r) final {
        return _impl.make_call(mirror((calculator::add(l, r))), l, r);
    }

    float subtract(float l, float r) final {
        return _impl.make_call(mirror((calculator::subtract(l, r))), l, r);
    }

    float multiply(float l, float r) final {
        return _impl.make_call(mirror((calculator::multiply(l, r))), l, r);
    }

    float divide(float l, float r) final {
        return _impl.make_call(mirror((calculator::divide(l, r))), l, r);
    }

    float negate(float x) final {
        return _impl.make_call(mirror((calculator::negate(x))), x);
    }

    float invert(float x) final {
        return _impl.make_call(mirror((calculator::invert(x))), x);
    }
};

class calculator_impl : public calculator {
public:
    float add(float l, float r) final {
        return l + r;
    }

    float subtract(float l, float r) final {
        return l - r;
    }

    float multiply(float l, float r) final {
        return l * r;
    }

    float divide(float l, float r) final {
        return l / r;
    }

    float negate(float x) final {
        return -x;
    }

    float invert(float x) final {
        return 1 / x;
    }
};

int main() {
    calculator_impl real_calc;
    fake_rpc_skeleton_impl<calculator> calc_skel{real_calc};
    calculator_stub calc_stub{calc_skel};
    calculator& calc = calc_stub;

    std::cout << calc.add(21.F, 21.F) << std::endl;
    std::cout << calc.subtract(10.F, 3.F) << std::endl;
    std::cout << calc.multiply(42.F, 10.F) << std::endl;
    std::cout << calc.divide(1.F, 2.F) << std::endl;
    std::cout << calc.negate(1.F) << std::endl;
    std::cout << calc.invert(10.F) << std::endl;

    return 0;
}
