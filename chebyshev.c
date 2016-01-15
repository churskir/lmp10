#include "chebyshev.h"

/* returns n-th power of a; n in natural */
int nth_power(int a, int n) {
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
	
	for (i = 0; i < pts_amount; i++) {
		if (mode)
			result += nth_power(pts->x[i], power) * pts->y[i];
		else
			result += nth_power(pts->x[i], power);
	}		
	return result;
}

matrix_t *fill_matrix(points_t *pts) {
	int i, j;
	int pts_amount = pts->n + 1;
	matrix_t mat = make_matrix(pts_amount, pts_amount + 1);
	for (i = 0; i < pts_amount; i++)
	  for (j = 0; j < pts_amount; i++)
		  mat->data[i * (pts_amount + 1) + j] = sum_ch(pts, 1, 2 * pts_amount -
																          i - j)
	  mat->data[i * (pts_amount + 1) + j] = sum_ch(pts, 0, pts_amount - i - 1);
	return mat;
}

double ch_polynominal(int n, double x) {
	assert(n >= 0);
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	return 2 * x * ch_polynominal(n - 1, x) - ch_polynominal(n - 2, x);
}

double ch_approx(matrix_t *a; double x) {
	double result = 0;
	int num_of_par = a->rn;
	int i;
	
	for (i = 0; i < num_of_par; i++)
		result += a->data[i] * ch_polynominal(i, x);

	return result;
}

points_t *generate_output_set(int n, double from, double to, points_t *pts_in, matrix_t *mat) {
	int index = 0;
	double i;
	double d = (to - from) / (n - 1);
	points_t *pts_out;
	pts_out->n = n;
	pts_out->x = malloc(n * sizeof(double));
	pts_out->y = malloc(n * sizeof(double));
	
	for (i = from; i <= to; i += d) {
		pts_out->x[index] = i;
		pts_out->y[index] = ch_approx(a, i);
	}
}

void chebyshev(int n, points_t *pts_in, points_t *pts_out) {
	matrix_t *mat = fill_matrix(pts_in);
	if (piv_ge_solver(mat))
		return EXIT_FAILURE;
	pts_out = generate_output_set(n, from, to, pts_in, mat);
}
