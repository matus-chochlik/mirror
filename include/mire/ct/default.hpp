/**
 * @file mire/ct/default.hpp
 * @brief Default implementation of the compile-time algorithms
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_DEFAULT_1105240825_HPP
#define MIRE_CT_DEFAULT_1105240825_HPP

#include <mire/config.hpp>
#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/optional.hpp>
#include <mire/ct/evaluate.hpp>

namespace mire {
namespace ct {

/// Returns the IfTrue or the IfFalse type based on the passed BooleanConstant
/**
 *  @tparam BooleanConstant the boolean constant type determining the result
 *  @tparam IfTrue the type returned if the BooleanConstant has the true value
 *  @tparam IfFalse the type returned if the BooleanConstant has false value
 *
 *  @ingroup ct_utils
 */
template <typename BooleanConstant, typename IfTrue, typename IfFalse>
struct if_
#ifndef MIRROR_DOCUMENTATION_ONLY
 : if_<typename evaluate<BooleanConstant>::type, IfTrue, IfFalse>
{ };
#else
{
	/// The @a IfTrue or @a IfFalse type depending on @a BooleanConstant
	typedef unspecified type;
};
#endif

/// Returns the IfTrue or the IfFalse type depending on the passed boolean value
/**
 *  @tparam BooleanConstant the boolean constant value determining the result
 *  @tparam IfTrue the type returned if the BooleanConstant has the true value
 *  @tparam IfFalse the type returned if the BooleanConstant has false value
 *
 *  @ingroup ct_utils
 */
template <bool BooleanConstant, typename IfTrue, typename IfFalse>
struct if_c;

/// Evaluates the IfTrue or the IfFalse expression depending on BooleanConstant
/**
 *  @tparam BooleanConstant the boolean constant type determining the result
 *  @tparam IfTrue the expression evaluated if the BooleanConstant has true value
 *  @tparam IfFalse the expression evaluated if the BooleanConstant has false value
 *
 *  @ingroup ct_utils
 */
template <typename BooleanConstant, typename IfTrue, typename IfFalse>
struct eval_if
#ifndef MIRROR_DOCUMENTATION_ONLY
 : eval_if<typename evaluate<BooleanConstant>::type, IfTrue, IfFalse>
{ };
#else
{
	/// The result of @a IfTrue or @a IfFalse depending on @a BooleanConstant
	typedef unspecified type;
};
#endif

/// Evaluates the IfTrue or the IfFalse expression depending on BooleanConstant
/**
 *  @tparam BooleanConstant the boolean constant value determining the result
 *  @tparam IfTrue the expression evaluated if the BooleanConstant has true value
 *  @tparam IfFalse the expression evaluated if the BooleanConstant has false value
 *
 *  @ingroup ct_utils
 */
template <bool BooleanConstant, typename IfTrue, typename IfFalse>
struct eval_if_c;

/// Metafunction returning a null terminated C-string literal from a String
/** This function returns a null-terminated C-string for the compile-time
 *  string, passed as the @a String template parameter.
 *
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename String>
struct c_str
#ifndef MIRROR_DOCUMENTATION_ONLY
 : c_str<typename evaluate<String>::type>
{ };
#else
{
	/// The C-string literal
	static constexpr const char* value;
};
#endif

/// Metafunction returning the character type of a compile-time String
/**
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename String>
struct char_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : char_type<typename evaluate<String>::type>
{ };
#else
{
	/// The character type use by the examined compile-time String
	typedef unspecified_char_type type;
};
#endif

/// Metafunction returning String from a StringLiteralClass
/** This metafunction returns a compile-time String equal to the compile-time
 *  StringLiteralClass passed as argument.
 *
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename StringLiteralClass>
struct to_string
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : String
{ };
#endif

/// Metafunction returning true_type if a compile-time String is empty
/**
 *  @see basic_string
 *  @see nonempty
 *  @see size
 *  @see length
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct empty
#ifndef MIRROR_DOCUMENTATION_ONLY
 : empty<typename evaluate<Range>::type>
#else
 : BooleanConstantType
#endif
{ };

/// Metafunction returning true_type if a compile-time string is not empty
/**
 *  @see basic_string
 *  @see empty
 *  @see size
 *  @see length
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct nonempty
#ifndef MIRROR_DOCUMENTATION_ONLY
 : nonempty<typename evaluate<Range>::type>
#else
 : BooleanConstantType
#endif
{ };

/// Nil intrinsic metafunction for Optional
/**
 *  @tparam Optional the optional to be examined
 *  @see optional
 *  @see get
 *  @ingroup ct_utils
 */
