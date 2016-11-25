
#include <stdio.h>
#include <stdlib.h>

#define type double

void draw_grid(type * grid, int x_size, int y_size, const char * name ){
	FILE* file = fopen( name , "w" );
	if( file == NULL )
	{
		fprintf(stderr, "file open");
	}
	type value;
	int r,g,b;
	fprintf( file, "P3\n%d %d\n255\n", x_size, y_size );
	
	int x;
	int y;
	for( y = 0; y < y_size; y++ )
	{
		for( x = 0; x < x_size; x++ )
		{
			value = grid[y*x_size+x];
			if( value >= 0.0f && value <= 0.25f )
			{
				r = 255;
				g = 255*4*value;
				b = 0;
			}else if( value > 0.25f && value <= 0.5f )
			{
				r = 255*2-255*4*value;
				g = 255;
				b = 0;
			}else if( value > 0.5f && value <= 0.75f )
			{
				r = 0;
				g = 255;
				b = 255*4*(value-0.5f);
			}else if ( value > 0.75f && value <= 1.0f){
				r = 0;
				g = 255-255*4*(value-0.75f);
				b = 255;
			}else{
				r = 0;
				g = 0;
				b = 0;
			}
			fprintf( file, "%d %d %d ", r, g, b );
		}
		fprintf( file, "\n" );
	}
	fclose( file );


}
