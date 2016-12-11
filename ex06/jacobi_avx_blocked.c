#include<immintrin.h>

#define type double
#define MIN(a,b) (((a)<(b))?(a):(b))

void jacobi_avx_blocked(type * new, type * old, const int x_size, const int y_size){
	int x;
	int y;
	int bx;
	int by;

	__m256d old_n, old_s, old_w, old_e, constant, temp;
	constant = _mm256_set1_pd(0.25);

	for(by = 1; by < y_size; by+=BY){
		for(bx = 1; bx < x_size; bx+=BX){
			for(y = by; y < MIN(y_size-1, (by+BY)); ++y){
				for(x = bx; x < MIN(x_size-4, (bx+BX)); x+=4){
					old_n = _mm256_loadu_pd(old+((y+1)*x_size + x));
					old_s = _mm256_loadu_pd(old+((y-1)*x_size + x));
					old_e = _mm256_loadu_pd(old+(y*x_size + x+1));
					old_w = _mm256_loadu_pd(old+(y*x_size + x-1));
					temp = _mm256_add_pd(old_n, old_s);
					temp = _mm256_add_pd(temp, old_w);
					temp = _mm256_add_pd(temp, old_e);
					temp = _mm256_mul_pd(temp, constant);
					_mm256_storeu_pd(new+(y*x_size+x), temp);
				}	
			}
		}
	}
}
