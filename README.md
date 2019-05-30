# Egyptian Form

In the article titled "An Algebraic Algorithm for the Representation Problems of the Ahmes Papyrus," by Solomon W. Golomb, *American Mathematical Monthly*, Vol. 69, 1962, an algorithm was described which gives the so-called **Egyptian form** for a fraction.

**Definition** An *Egyptian form* for a fraction p/q with integers 0 < p < q is a sum of reciprocals of distinct positive integers, that is,
```math
\frac{p}{q} = \frac{1}{n_{1}} + \cdots + \frac{1}{n_{k}}.
```

The algorithm described by Golomb puts the fraction into lowest terms so that gcd(p,q) = 1, that way p has an inverse p' modulo q. Then, there exists an integer r such that pp' = qr + 1. Then, we get
```math
\frac{p}{q} = \frac{qr + 1}{p'q} = \frac{1}{p'q} + \frac{r}{p'}.
```

Since 0 < r < min(p,p') and p' < q, this process can be iterated on r/p' and will eventually end.