
#define type double

void jacobi_vanilla(type * new, type * old, int x_size, int y_size){
	int x;
	int y;
	for(y = 1; y < y_size-1; ++y){
		for(x = 1; x < x_size-1; ++x){
			new[y*x_size + x] = 0.25*(old[(y+1)*x_size + x] + old[(y-1)*x_size + x] + old[y*x_size + x+1] + old[y*x_size + x-1]);
		}

	}
	




}