template <typename Optional>
struct nil
#ifndef MIRROR_DOCUMENTATION_ONLY
 : nil<typename evaluate<Optional>::type>
#else
 : BooleanConstantType
#endif
{ };

/// Metafunction returning the length of a compile-time String
/**
 *  This metafunction is equivalent to the @c length metafunction.
 *  @see basic_string
 *  @see empty
 *  @see nonempty
 *  @see length
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct size
#ifndef MIRROR_DOCUMENTATION_ONLY
 : size<typename evaluate<Range>::type>
#else
 : IntegralConstantType
#endif
{ };

/// Metafunction returning the length of a compile-time String
/**
 *  This metafunction is equivalent to the @c size metafunction.
 *  @see basic_string
 *  @see empty
 *  @see nonempty
 *  @see size
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct length
#ifndef MIRROR_DOCUMENTATION_ONLY
 : length<typename evaluate<Range>::type>
#else
 : IntegralConstantType
#endif
{ };

/// Metafunction returnint the element of the optional passed as argument
/**
 *  This operation may be invoked only on non-nil optionals.
 *
 *  @tparam Optional the optional the item of which is to be returned
 *  @see optional
 *  @see nil
 *  @see empty
 *  @ingroup ct_utils
 */
template <typename Optional>
struct get
#ifndef MIRROR_DOCUMENTATION_ONLY
 : get<typename evaluate<Optional>::type>
{ };
#else
{
	/// The type in the optional passed as argument
	typedef unspecified_type type;
};
#endif

/// Equality comparison metafunction for compile-time Range
/**
 *  @see basic_string
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct equal
#ifndef MIRROR_DOCUMENTATION_ONLY
 : equal<
	typename evaluate<Range1>::type,
	typename evaluate<Range2>::type
>
#else
 : BooleanConstantType
#endif
{ };

/// Non-equality comparison metafunction for compile-time Range
/**
 *  @see basic_string
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct nonequal
#ifndef MIRROR_DOCUMENTATION_ONLY
 : nonequal<
	typename evaluate<Range1>::type,
	typename evaluate<Range2>::type
>
#else
 : BooleanConstantType
#endif
{ };

/// Equality comparison metafunction for arbitrary types
/**
 *  @ingroup ct_utils
 */
template <typename T, typename ... P>
struct equal_types
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : BooleanConstantType
{ };
#endif

