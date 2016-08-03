/**
 *  @file mire/ct_counter.hpp
 *  @brief Implements compile-time counters
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_COUNTER_1401061342_HPP
#define MIRE_CT_COUNTER_1401061342_HPP

#include <mire/config.hpp>
#include <type_traits>

/** @defgroup ct_counter_macros Macros
 */

#ifndef MIRE_CT_COUNTER_LUID
#ifdef __COUNTER__
#define MIRE_CT_COUNTER_LUID __COUNTER__
#else
#define MIRE_CT_COUNTER_LUID __LINE__
#define MIRE_CT_COUNTER_UNRELIABLE
#endif
#endif

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Enables compile-time counters in the current namespace
/** To use the compile-time counters implemented by this library
 *  on the global-scope on in a namespace, the #MIRE_CT_COUNTER_ENABLE()
 *  macro must be used in that namespace before any other MIRE_CT_COUNTER_*
 *  macro.
 *
 *  @ingroup ct_counter_macros
 *
 *  @see #MIRE_CT_COUNTER_CREATE
 */
#define MIRE_CT_COUNTER_ENABLE()
#else
#define MIRE_CT_COUNTER_ENABLE() \
namespace ct_counter { \
\
struct null_ { }; \
typedef std::integral_constant<int, -1> initial; \
typedef std::integral_constant<int,  0> zero; \
\
template <class Selector> null_ get_next(Selector, ...); \
template <class Selector> zero get_next(Selector, initial);\
\
template <class Selector, class Value, int InstId> struct curr; \
\
template <class Selector, class Current, class Next, int InstId> \
struct next \
{ typedef typename curr<Selector, Next, InstId>::type type; }; \
\
template <class Selector, class Current, int InstId> \
struct next<Selector, Current, null_, InstId> \
{ typedef Current type; }; \
\
template <class Selector, class Value, int InstId> \
struct curr : next< \
	Selector, \
	Value, \
	decltype(get_next(Selector(), Value())), \
	InstId \
>::type { }; \
\
template <class T> struct sel;\
}
#endif // MIRROR_DOCUMENTATION_ONLY

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Creates a new compile-time counter in the current namespace
/** This macro creates a new compile-time counter identified by the @c SELECTOR
 *  type. The @c SELECTOR type must be defined prior to its use in the counter
 *  macros.
 *
 *  @note The compile-time counters must be enabled in the current namespace
 *  with the @c MIRE_CT_COUNTER_ENABLE macro before they can be created with
 *  @c MIRE_CT_COUNTER_CREATE.
 *
 *  @ingroup ct_counter_macros
 *
 *  @see #MIRE_CT_COUNTER_ENABLE
 *  @see #MIRE_CT_COUNTER_CURRENT
 *  @see #MIRE_CT_COUNTER_INCREMENT
 */
#define MIRE_CT_COUNTER_CREATE(SELECTOR)
#else
#define MIRE_CT_COUNTER_CREATE(SELECTOR) \
namespace ct_counter { \
template <> struct sel < SELECTOR > { }; \
} /* namespace ct_counter */
#endif // MIRROR_DOCUMENTATION_ONLY

// Helper macro used in implementation of MIRE_CT_COUNTER_CURRENT
#define MIRE_CT_COUNTER_CURRENT_COUNT(SELECTOR, LUID) \
	ct_counter::curr< \
		ct_counter::sel< SELECTOR >, \
		ct_counter::initial, \
		LUID \
	>::type

// Helper macro used for implementation of MIRE_CT_COUNTER_PREVIOUS
#define MIRE_CT_COUNTER_PREVIOUS_COUNT(SELECTOR, LUID) \
	std::integral_constant< \
		int, MIRE_CT_COUNTER_CURRENT_COUNT(SELECTOR, LUID)::value-1 \
	>


// Helper macro used in implementation of MIRE_CT_COUNTER_INCREMENT
#define MIRE_CT_COUNTER_INCREMENT_COUNTER(SELECTOR, LUID) \
namespace ct_counter { \
	std::integral_constant< \
		int, curr< sel< SELECTOR >, initial, LUID >::value+1 \
	> get_next( \
		sel< SELECTOR >, \
		curr< sel< SELECTOR >, initial, LUID >::type \
	); \
} /* namespace ct_counter */

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns the current value of the counter identified by the @c SELECTOR
/** This macro expands into an @c integral_constant<int, ...> with the current
 *  value of the counter identified by the @c SELECTOR type. The counter
 *  must be created with the #MIRE_CT_COUNTER_CREATE macro before
 *  #MIRE_CT_COUNTER_CURRENT can be used.
 *
 *  @ingroup ct_counter_macros
 *
 *  @see #MIRE_CT_COUNTER_CREATE
 *  @see #MIRE_CT_COUNTER_INCREMENT
 */
#define MIRE_CT_COUNTER_CURRENT(SELECTOR)
#else
#define MIRE_CT_COUNTER_CURRENT(SELECTOR) \
	MIRE_CT_COUNTER_CURRENT_COUNT( \
		SELECTOR, \
		MIRE_CT_COUNTER_LUID \
	)
#endif // MIRROR_DOCUMENTATION_ONLY

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns the previous value of the counter identified by the @c SELECTOR
/** This macro expands into an @c integral_constant<int, ...> with the previous
 *  value of the counter identified by the @c SELECTOR type. The counter
 *  must be created with the #MIRE_CT_COUNTER_CREATE macro before
 *  #MIRE_CT_COUNTER_CURRENT can be used.
 *
 *  @ingroup ct_counter_macros
 *
 *  @see #MIRE_CT_COUNTER_CREATE
 *  @see #MIRE_CT_COUNTER_INCREMENT
 */
#define MIRE_CT_COUNTER_PREVIOUS(SELECTOR)
#else
#define MIRE_CT_COUNTER_PREVIOUS(SELECTOR) \
	MIRE_CT_COUNTER_PREVIOUS_COUNT( \
		SELECTOR, \
		MIRE_CT_COUNTER_LUID \
	)
#endif // MIRROR_DOCUMENTATION_ONLY

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Increments the value of the counter identified by the @c SELECTOR
/** This macro increments the value of the counter identified by the @c SELECTOR
 *  type. The countermust be created with the #MIRE_CT_COUNTER_CREATE macro
 *  before #MIRE_CT_COUNTER_INCREMENT can be used.
 *
 *  @ingroup ct_counter_macros
 *
 *  @see #MIRE_CT_COUNTER_CREATE
 */
#define MIRE_CT_COUNTER_INCREMENT(SELECTOR)
#else
#define MIRE_CT_COUNTER_INCREMENT(SELECTOR) \
	MIRE_CT_COUNTER_INCREMENT_COUNTER(SELECTOR, MIRE_CT_COUNTER_LUID)
#endif

#endif //include guard

