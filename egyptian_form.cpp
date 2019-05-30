/*
MIT License

Copyright (c) 2019 Math Nerd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <algorithm>
#include <iostream>
#include <vector>

#include <NTL/ZZ.h>

NTL::ZZ string_to_ZZ(std::string const &str);

int main(int argc, char **argv)
{
    NTL::ZZ numerator  { 12345 };
    NTL::ZZ denominator{ 99999 };

    if( argc > 1 )
    {   // If there is an argument, handle it.
        switch( argc )
        {
            default:
            {   // Final argument should be denominator.
                denominator = string_to_ZZ(argv[argc - 1]);
            }
            [[fallthrough]];

            case 2:
            {
                std::string digits{ argv[1] };

                auto slash = digits.find('/');

                if( slash != std::string::npos && slash != digits.length() - 1 )
                {   // If argument is fraction, p/q, handle each.
                    std::string numer_digits{ digits.substr(0, slash) };
                    std::string denom_digits{ digits.substr(slash+1, digits.length()) };

                    numerator   = string_to_ZZ(numer_digits);
                    denominator = string_to_ZZ(denom_digits);
                }
                else
                {   // Otherwise, arguments are separate numerator and (optionally) denominator.
                    numerator = string_to_ZZ(digits);
                }

                break;
            }
        }
    }
    
    if( numerator <= 0 || numerator >= denominator )
    {   // Fraction must be of the form p/q with 0 < p < q.
        std::cout << "Error: Numerator must be positive and strictly less than the denominator.\n\n";

        std::cout << "Usage: " << argv[0] << " [numerator] [denominator]\n";
        std::cout << "or:    " << argv[0] << " [numerator]/[denominator]\n";

        return EXIT_FAILURE;
    }

    // Start output
    std::cout << numerator << "/" << denominator << " = ";

    if( NTL::ZZ gcd{ NTL::GCD(numerator, denominator) }; gcd > 1 )
    {   // Reduce fraction to simplest form.
        numerator   /= gcd;
        denominator /= gcd;

        if( numerator != 1 )
        {   // If reduced fraction has 1 as numerator, output will be below.
            std::cout << numerator << "/" << denominator << " = ";
        }
    }

    if( numerator == 1 )
    {   // If reduced fraction has 1 as numerator, it is already in Egyptian form.
        std::cout << numerator << "/" << denominator << '\n';
        return EXIT_SUCCESS;
    }

    // Hold denominators in 
    std::vector<NTL::ZZ> egyptian_denominators;

    // Algorithm end condition within body.
    while( true )
    {
        NTL::ZZ numerator_inverse, quotient;

        // Let p' be the inverse of p modulo q, and r = floor(pp'/q).
        // Then, p/q = (qr + 1)/(p'q) = 1/(p'q) + r/p'.
        // numerator = p, denominator = q

        numerator_inverse = NTL::InvMod(numerator, denominator); // p'
        quotient = numerator * numerator_inverse / denominator;  // r

        egyptian_denominators.push_back(numerator_inverse * denominator); // p'q

        // Repeat algorithm on r/p'
        numerator   = quotient;
        denominator = numerator_inverse;

        if( numerator == 1 )
        {   // Final denominator.
            egyptian_denominators.push_back(denominator);
            break;
        }
    }

    std::cout << "\n\n";

    // Technically, Egyptian form is a sum of reciprocals in decreasing order (increasing denominators).
    // The algorithm finds them in reverse, so we display egyptian_denominators in reverse.
    for( auto it = egyptian_denominators.rbegin(); it != egyptian_denominators.rend(); ++it )
    {
        if( it != egyptian_denominators.rbegin() )
        {
            std::cout << "+ ";
        }
        else
        {
            std::cout << "  ";
        }
        std::cout << "1/" << *it << '\n';
    }

    std::cout << '\n';

    return EXIT_SUCCESS;
}

/** \fn NTL::ZZ string_to_ZZ(std::string const &str)
    \brief Standard string to integer function, but for arbitrarily large integers.
 */
NTL::ZZ string_to_ZZ(std::string const &str)
{
    auto digits{ str.length() };

    NTL::ZZ number{ 0 };

    for( size_t idx{ 0 }; idx < digits; ++idx )
    {
        if( str[idx] >= '0' && str[idx] <= '9' )
        {
            number *= 10;
            number += str[idx] - '0';
        }
    }

    return number;
}