/// Metafunction returning the first element of a compile-time Range or String
/**
 *  @see range
 *  @see basic_string
 *  @see empty
 *  @see nonempty
 *  @see next
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct front
#ifndef MIRROR_DOCUMENTATION_ONLY
 : front<typename evaluate<Range>::type>
#else
 : CharacterConstantType
#endif
{ };

/// Metafunction returning a Range or String without its first element
/**
 *  @see basic_string
 *  @see empty
 *  @see nonempty
 *  @see front
 *  @see skip_front
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct next
#ifndef MIRROR_DOCUMENTATION_ONLY
 : next<typename evaluate<Range>::type>
{ };
#else
{
	/// The original compile-time Range without the first element
	typedef String type;
};
#endif

/// Metafunction concatenating several compile-time Range(s) or String(s) together
/**
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename ... Ranges>
struct concat
#ifndef MIRROR_DOCUMENTATION_ONLY
 : concat<typename evaluate<Ranges>::type...>
#else
 : Range
#endif
{ };

/// Metafunction creating a Range containing @p Count instances of @p Type
/**
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename Count, typename Type>
struct repeat_type
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Metafunction creating a Range containing @p Count instances of @p Type
/**
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <size_t Count, typename Type>
struct repeat_type_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Metafunction creating a String containing @p Count instances of @p Element
/**
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Count, typename Char, Char C>
struct repeat_char
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Metafunction creating a String containing @p Count instances of @p Element
/**
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <size_t Count, typename Char, Char C>
struct repeat_char_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Returns a Range having the passed item(s) appended.
/**
 *  @see range
 *
 *  @tparam Range the range to be modified
 *  @tparam T the type(s) to be appended to the range
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename ... T>
struct append
#ifndef MIRROR_DOCUMENTATION_ONLY
 : append<typename evaluate<Range>::type, T...>
#else
 : Range
#endif
{ };

/// Returns a String having the passed item(s) appended.
/**
 *  @see basic_string
 *
 *  @tparam String the range to be modified
 *  @tparam T the character(s) to be appended to the range
 *
 *  @ingroup ct_utils
 */
template <typename String, typename Char, Char ... T>
struct append_c
#ifndef MIRROR_DOCUMENTATION_ONLY
 : append_c<typename evaluate<String>::type, Char, T...>
#else
 : String
#endif
{ };

/// Returns a String having the passed item(s) appended.
/**
 *  @see basic_string
 *
 *  @tparam String the range to be modified
 *  @tparam T the character(s) to be appended to the range
 *
 *  @ingroup ct_utils
 */
template <typename String, char ... T>
struct append_char
#ifndef MIRROR_DOCUMENTATION_ONLY
 : append_c<typename evaluate<String>::type, char, T...>
#else
 : String
#endif
{ };

/// Returns a Range having the passed item(s) prepended.
/**
 *  @see range
 *
 *  @tparam Range the range to be modified
 *  @tparam T the type(s) to be prepended to the range
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename ... T>
struct prepend
#ifndef MIRROR_DOCUMENTATION_ONLY
 : prepend<typename evaluate<Range>::type, T...>
#else
 : Range
#endif
{ };

/// Returns a String having the passed item(s) prepended.
/**
 *  @see basic_string
 *
 *  @tparam String the range to be modified
 *  @tparam T the character(s) to be prepended to the range
 *
 *  @ingroup ct_utils
 */
template <typename String, typename Char, Char ... T>
struct prepend_c
#ifndef MIRROR_DOCUMENTATION_ONLY
 : prepend_c<typename evaluate<String>::type, Char, T...>
#else
 : String
#endif
{ };

/// Removes the first element from a range
/**
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct pop_front
#ifndef MIRROR_DOCUMENTATION_ONLY
 : pop_front<typename evaluate<Range>::type>
#else
 : Range
#endif
{ };

/// Removes the specified element from a Range
/**
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Elem>
struct remove
#ifndef MIRROR_DOCUMENTATION_ONLY
 : remove<typename evaluate<Range>::type, Elem>
#else
 : Range
#endif
{ };

/// Removes the specified character from a String
/**
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename String, typename Char, Char C>
struct remove_c
#ifndef MIRROR_DOCUMENTATION_ONLY
 : remove_c<typename evaluate<String>::type, Char, C>
#else
 : Range
#endif
{ };

/// Removes elements satisfying a predicate from a Range
/**
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Predicate>
struct remove_if
#ifndef MIRROR_DOCUMENTATION_ONLY
 : remove_if<typename evaluate<Range>::type, Predicate>
#else
 : Range
#endif
{ };

/// Returns a sub-Range containing the first @p Count elements of @p Range
/**
 *  @see range
 *  @see basic_string
 *  @see tail
 *  @see slice
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Count>
struct head
#ifndef MIRROR_DOCUMENTATION_ONLY
 : head<
	typename evaluate<Range>::type,
	typename evaluate<Count>::type
>
#else
 : Range
#endif
{ };

/// Returns a sub-Range containing the first @p Count elements of @p Range
/**
 *  @see head_c
 *  @see tail
 *  @see slice
 *
 *  @ingroup ct_utils
 */
