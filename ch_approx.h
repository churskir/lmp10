#include "points.h"
#include "matrix.h"
#include "piv_ge_solver.h"
#include "splines.h"
#include "ch_polynominals.h"

/* Zwraca zmienną typu spline_t zawiarającą informacje o funkcji aproksymującej zbiór punktów in */
spline_t *ch_approx(int n, points_t *in);
