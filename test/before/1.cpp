#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>
#include <math.h>
#include <inttypes.h>

enum { m = 10000, n = 10000 };
/* dgemv: Compute matrix-vector product c[m] = a[m][n] * b[n] */
void dgemv(float *a, float *b, float *c, int m, int n)
{
for (int i = 0; i < m; i++) {
c[i] = 0.0;
for (int j = 0; j < n; j++)
c[i] += a[i * n + j] * b[j];
}
}

int main(int argc, char **argv)
{
	
double t = wtime();
float *a, *b, *c;
a = xmalloc(sizeof(*a) * m * n);
b = xmalloc(sizeof(*b) * n);
c = xmalloc(sizeof(*c) * m);
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++)
a[i * n + j] = i + 1;
}
for (int j = 0; j < n; j++)
b[j] = j + 1;
dgemv(a, b, c, m, n);
t = wtime() - t;
// Validation
for (int i = 0; i < m; i++) {
double r = (i + 1) * (n / 2.0 + pow(n, 2) / 2.0);
if (fabs(c[i] - r) > 1E-6) {
fprintf(stderr, "Validation failed: elem %d = %f (real value %f)\n", i, c[i], r); break;
}
}
double gflop = 2.0 * m * n * 1E-9;
printf("Elapsed time (serial): %.6f sec.\n", t);
printf("Performance: %.2f GFLOPS\n", gflop / t);
free(a); free(b); free(c);
return 0;
}