template <typename Range, size_t Count>
struct head_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Returns a sub-Range containing the last @p Count elements of @p Range
/**
 *  @see range
 *  @see basic_string
 *  @see head
 *  @see tail
 *  @see tail_c
 *  @see slice
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Count>
struct tail
#ifndef MIRROR_DOCUMENTATION_ONLY
 : tail<
	typename evaluate<Range>::type,
	typename evaluate<Count>::type
>
#else
 : Range
#endif
{ };

/// Returns a sub-Range containing the last @Count elements of @p Range
/**
 *  @see basic_string
 *  @see head
 *  @see tail
 *  @see slice
 *
 *  @ingroup ct_utils
 */
template <typename Range, size_t Count>
struct tail_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Metafunction returning the position of sub-range in a Range
/** This metafunction template returns the position of a sub-range
 *  in the original compile-time range, or nil_t if the sub-range
 *  is not present in the original range.
 *
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct position
#ifndef MIRROR_DOCUMENTATION_ONLY
 : position<
	typename evaluate<Range1>::type,
	typename evaluate<Range2>::type
>
#else
 : IntegralConstantOrNil
#endif
{ };

/// Returns a sub-range ending before the first occurence of the searched Range
/**
 *  @tparam Range1 the range to search in.
 *  @tparam Range2 the range searched for
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct before
#ifndef MIRROR_DOCUMENTATION_ONLY
 : before<
	typename evaluate<Range1>::type,
	typename evaluate<Range2>::type
>
#else
 : Range
#endif
{ };

/// Returns a Range starting with the searched sub-range
/** This metafunction template returns a sub-range of the original
 *  compile-time range, that starts with the searched range (in case
 *  the original range contains it) or an empty range (otherwise).
 *
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct find
#ifndef MIRROR_DOCUMENTATION_ONLY
 : find<
	typename evaluate<Range1>::type,
	typename evaluate<Range2>::type
>
#else
 : Range
#endif
{ };

/// Returns a sub-Range starting with first elements satisfying @p a Predicate
/** This metafunction template returns a sub-range of the original
 *  compile-time range, that starts with the first element satisfying a unary
 *  predicate (in case the original range contains it) or and empty range
 *  (otherwise).
 *
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Predicate>
struct find_if
#ifndef MIRROR_DOCUMENTATION_ONLY
 : find_if<typename evaluate<Range>::type, Predicate>
#else
 : Range
#endif
{ };

/// Returng a sub-range of a compile-time Range
/** This metafunction returns a sub-Range starting at a specified
 *  position with the given length
 *
 *  @see range
 *  @see basic_string
 *  @see head
 *  @see tail
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Start, typename Size>
struct slice
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : String
{ };
#endif

/// Metafunction returning a sub-Range of a compile-time Range
/**
 *  @see basic_string
 *  @see head_c
 *  @see tail_c
 *
 *  @ingroup ct_utils
 */
template <typename Range, size_t Start, size_t Size>
struct slice_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : Range
{ };
#endif

/// Metafunction returning a sub-Range without the first N elements
/**
 *  @see basic_string
 *  @see head
 *  @see tail
 *  @see next
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Size>
struct skip_front
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : String
{ };
#endif

/// Metafunction returning a sub-string without the first N characters
/**
 *  @see basic_string
 *  @see head_c
 *  @see tail_c
 *  @see next
 *
 *  @ingroup ct_utils
 */
template <typename Range, size_t Count>
struct skip_front_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : String
{ };
#endif

/// Metafunction returning the element at the N-th position in a Range
/**
 *  @see basic_string
 *  @see head
 *  @see front
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Position>
struct at
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : CharacterConstantType
{ };
#endif

/// Metafunction returning the character at the N-th position
/**
 *  @see basic_string
 *  @see head_c
 *  @see front
 *
 *  @ingroup ct_utils
 */
