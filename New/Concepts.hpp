#include <iterator>

// The Iterator_type function returns the iterator type of a Range, the
// type resulting from a call to std::begin.
template<typename R>
using Iterator_type = decltype(std::begin(std::declval<R&>()));

template<typename T, typename U>
concept bool Same() {
    return std::is_same<T,U>::value;
}

template<typename T>
concept bool Conditional()
{
  return requires(T t)
  {
    (bool)t;        // Explicitly convertible
  };
}

template<typename T>
concept bool 
Object_type() 
{ 
  return std::is_object<T>::value; 
}

template<typename T>
concept bool
Boolean()
{
  return Conditional<T>() && requires(T a, T b)
  {
    { !a } -> Same<bool>
    { a && b } -> Same<bool>;
    { a || b} -> Same<bool>;
  };
}

template<typename T>
concept bool
Equality_comparable() {
  return requires (T a, T b)
  {
    { a == b } -> Boolean;
    { a != b } -> Boolean;
  };
}

// The Sentinel type function returns the sentinel type of a Range, the
// type resuluting from a call to std::end. Note that this is not 
// required to be the same as a Range's Iterator_type.
template<typename R>
using Sentinel_type = decltype(std::end(std::declval<R&>()));

using std::begin;
using std::end;

template<typename R>
concept bool Range()
{
  return requires (R& range) 
  {
    typename Iterator_type<R>;
    typename Sentinel_type<R>;
    { begin(range) } -> Iterator_type<R>;
    { end(range) } -> Sentinel_type<R>;
  };
}

template<typename S>
concept bool Sequence() {
    return requires(S seq){
        { seq.front() } -> const typename S::value_type&;
        { seq.back() } -> const typename S::value_type&;
    };
}

template<typename T, typename U>
concept bool Same_as() {
    return std::is_same<T,U>::value;
}

// Is true if a variable of type T can be destroyed.
template<typename T>
concept bool
Destructible()
{
  // return std::is_destructible<T>::value;
  return requires (T* t) { t->~T(); };
}

// Is true if and only if an object of type T can be constructed with
// the types of arguments in Args.
template<typename T, typename... Args>
concept bool
Constructible()
{
  return Destructible<T>() && std::is_constructible<T, Args...>::value;
}


// Is true if and only if an object of T can be default constructed.
//
// Note that default construction implies that an object of type T can
// also be default initialized. Types modeling this concept must ensure
// that any two default initialized objects must have the same value.
template<typename T>
concept bool
Default_constructible()
{
  return Constructible<T>();
}

// Is true if and only if an object of type T can be move constructed.
template<typename T>
concept bool
Move_constructible()
{
  return Constructible<T, T&&>();
}

// Is true if and only if an object of type T can be copy constructed.
template<typename T>
concept bool
Copy_constructible()
{
  return Move_constructible<T>() && Constructible<T, const T&>();
}

// Is true if and only if an argument of type T can be assigned a value
// of type U.
//
// Note that T is typically expected to be an lvalue reference type.
template<typename T, typename U>
concept bool
Assignable()
{
  return std::is_assignable<T, U>::value;
}


// Is true if and only if an object of type T can be move assigned.
template<typename T>
concept bool
Move_assignable()
{
  return Assignable<T&, T&&>();
}


// Is true if and only if an object of type T can be copy assigned.
template<typename T>
concept bool
Copy_assignable()
{
  return Move_assignable<T>() && Assignable<T&, const T&>();
}


// Is true if and only if T supports move semantics. The type T must
// be move constructible and move assignable.
template<typename T>
concept bool
Movable()
{
  return Move_constructible<T>() && Move_assignable<T>();
}


// Is true if and only if T supports copy semantics. The type T must
// be copy constructible and copy assignable.
template<typename T>
concept bool
Copyable()
{
  return Copy_constructible<T>() && Copy_assignable<T>();
}


// A type is a semiregular type if it is default constructible and
// copyable. Alternatively, a semiregular type is a regular type that
// is not equality comparable.
//
// The semiregular type represents types like C structures, which can
// be default constructed and copied, but have no default definition
// of equality.
template<typename T>
concept bool
Semiregular()
{
  return Default_constructible<T>() && Copyable<T>();
}


// A type `T` is regular when it is semiregular and equality comparable.
// Regular types can be used like most scalar types, although they
// are not guaranteed to be ordered (comparble with `<`).
template<typename T>
concept bool
Regular()
{
  return Semiregular<T>() && Equality_comparable<T>();
}

template<typename S>
concept bool Associative_container() {
    return 
    requires {
        typename S::key_type;
    } &&
    requires (S s, typename S::key_type k){
        { s.empty() } -> bool;
        { s.size() } -> int;
        { s.find(k) } -> typename S::iterator;
        { s.count(k) } -> int;
    };
}