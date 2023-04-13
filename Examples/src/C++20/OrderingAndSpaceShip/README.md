# Ordering relations and the new spaceship operator #

C++20 has extended relational operators also to other standard types, in particular containers like `std::vector`. Now you can natively use all 6 relational operators (4 comparison operators: `<`, `<=`, '>', '>=') and 2 equivalence/inequivalence operators (`==`, `!=`) on standard vectors. They compare the vector elements lexicographically. It is required that the vector elements be themselves comparable!.

But, we have some other important additions.

- The relational operators '<,<=,>, >=,==' can be declared as *default*. For instance, either adding in the public section of you class `T`:

	friend bool operator (T const &, T const &)==default;
	
which defaults the funcional version, or

	bool operator(T const &) const=default;
which defaults the member version.

In both cases, the compiler will add both `==` and `!=` operators by applying the same operator to all non-static members of the class, in the order of their declaration. In the case of a derived class, the members of the base are compared first. In the case of comparison operators, the comparison is made lexicographycally.

- You can define a defaulted *spaceship operator* (`<=>`):

	friend auto operator <=> (T const &, T const &)=default;
(or the equivalent member version). This way, the compiler generates the full set of relational operators, again by operating  on the class members in turn (in the order of declaration), with a lexicograpical procedure in the case of comparisons. The spaceship operator returns an **ordering**, a special class that represents a particular ordering relation (see below). Here, the use of `auto` will spare the hassle of identifying the return type precisely.

## The spaceship operator and ordering relations ##

C++20 has tried to clarify some issues that may arise when defining ordering relation. Indeed, it has introduced the concepts of *strong*, *weak* and *partial* ordering, which roughly corresponds to the mathematical definitions.

- *strong ordering* In a strong ordered collection any two elements of the collection are comparable, and we have `a<b -> ~(b<a)`, `a<b && b<c -> a<c`, `a<b -> b>a` and  the equivalence relation `==` is such that if `a==b` then `f(a)==f(b)` for any pure function `f`. In other words, in a strong ordering two equivalent elements are indistinguishable, at least with respect to the components that are involved in the comparison process. For instance, the default ordering relation on integers is strong. 
- *weak ordering* Like strong ordering, but equivalent objects can be distinguisheable. For instance, the rational number `2/3` is equivalent to `4/6` and indeed I can define an equivalence operator for which `a=2/3` and `b=4/6` are equivalent (`a==b` returns `true`). But the two objects are distinguisheable, for instance by creating a function `f` that extracts the numerator: `f(a)==f(b)`  is in this case `false`.
- *partial ordering*. In a partial ordering two elements may be incomparable. For comparable elements, the ordering satisfies the same properties of a weak ordering. Example of partial ordering is an ordering relation among nodes of a binary tree for which node `b` is *less-than* node `a` if it is a direct descendant. Two nodes on different tree branches are not comparable.  

The spaceship operator `<=>` may be used to disambiguate the type of ordering whenever necessary. See some examples in the given source file.

Note that if you ** define ** the spaceship operator (a differnt case that when you default it) you have to return an object of the correct ordering type. Moreover, while the comparison operators are then provided automatically, where `a<b` is equivalent to `(a<=>b)<0`, and `a>b` is equivalent to `(a<=>b)>0` and so on, operators `==` and `!=` are not given automatically, since the user should disambiguate. You have instead the functions `std::is_eq` and `std::is_neq` that take in input the output of `<=>`. Indeed, `std::eq(a<=>b)=true` iff `(a<=>b)==0`. If you want, you can define the `==` and `!=` operators consistently or maybe you want to do something different, as shown in the example. C++ thus allows you to keep separate comparison and equivalence if you want.

More information on [cppreference.com](https://en.cppreference.com/w/cpp/language/default_comparisons).

# What do I learn here? #
- A more complete way of defining relational operators in c++ code;
- The new way C++ treats relational operators;
- The spaceship operator `<=>`.






 