template <typename Range, size_t Position>
struct at_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : CharacterConstantType
{ };
#endif

/// Metafunction returning true_type if the Range starts with a sub-range
/**
 *  @see basic_string
 *  @see head
 *  @see equal
 *  @see contains
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct starts_with
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : BooleanConstantType
{ };
#endif


/// Metafunction returning true_type if the Range ends with a sub-range
/**
 *  @see basic_string
 *  @see tail
 *  @see equal
 *  @see contains
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct ends_with
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : BooleanConstantType
{ };
#endif

/// Metafunction returning true_type if the a Range contains a sub-range
/**
 *  @see range
 *  @see basic_string
 *  @see equal
 *  @see lacks
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct contains
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : BooleanConstantType
{ };
#endif

/// Metafunction that reverses the elements in a Range
/**
 *  @see range
 *  @see basic_string
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct reverse
#ifndef MIRROR_DOCUMENTATION_ONLY
 : reverse<typename evaluate<Range>::type>
#else
 : Range
#endif
{ };

/// Metafunction returns true_type if the Range does not contain a sub-range
/**
 *  @see range
 *  @see basic_string
 *  @see equal
 *  @see contains
 *
 *  @ingroup ct_utils
 */
template <typename Range1, typename Range2>
struct lacks
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
 : BooleanConstantType
{ };
#endif

/// Returns a Range with the duplicities removed
/**
 *  @tparam Range the range to be filtered
 *
 *  @ingroup ct_utils
 */
template <typename Range>
struct unique
#ifndef MIRROR_DOCUMENTATION_ONLY
 : unique<typename evaluate<Range>::type>
#else
 : Range
#endif
{ };

/// Calls a nested metafunction with a pack <0,1,2, ... N-1> of ints
/** This template assembles a pack of integral non-type template parameters
 *  which form a sequence of 0, 1, 2, ... , N-1 and calls the metafunction
 *  called apply nested in the MetaFunctionClass, passing the pack as
 *  parameters.
 *
 *  @tparam MetaFunctionClass a class containing a nested template called
 *  apply which can take @a N integral template parameters having
 *  typedef called "type".
 *  @param N the count of arguments for the metafunction.
 *
 *  @see apply_on_seq_pack
 *  @ingroup ct_utils
 */
template <typename MetaFunctionClass, size_t N>
struct apply_on_seq_pack_c
#ifndef MIRROR_DOCUMENTATION_ONLY
;
#else
{
	/// The result of the metafunction with the <0,1,2,...,N-1> params
	/** This type is the result of the following expression
	 *  @verbatim
	 *  typename MetaFunctionClass:: template apply<
	 *      0, 1, 2, ..., N-1
	 *  >::type
	 *  @endverbatim
	 */
	typedef unspecified_type type;
};
#endif

/// Calls a nested metafunction with a pack <0,1,2, ... N-1> of ints
/** This template assembles a pack of integral non-type template parameters
 *  which form a sequence of 0, 1, 2, ... , N-1 and calls the metafunction
 *  called apply nested in the MetaFunctionClass, passing the pack as
 *  parameters.
 *
 *  @tparam MetaFunctionClass a class containing a nested template called
 *  apply which can take @a N integral template parameters having
 *  typedef called "type".
 *  @param N an integral constant type providing the count of arguments for
 *  the metafunction.
 *
 *  @see apply_on_seq_pack
 *  @ingroup ct_utils
 */
template <typename MetaFunctionClass, typename N>
struct apply_on_seq_pack
#ifndef MIRROR_DOCUMENTATION_ONLY
 : public apply_on_seq_pack_c<MetaFunctionClass, N::value>
{ };
#else
{
	/// The result of the metafunction with the <0,1,2,...,N-1> params
	/** This type is the result of the following expression
	 *  @verbatim
	 *  typename MetaFunctionClass:: template apply<
	 *      0, 1, 2, ..., N-1
	 *  >::type
	 *  @endverbatim
	 */
	typedef unspecified_type type;
};
#endif

