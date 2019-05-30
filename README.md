# Egyptian Form

In the article titled "An Algebraic Algorithm for the Representation Problems of the Ahmes Papyrus," by Solomon W. Golomb, *American Mathematical Monthly*, Vol. 69, 1962, an algorithm was described which gives a so-called **Egyptian form** for a fraction.

**Definition** An *Egyptian form* for a fraction p/q with integers 0 < p < q is a sum of reciprocals of distinct positive integers, that is,
```math
\frac{p}{q} = \frac{1}{n_{1}} + \cdots + \frac{1}{n_{k}}.
```

The algorithm described by Golomb puts the fraction into lowest terms so that gcd(p,q) = 1, that way p has an inverse p' modulo q. Then, there exists an integer r such that pp' = qr + 1. Then, we get
```math
\frac{p}{q} = \frac{qr + 1}{p'q} = \frac{1}{p'q} + \frac{r}{p'}.
```

Since 0 < r < min(p,p') and p' < q, this process can be iterated on r/p' and will eventually end.

This project uses the [Number Theory Library](https://shoup.net/ntl/).

Example usage:
```
./egyptian_form 97/719113371917
97/719113371917 =

  1/7413539917
+ 1/219842296396395927639
+ 1/1538896074715463174139
+ 1/3847240186762710545639
+ 1/7144874632538138042139
+ 1/11431799412041745663639
+ 1/16708014525273533410139
+ 1/22973519972233501281639
+ 1/30228315752921649278139
+ 1/38472401867337977399639
+ 1/47705778315482485646139
+ 1/57928445097355174017639
+ 1/69140402212956042514139
+ 1/81341649662285091135639
+ 1/94532187445342319882139
+ 1/108712015562127728753639
+ 1/123881134012641317750139
+ 1/140039542796883086871639
+ 1/157187241914853036118139
+ 1/175324231366551165489639
+ 1/194450511151977474986139
+ 1/214566081271131964607639
+ 1/235670941724014634354139
+ 1/257765092510625484225639
+ 1/280848533630964514222139
+ 1/304921265085031724343639
+ 1/329983286872827114590139
+ 1/356034598994350684961639
+ 1/383075201449602435458139
+ 1/411105094238582366079639
+ 1/440124277361290476826139
+ 1/470132750817726767697639
+ 1/501130514607891238694139
```