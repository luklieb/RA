#include<immintrin.h>

#define type double
#define BLOCK 5000
#define MIN(a,b) (((a)<(b))?(a):(b))

void jacobi_avx_blocked_1d(type * new, type * old, const int x_size, const int y_size){
	int x;
	int y;
	int b;


	__m256d old_n, old_s, old_w, old_e, constant, temp;
	constant = _mm256_set1_pd(0.25);

	//if (block_size < x_size){
		for(b = 0; b < x_size; b+=BX){
			for(y = 1; y < y_size-1; ++y){
				for(x = b+1; x < MIN(x_size-4,(b+BX)); x+=4){
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
	/*
		//printf("letzter Block b: %d \n", b);
		//letzer Block left over
		for(y = 1; y < y_size-1; ++y){
			for(x = b; x < x_size-4; x+=4){
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
	}else{
		//printf("nicht geblockte Version!!!\n");
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
	*/
}