/// Invokes a metafunction-class or placeholder lambda expression.
/**
 *
 *  @tparam LambdaExpression the expression to be "called"
 *  @tparam Params the pack of params passed to the lambda expression
 *
 *  @ingroup ct_utils
 */
template <typename LambdaExpression, typename ... Params>
struct apply
#ifndef MIRROR_DOCUMENTATION_ONLY
 : LambdaExpression::template apply<Params...>
{ };
#else
{
	/// The result of the invocation of the expression with the params
	typedef unspecified type;
};
#endif

/// Invokes a metafunction-class or placeholder lambda expression.
/**
 *
 *  @tparam LambdaExpression the expression to be "called"
 *  @tparam Params the pack of params passed to the lambda expression
 *
 *  @ingroup ct_utils
 */
template <typename LambdaExpression, typename Char, Char ... Params>
struct apply_c
#ifndef MIRROR_DOCUMENTATION_ONLY
 : LambdaExpression::template apply_c<Char, Params...>
{ };
#else
{
	/// The result of the invocation of the expression with the params
	typedef unspecified type;
};
#endif

/// Returns a sub-range containing only elements satisfying a predicate
/**
 *  @tparam Range the range to be filtered
 *  @tparam Predicate a unary lambda expression returning a boolean type
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename Predicate>
struct only_if
#ifndef MIRROR_DOCUMENTATION_ONLY
 : only_if<typename evaluate<Range>::type, Predicate>
#else
 : Range
#endif
{ };

/// Returns a range containing elements transformed by a unary function
/** This metafunction returns a Range containing elements transformed
 *  by the UnaryMetaFnClass.
 *
 *  @tparam Range the range to be transformed
 *  @tparam UnaryMetaFnClass the metafunction class transforming the elements
 *
 *  @ingroup ct_utils
 */
template <typename Range, typename UnaryMetaFnClass>
struct transform
#ifndef MIRROR_DOCUMENTATION_ONLY
 : transform<typename evaluate<Range>::type, UnaryMetaFnClass>
#else
 : Range
#endif
{ };

/// Returns a String containing characters transformed by a unary function
/**
 *  @tparam String the string to be transformed
 *  @tparam UnaryMetaFnClass the metafunction class transforming the elements
 *
 *  @ingroup ct_utils
 */
template <typename String, typename UnaryMetaFnClass>
struct transform_c
#ifndef MIRROR_DOCUMENTATION_ONLY
 : transform_c<typename evaluate<String>::type, UnaryMetaFnClass>
#else
 : String
#endif
{ };

/// Returns the result of successive application of ForwardOp on a range
/** This metafunction returns the result of successive application
 *  of the binary forward operation on the status and all the items
 *  in the range passed as argument.
 *
 *  @tparam Range the range to traverse
 *  @tparam Status the initial status for the first call of the @a ForwardOp
 *  @tparam ForwardOp the operation to be executed during the traversal
 *
 *  @see for_each
 *  @ingroup ct_utils
 */
template <
	typename Range,
	typename Status,
	typename ForwardOp
> struct fold
#ifndef MIRROR_DOCUMENTATION_ONLY
 : fold<typename evaluate<Range>::type, Status, ForwardOp>
{ };
#else
{
	/// The result of the operation
	typedef unspecified_type type;
};
#endif

/// Zips the elements from the specified Range(s) into a single range
/** This metafunction creates a Range, containing the elements from
 *  all ranges passed as arguments.
 *
 *  @note At least one range must be specified, all ranges must have
 *  the same number of elements.
 *
 *  @ingroup ct_utils
 */
template <typename ... Ranges>
struct zip
#ifndef MIRROR_DOCUMENTATION_ONLY
 : zip<typename evaluate<Ranges>::type...>
#else
 : Range
#endif
{ };

} // namespace ct
} // namespace mire

#endif //include guard

