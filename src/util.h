#pragma once

namespace util {

// Dzielenie z reszta
// Oblicza liczbe calkowita `n` tak ze:
// `lhs = n * rhs + rem_euclid(lhs, rhs)`
//
// //                               lhs      n    rhs  rem
// div_euclid( 7.0,  4.0) ==  1 //  7.0 ==  4.0 *  1 + 3.0
// div_euclid(-7.0,  4.0) == -2 // -7.0 ==  4.0 * -2 + 1.0
// div_euclid( 7.0, -4.0) == -1 //  7.0 == -4.0 * -1 + 3.0
// div_euclid(-7.0, -4.0) ==  2 // -7.0 == -4.0 *  2 + 1.0
float div_euclid(float, float);

// Oblicza reszte z dzielenia czyli `lhs (mod rhs)`.
// wartosc zwracana `r` spelnia zaleznosc `0.0 <= r <= abs(rhs)`
//
// rem_euclid( 7.0,  4.0) == 3.0
// rem_euclid(-7.0,  4.0) == 1.0
// rem_euclid( 7.0, -4.0) == 3.0
// rem_euclid(-7.0, -4.0) == 1.0
float rem_euclid(float, float);

}
