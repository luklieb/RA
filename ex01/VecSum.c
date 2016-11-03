
float vec_sum(float *A, int N){
	int i = 0;
	float sum = 0;
	#pragma novector
	#pragma nounroll
	for(i = 0; i < N; ++i){
		sum += A[i];
		//printf("%f sum, %d iter \n", sum, i);
	}
	return sum;
}

float vec_sum_2(float *A, int N){
        int i = 0;
        float sum1 = 0;
	float sum2 = 0;
	int left = N%2;
	int cond = N-left;
	
        #pragma novector
        #pragma nounroll
        for(i = 0; i < cond; i += 2){
                sum1 += A[i];
		sum2 += A[i+1];
        }
	sum1 += sum2;
        #pragma novector
        #pragma nounroll
	for(i = cond; i<N ; ++i){
		sum1 += A[i];
	}
	return sum1;
}

float vec_sum_3(float *A, int N){
        int i = 0;
        float sum1 = 0;
        float sum2 = 0;
	float sum3 = 0;
        int left = N%3;
        int cond = N - left;

        #pragma novector
        #pragma nounroll
        for(i = 0; i < cond; i += 3){
                sum1 += A[i];
                sum2 += A[i+1];
		sum3 = A[i+2];
        }
        sum1 = sum1 + sum2 + sum3;
        #pragma novector
        #pragma nounroll
        for(i = cond; i<N ; ++i){
                sum1 += A[i];
        }
	return sum1;
}

float vec_sum_4(float *A, int N){
        int i = 0;
        float sum1 = 0;
        float sum2 = 0;
	float sum3 = 0;
	float sum4 = 0;
        int left = N%4;
        int cond = N - left;

        #pragma novector
        #pragma nounroll
        for(i = 0; i < cond; i += 4){
                sum1 += A[i];
                sum2 += A[i+1];
		sum3 += A[i+2];
		sum4 += A[i+3];
        }
        sum1 = sum1 + sum2 + sum3 +sum4;;
        #pragma novector
        #pragma nounroll
        for(i = cond; i<N ; ++i){
                sum1 += A[i];
        }
	return sum1;
}

float vec_sum_8(float *A, int N){
        int i = 0;
        float sum1 = 0;
        float sum2 = 0;
	float sum3 = 0;
	float sum4 = 0;
	float sum5 = 0;
	float sum6 = 0;
	float sum7 = 0;
	float sum8 = 0;
        int left = N%8;
        int cond = N - left;

        #pragma novector
        #pragma nounroll
        for(i = 0; i < cond; i += 8){
                sum1 += A[i];
                sum2 += A[i+1];
		sum3 += A[i+2];
		sum4 += A[i+3];
		sum5 += A[i+4];
		sum6 += A[i+5];
		sum7 += A[i+6];
		sum8 += A[i+7];;
        }
        sum1 = sum1 + sum2 + sum3 + sum4 + sum5 +sum6 +sum7 + sum8;
        #pragma novector
        #pragma nounroll
        for(i = cond; i<N ; ++i){
                sum1 += A[i];
        }
	return sum1;
}
