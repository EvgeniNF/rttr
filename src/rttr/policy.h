/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014, 2015 Axel Menzel <info@axelmenzel.de>                       *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#ifndef RTTR_POLICY_H_
#define RTTR_POLICY_H_

#include "rttr/detail/base/core_prerequisites.h"
#include "rttr/detail/misc/misc_type_traits.h"

namespace rttr
{

namespace detail
{

struct return_as_ptr
{};

struct set_as_ptr
{};

struct return_as_copy
{};

struct read_only
{};

struct set_value
{};

struct discard_return
{};

struct default_invoke
{};

/////////////////////////////////////////////////////////////////////////////////////////

// default getter policy
template<typename T>
struct get_getter_policy
{
    typedef return_as_copy type; 
};

// default setter policy
template<typename T>
struct get_setter_policy
{
    typedef set_value type; 
};

/////////////////////////////////////////////////////////////////////////////////////////

struct bind_property_as_ptr_policy
{};

struct return_reference_as_ptr_policy
{};

struct discard_return_value_policy
{};

/////////////////////////////////////////////////////////////////////////////////////////

template<typename... T>
struct policy_list_impl {};

using policy_list = policy_list_impl<bind_property_as_ptr_policy, 
                                     return_reference_as_ptr_policy, 
                                     discard_return_value_policy>;

/////////////////////////////////////////////////////////////////////////////////////////

template<>
struct get_getter_policy<bind_property_as_ptr_policy>
{
    typedef return_as_ptr type;
};

template<>
struct get_setter_policy<bind_property_as_ptr_policy>
{
    typedef set_as_ptr type;
};

/////////////////////////////////////////////////////////////////////////////////////////

// default method policy
template<typename T>
struct get_method_policy
{
    typedef default_invoke type; 
};

/////////////////////////////////////////////////////////////////////////////////////////


template<>
struct get_method_policy<return_reference_as_ptr_policy>
{
    typedef return_as_ptr type;
};

/////////////////////////////////////////////////////////////////////////////////////////

template<>
struct get_method_policy<discard_return_value_policy>
{
    typedef discard_return type;
};

/////////////////////////////////////////////////////////////////////////////////////////

using method_policy_list    = type_list<discard_return_value_policy, return_reference_as_ptr_policy>;
using property_policy_list  = type_list<return_reference_as_ptr_policy, bind_property_as_ptr_policy, read_only>;
using ctor_policy_list      = type_list<>;

} // end namespace detail;

/*!
 * The \ref policy class contains all policies that can be used during the registration of reflection information.
 *
 * \code{.cpp}
 *
 *  registration::method("test", &func_1)
 *  (
 *       policy::discard_return_value
 *  );
 *
 * \endcode
 */
struct RTTR_API policy
{
    /*!
     * Add documentation here
     */
    static const detail::bind_property_as_ptr_policy        bind_property_as_ptr;

    /*!
     * Add documentation here
     */
    static const detail::return_reference_as_ptr_policy     return_reference_as_ptr;

    /*!
     * Add documentation here
     */
    static const detail::discard_return_value_policy        discard_return_value;
};

} // end namespace rttr

#endif // RTTR_POLICY_H_
