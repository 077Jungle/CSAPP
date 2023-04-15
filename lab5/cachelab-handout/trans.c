/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
if (M == 32)
{
	int i, j, x1, x2, x3, x4, x5, x6, x7, x8, x, y;
	for (i = 0; i < N; i += 8)
		for (j = 0; j < N; j += 8)
		{
			if (i == j)
			{
				x=i;
				x1=A[x][j];x2=A[x][j+1];x3=A[x][j+2];x4=A[x][j+3];
				x5=A[x][j+4];x6=A[x][j+5];x7=A[x][j+6];x8=A[x][j+7];
 
				B[x][j]=x1;B[x][j+1]=x2;B[x][j+2]=x3;B[x][j+3]=x4;
				B[x][j+4]=x5;B[x][j+5]=x6;B[x][j+6]=x7;B[x][j+7]=x8;
 
				x1=A[x+1][j];x2=A[x+1][j+1];x3=A[x+1][j+2];x4=A[x+1][j+3];
				x5=A[x+1][j+4];x6=A[x+1][j+5];x7=A[x+1][j+6];x8=A[x+1][j+7];
 
				B[x+1][j]=B[x][j+1];B[x][j+1]=x1;
 
				B[x+1][j+1]=x2;B[x+1][j+2]=x3;B[x+1][j+3]=x4;
				B[x+1][j+4]=x5;B[x+1][j+5]=x6;B[x+1][j+6]=x7;B[x+1][j+7]=x8;
 
				x1=A[x+2][j];x2=A[x+2][j+1];x3=A[x+2][j+2];x4=A[x+2][j+3];
				x5=A[x+2][j+4];x6=A[x+2][j+5];x7=A[x+2][j+6];x8=A[x+2][j+7];
 
				B[x+2][j]=B[x][j+2];B[x+2][j+1]=B[x+1][j+2];
				B[x][j+2]=x1;B[x+1][j+2]=x2;B[x+2][j+2]=x3;
				B[x+2][j+3]=x4;B[x+2][j+4]=x5;B[x+2][j+5]=x6;B[x+2][j+6]=x7;B[x+2][j+7]=x8;
 
				x1=A[x+3][j];x2=A[x+3][j+1];x3=A[x+3][j+2];x4=A[x+3][j+3];
				x5=A[x+3][j+4];x6=A[x+3][j+5];x7=A[x+3][j+6];x8=A[x+3][j+7];
 
				B[x+3][j]=B[x][j+3];B[x+3][j+1]=B[x+1][j+3];B[x+3][j+2]=B[x+2][j+3];
				B[x][j+3]=x1;B[x+1][j+3]=x2;B[x+2][j+3]=x3;B[x+3][j+3]=x4;
				B[x+3][j+4]=x5;B[x+3][j+5]=x6;B[x+3][j+6]=x7;B[x+3][j+7]=x8;
 
				x1=A[x+4][j];x2=A[x+4][j+1];x3=A[x+4][j+2];x4=A[x+4][j+3];
				x5=A[x+4][j+4];x6=A[x+4][j+5];x7=A[x+4][j+6];x8=A[x+4][j+7];
 
				B[x+4][j]=B[x][j+4];B[x+4][j+1]=B[x+1][j+4];B[x+4][j+2]=B[x+2][j+4];B[x+4][j+3]=B[x+3][j+4];
				B[x][j+4]=x1;B[x+1][j+4]=x2;B[x+2][j+4]=x3;B[x+3][j+4]=x4;B[x+4][j+4]=x5;
				B[x+4][j+5]=x6;B[x+4][j+6]=x7;B[x+4][j+7]=x8;
 
				x1=A[x+5][j];x2=A[x+5][j+1];x3=A[x+5][j+2];x4=A[x+5][j+3];
				x5=A[x+5][j+4];x6=A[x+5][j+5];x7=A[x+5][j+6];x8=A[x+5][j+7];
 
				B[x+5][j]=B[x][j+5];B[x+5][j+1]=B[x+1][j+5];B[x+5][j+2]=B[x+2][j+5];B[x+5][j+3]=B[x+3][j+5];B[x+5][j+4]=B[x+4][j+5];
				B[x][j+5]=x1;B[x+1][j+5]=x2;B[x+2][j+5]=x3;B[x+3][j+5]=x4;B[x+4][j+5]=x5;B[x+5][j+5]=x6;
				B[x+5][j+6]=x7;B[x+5][j+7]=x8;
 
				x1=A[x+6][j];x2=A[x+6][j+1];x3=A[x+6][j+2];x4=A[x+6][j+3];
				x5=A[x+6][j+4];x6=A[x+6][j+5];x7=A[x+6][j+6];x8=A[x+6][j+7];
 
				B[x+6][j]=B[x][j+6];B[x+6][j+1]=B[x+1][j+6];B[x+6][j+2]=B[x+2][j+6];B[x+6][j+3]=B[x+3][j+6];
				B[x+6][j+4]=B[x+4][j+6];B[x+6][j+5]=B[x+5][j+6];
				B[x][j+6]=x1;B[x+1][j+6]=x2;B[x+2][j+6]=x3;B[x+3][j+6]=x4;B[x+4][j+6]=x5;B[x+5][j+6]=x6;
				B[x+6][j+6]=x7;B[x+6][j+7]=x8;
 
				x1=A[x+7][j];x2=A[x+7][j+1];x3=A[x+7][j+2];x4=A[x+7][j+3];
				x5=A[x+7][j+4];x6=A[x+7][j+5];x7=A[x+7][j+6];x8=A[x+7][j+7];
 
				B[x+7][j]=B[x][j+7];B[x+7][j+1]=B[x+1][j+7];B[x+7][j+2]=B[x+2][j+7];B[x+7][j+3]=B[x+3][j+7];
				B[x+7][j+4]=B[x+4][j+7];B[x+7][j+5]=B[x+5][j+7];B[x+7][j+6]=B[x+6][j+7];
				B[x][j+7]=x1;B[x+1][j+7]=x2;B[x+2][j+7]=x3;B[x+3][j+7]=x4;B[x+4][j+7]=x5;B[x+5][j+7]=x6;B[x+6][j+7]=x7;
				B[x+7][j+7]=x8;
			}
				
			else
			{
				for(x = i; x < (i + 8); ++x)
					for(y = j; y < (j + 8); ++y)
						B[y][x] = A[x][y];
			}
		}
}
    else if(M==64)
    {
        int x5, x6, x7, x8, x, y, i, j;
        for(i=0;i<4*8;i+=8)
        {
            // misses A4+B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i+8+y]=A[i+y][i+x];
                    B[i+x][i+12+y]=A[i+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i+16+y]=A[i+y+4][i+x];
                    B[i+x][i+20+y]=A[i+y+4][i+4+x];
                }
            // misses B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+y][i+x]=B[i+y][i+8+x];
                    B[i+y][i+4+x]=B[i+y][i+16+x];
                }
            // misses B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+4+y][i+x]=B[i+y][i+12+x];
                    B[i+4+y][i+4+x]=B[i+y][i+20+x];
                }
            // misses A4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i+8+y]=A[i+8+y][i+x];
                    B[i+x][i+12+y]=A[i+8+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
            {
                x5=B[i+y][i+12];x6=B[i+y][i+13];x7=B[i+y][i+14];x8=B[i+y][i+15];
                B[i+y][i+12]=A[i+12][i+y];B[i+y][i+13]=A[i+13][i+y];B[i+y][i+14]=A[i+14][i+y];B[i+y][i+15]=A[i+15][i+y];
                B[i+4+y][i+8]=x5;B[i+4+y][i+9]=x6;B[i+4+y][i+10]=x7;B[i+4+y][i+11]=x8;

            }
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                    B[i+4+y][i+12+x]=A[i+12+x][i+4+y];
            // misses A4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i+16+y]=A[i+16+y][i+x];
                    B[i+x][i+20+y]=A[i+16+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
            {
                x5=B[i+y][i+20];x6=B[i+y][i+21];x7=B[i+y][i+22];x8=B[i+y][i+23];
                B[i+y][i+20]=A[i+20][i+y];B[i+y][i+21]=A[i+21][i+y];B[i+y][i+22]=A[i+22][i+y];B[i+y][i+23]=A[i+23][i+y];
                B[i+4+y][i+16]=x5;B[i+4+y][i+17]=x6;B[i+4+y][i+18]=x7;B[i+4+y][i+19]=x8;

            }
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                    B[i+4+y][i+20+x]=A[i+20+x][i+4+y];
        }
        for(i=4*8;i<8*8;i+=8)
        {
            // misses A4+B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i-8+y]=A[i+y][i+x];
                    B[i+x][i-4+y]=A[i+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i-16+y]=A[i+y+4][i+x];
                    B[i+x][i-12+y]=A[i+y+4][i+4+x];
                }
            // misses B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+y][i+x]=B[i+y][i-8+x];
                    B[i+y][i+4+x]=B[i+y][i-16+x];
                }
            // misses B4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+4+y][i+x]=B[i+y][i-4+x];
                    B[i+4+y][i+4+x]=B[i+y][i-12+x];
                }
            // misses A4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i-8+y]=A[i-8+y][i+x];
                    B[i+x][i-4+y]=A[i-8+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
            {
                x5=B[i+y][i-4];x6=B[i+y][i-3];x7=B[i+y][i-2];x8=B[i+y][i-1];
                B[i+y][i-4]=A[i-4][i+y];B[i+y][i-3]=A[i-3][i+y];B[i+y][i-2]=A[i-2][i+y];B[i+y][i-1]=A[i-1][i+y];
                B[i+4+y][i-8]=x5;B[i+4+y][i-8+1]=x6;B[i+4+y][i-8+2]=x7;B[i+4+y][i-8+3]=x8;

            }
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                    B[i+4+y][i-8+4+x]=A[i-8+4+x][i+4+y];
            // misses A4
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                {
                    B[i+x][i-16+y]=A[i-16+y][i+x];
                    B[i+x][i-12+y]=A[i-16+y][i+4+x];
                }
            // misses A4+B4
            for(y=0;y<4;y++)
            {
                x5=B[i+y][i-12];x6=B[i+y][i-11];x7=B[i+y][i-10];x8=B[i+y][i-9];
                B[i+y][i-12]=A[i-12][i+y];B[i+y][i-11]=A[i-11][i+y];B[i+y][i-10]=A[i-10][i+y];B[i+y][i-9]=A[i-9][i+y];
                B[i+4+y][i-16]=x5;B[i+4+y][i-16+1]=x6;B[i+4+y][i-16+2]=x7;B[i+4+y][i-16+3]=x8;

            }
            for(y=0;y<4;y++)
                for(x=0;x<4;x++)
                    B[i+4+y][i-16+4+x]=A[i-16+4+x][i+4+y];
        }
        for(i=0;i<4*8;i+=8)
            for(j=i+3*8;j<8*8;j+=8)
            {
                // misses A4
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                    {
                        B[i+x][j+y]=A[j+y][i+x];
                        B[i+x][j+4+y]=A[j+y][i+4+x];
                    }
                // misses A4+B4
                for(y=0;y<4;y++)
                {
                    x5=B[i+y][j+4];x6=B[i+y][j+5];x7=B[i+y][j+6];x8=B[i+y][j+7];
                    B[i+y][j+4]=A[j+4][i+y];B[i+y][j+5]=A[j+5][i+y];B[i+y][j+6]=A[j+6][i+y];B[i+y][j+7]=A[j+7][i+y];
                    B[i+4+y][j]=x5;B[i+4+y][j+1]=x6;B[i+4+y][j+2]=x7;B[i+4+y][j+3]=x8;
                }
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                        B[i+4+y][j+4+x]=A[j+4+x][i+4+y];
            }
        for(i=4*8;i<8*8;i+=8)
            for(j=i+1*8;j<8*8;j+=8)
            {
                // misses A4
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                    {
                        B[i+x][j+y]=A[j+y][i+x];
                        B[i+x][j+4+y]=A[j+y][i+4+x];
                    }
                // misses A4+B4
                for(y=0;y<4;y++)
                {
                    x5=B[i+y][j+4];x6=B[i+y][j+5];x7=B[i+y][j+6];x8=B[i+y][j+7];
                    B[i+y][j+4]=A[j+4][i+y];B[i+y][j+5]=A[j+5][i+y];B[i+y][j+6]=A[j+6][i+y];B[i+y][j+7]=A[j+7][i+y];
                    B[i+4+y][j]=x5;B[i+4+y][j+1]=x6;B[i+4+y][j+2]=x7;B[i+4+y][j+3]=x8;
                }
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                        B[i+4+y][j+4+x]=A[j+4+x][i+4+y];
            }
        for(i=0;i<4*8;i+=8)
            for(j=0;j<i;j+=8)
            {
                // misses A4
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                    {
                        B[i+x][j+y]=A[j+y][i+x];
                        B[i+x][j+4+y]=A[j+y][i+4+x];
                    }
                // misses A4+B4
                for(y=0;y<4;y++)
                {
                    x5=B[i+y][j+4];x6=B[i+y][j+5];x7=B[i+y][j+6];x8=B[i+y][j+7];
                    B[i+y][j+4]=A[j+4][i+y];B[i+y][j+5]=A[j+5][i+y];B[i+y][j+6]=A[j+6][i+y];B[i+y][j+7]=A[j+7][i+y];
                    B[i+4+y][j]=x5;B[i+4+y][j+1]=x6;B[i+4+y][j+2]=x7;B[i+4+y][j+3]=x8;
                }
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                        B[i+4+y][j+4+x]=A[j+4+x][i+4+y];
            }
        for(i=4*8;i<8*8;i+=8)
            for(j=0;j<i-2*8;j+=8)
            {
                // misses A4
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                    {
                        B[i+x][j+y]=A[j+y][i+x];
                        B[i+x][j+4+y]=A[j+y][i+4+x];
                    }
                // misses A4+B4
                for(y=0;y<4;y++)
                {
                    x5=B[i+y][j+4];x6=B[i+y][j+5];x7=B[i+y][j+6];x8=B[i+y][j+7];
                    B[i+y][j+4]=A[j+4][i+y];B[i+y][j+5]=A[j+5][i+y];B[i+y][j+6]=A[j+6][i+y];B[i+y][j+7]=A[j+7][i+y];
                    B[i+4+y][j]=x5;B[i+4+y][j+1]=x6;B[i+4+y][j+2]=x7;B[i+4+y][j+3]=x8;
                }
                for(y=0;y<4;y++)
                    for(x=0;x<4;x++)
                        B[i+4+y][j+4+x]=A[j+4+x][i+4+y];
            }
    }
	else if(M == 61)
	{
		int i, j, v1, v2, v3, v4, v5, v6, v7, v8;
		int n = N / 8 * 8;
		int m = M / 8 * 8;
		for (j = 0; j < m; j += 8)
			for (i = 0; i < n; ++i)
			{
				v1 = A[i][j];
				v2 = A[i][j+1];
				v3 = A[i][j+2];
				v4 = A[i][j+3];
				v5 = A[i][j+4];
				v6 = A[i][j+5];
				v7 = A[i][j+6];
				v8 = A[i][j+7];
				
				B[j][i] = v1;
				B[j+1][i] = v2;
				B[j+2][i] = v3;
				B[j+3][i] = v4;
				B[j+4][i] = v5;
				B[j+5][i] = v6;
				B[j+6][i] = v7;
				B[j+7][i] = v8;
			}
		for (i = n; i < N; ++i)
			for (j = m; j < M; ++j)
			{
				v1 = A[i][j];
				B[j][i] = v1;
			}
		for (i = 0; i < N; ++i)
			for (j = m; j < M; ++j)
			{
				v1 = A[i][j];
				B[j][i] = v1;
			}
		for (i = n; i < N; ++i)
			for (j = 0; j < M; ++j)
			{
				v1 = A[i][j];
				B[j][i] = v1;
			}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

