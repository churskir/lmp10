#include "ch_polynominals.h"

double T_n(int n, double x) {
	assert(n >= 0);
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	return 2 * x * T_n(n - 1, x) - T_n(n - 2, x);
}

double T_n_1(int n, double x) {
	assert(n >= 0);
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return 2 * T_n(n - 1, x) + 2 * x * T_n_1(n - 1, x) - T_n_1(n - 2, x);
}

double T_n_2(int n, double x) {
	assert(n >= 0);
	if (n == 0)
		return 0;
	if (n == 1)
		return 0;
	return 4 * T_n_1(n - 1, x) + 2 * x * T_n_2(n - 1, x) - T_n_2(n - 2, x);
}

double T_n_3(int n, double x) {
	assert(n >= 0);
	if (n == 0)
		return 0;
	if (n == 1)
		return 0;
	return 6 * T_n_2(n - 1, x) + 2 * x * T_n_3(n - 1, x) - T_n_3(n - 2, x);
}
