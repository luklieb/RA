#include<emmintrin.h>

#define type double

void jacobi_sse(type * new, type * old, int x_size, int y_size){
	int x;
	int y;
	__m128d old_n, old_s, old_w, old_e, constant, temp;
	constant = _mm_set_pd(0.25,0.25);
	
	for(y = 1; y < y_size-1; ++y){
		for(x = 1; x < x_size-2; x+=2){
			old_n = _mm_loadu_pd( &old[(y+1)*x_size + x] );
			old_s = _mm_loadu_pd( &old[(y-1)*x_size + x] );
			old_e = _mm_loadu_pd( &old[y*x_size + x+1] );
			old_w = _mm_loadu_pd( &old[y*x_size + x-1] );
			temp = _mm_add_pd(old_n, old_s);
			temp = _mm_add_pd(temp, old_w);
			temp = _mm_add_pd(temp, old_e);
			temp = _mm_mul_pd(temp, constant);
			_mm_storeu_pd( &new[y*x_size+x], temp);	
		}
	}
	
}
