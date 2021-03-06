/*
 *  Copyright (c) 2019 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KISCPPQUIRKS_H
#define KISCPPQUIRKS_H

#include <type_traits>

namespace std {

// from C++14

#if __cplusplus < 201402L

template <typename Cont>
inline auto rbegin(Cont &cont) -> decltype(declval<Cont>().rbegin()) {
    return cont.rbegin();
}

template <typename Cont>
inline auto rend(Cont &cont) -> decltype(declval<Cont>().rend()) {
    return cont.rend();
}

template <class BidirectionalIterator>
inline reverse_iterator<BidirectionalIterator> make_reverse_iterator(BidirectionalIterator x)
{
    return reverse_iterator<BidirectionalIterator>(x);
}

template< bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;

template< bool B, class T, class F >
using conditional_t = typename conditional<B,T,F>::type;

template< class T >
using add_const_t    = typename add_const<T>::type;


#endif

// from C++17

#if __cplusplus < 201703L

template<typename...>
using void_t = void;

template <class T>
constexpr std::add_const_t<T>& as_const(T& t) noexcept
{
    return t;
}

template <class T>
void as_const(const T&&) = delete;

#endif

template <bool is_const, class T>
struct add_const_if
{
    using type = std::conditional_t<is_const, std::add_const_t<T>, T>;
};

template <bool is_const, class T>
using add_const_if_t = typename add_const_if<is_const, T>::type;

}

#endif // KISCPPQUIRKS_H
