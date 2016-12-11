#include<immintrin.h>

#define type double

void jacobi_avx(type * new, type * old, int x_size, int y_size){
	int x;
	int y;
	__m256d old_n, old_s, old_w, old_e, constant, temp;
	constant = _mm256_set_pd(0.25, 0.25, 0.25, 0.25);
	
	for(y = 1; y < y_size-1; ++y){
		for(x = 1; x < x_size-4; x+=4){
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
