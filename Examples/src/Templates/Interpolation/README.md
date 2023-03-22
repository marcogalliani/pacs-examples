# An example of policy # 

We want to define a class, called `interp1D`
that parform the interpolation of a vector of values given the couple
`X`,`Y` of interpolation nodes and values. The type of interpolation is
implemented via a policy, that, given `X` and `Y` provides the method to
interpolate a single value at a given location `x`.

I have implemented Lagrange interpolation, using the classical
formula, which interpolates on the polynomial of degree n-1, being n
the number of interpolation nodes, Lagrange interpolation using the
Newton formula (which is slightly more stable) and piecewise linear
interpolation.

You can add other interpolators, if you wish!

# What do I learn here ? #
- Another use of a policy to provide a component that changes the behaviour of an algorithm.

