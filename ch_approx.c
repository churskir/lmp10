#include "makespl.h"
#include "piv_ge_solver.h"
#include "ch_polynominals.h"

#include <float.h>


/* Zwraca n-tą potęgę a; zakłada, że n jest naturalne */
int nth_power(int a, int n) {
	int i;
	assert(n >= 0);
	int result = 1;
	for (i = 0; i < n; i++)
		result *= a;
	return result;
}

/* Zwraca sumę od 0 do n:
 *	 mode = 1: x^power
 *	 mode = 0: y * (x^power) */
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

/* Zwraca macierz gotową do eliminacji Gausa */
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

/* Oblicza wartość funkcji aproksumującej lub jej pochodnej (1., 2. lub 3.) dla x*/
double ch_approx(matrix_t *a; double x, int derivative) {
	double result = 0;
	int num_of_param = a->rn;
	int i;
	
	switch (derivative) {
		case 0:
			for (i = 0; i < num_of_param; i++)
				result += a->data[i] * T_n(i, x);
			break;
		case 1:
			for (i = 0; i < num_of_param; i++)
				result += a->data[i] * T_n_1(i, x);
			break;
		case 2:
			for (i = 0; i < num_of_param; i++)
				result += a->data[i] * T_n_2(i, x);
			break;
		case 3:
			for (i = 0; i < num_of_param; i++)
				result += a->data[i] * T_n_3(i, x);
			break;
		default:
				printf("Derivative not in {0, 1, 2, 3}\n");
				return -1;
			break;
	return result;
}

/* Wypełnia spl*/
void *fill_spl_ch(spline_t *spl, points_t *pts, matrix_t *mat) {
	int n = pts->n - 3 > 10 ? 10 : pts->n - 3;
	int i;
	double x = pts->x[0], d = (pts->x[n - 1] - pts->x[0]) / (spl->n - 1);
	char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		n = atoi( nbEnv );
		
	if (!alloc_spl(spl, nb)) {
		fun->n = n;
		for (i = 0; i < n; i++) {
			fun->x[i] = x;
			fun->f[i] = ch_approx(mat, x, 0);
			fun->f1[i] = ch_approx(mat, x, 1);
			fun->f2[i] = ch_approx(mat, x, 2);
			fun->f3[i] = ch_approx(mat, x, 3);
			x += d + 10.0 * DBL_EPSILON;
		}
	}
}

void make_spl(points_t *pts, spline_t *spl) {
	matrix_t *mat = fill_matrix(pts);
	spline_t *fun;
	double x;
	if (piv_ge_solver(mat))
		return EXIT_FAILURE;
		
	return fill_spl_ch(spl, pts, mat);	
}
