#include "chebyshev.h"

/* returns n-th power of a; n in natural */
int nth_power(int a, int n)
{
	int i;
	assert(n >= 0);
	int result = 1;
	for (i = 0; i < n; i++)
		result *= a;
	return result;
}

/* returns sum from 0 to n of:
 *	 mode 1: x^power
 *	 mode 0: y * (x^power) */
int sum_ch(points_t *pts, int mode, int power) {
	double result = 0;
	int pts_amount = pts->n + 1;
	int i;
	
	for (i = 0; i < pts_amount; i++)
	{
		if (mode)
			result += nth_power(pts->x[i], power) * pts->y[i];
		else
			result += nth_power(pts->x[i], power);
	}		
	return result;
}

matrix_t *fill_matrix_A(points_t *pts) {
	int i, j;
	int pts_amount = pts->n + 1;
	matrix_t A = make_matrix(pts_amount, pts_amount);
	for (i = 0; i < pts_amount; i++)
	  for (j = 0; j < pts_amount; i++)
		  A->data[i * pts_amount + j] = sum_ch(pts, 1, 2 * pts_amount -
																  i - j)
	return A;
}

matrix_t *fill_matrix_b() {
	int i;
	int pts_amount = pts->n + 1;
	matrix_t b = make_matrix(pts_amount, 1);
	for (i = 0; i < pts_amount; i++)
	  A->data[i] = sum_ch(pts, 0, pts_amount - i - 1);
	return b;
}

void chebyshev(int n, points_t *pts_in, points_t *pts_out) {
	matrix_t *A = fill_matrix_A(pts_in);
	matrix_t *b = fill_matrix_b(pts_in);
	matrix_t *a = ELIMINACJA_GAUSA_GDZIEKOLWIEK_ONA_JEST(A, b);
}
