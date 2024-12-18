/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Your transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * The transpose function is evaluated by counting the number of misses
 * on a 512B direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
int A[32][32], B[32][32];

void transpose_submit(int M, int N)
{
    /*
     * Please define your local variables here. 
     * You are allowed to define at most 12 local variables.
    */
    int i, j, k, temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;
    
    if(M == 16) { //16x16 matrix
    
        
        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < 8; ++j)
                B[i][j + 8] = A[i][j];

        for(int i = 0; i < N; ++i)
            for(int j = 8; j < M; ++j)
                B[j - 8][i] = B[i][j];

        for(j = 0; j < 8; ++j)
            for(i = 8; i < N; ++i)
                B[j][i] = A[i][j];

        for(int i = 8; i < N; ++i)
            for(int j = 8; j < M; ++j)
                B[i][j - 8] = A[i][j];
        
        for(int i = 8; i < N; ++i)
            for(int j = 0; j < 8; ++j)
                B[j + 8][i] = B[i][j];

        for(j = 8; j < M; ++j)
            for(i = 0; i < 8; ++i)
                B[j][i] = A[i][j];

        // for(j = 8; j < M; ++j)
        //     for(i = 0; i < 8; ++i)
        //         B[j][i] = A[i][j];

        // for(j = 0; j < 8; ++j)
        //     for(i = 8; i < N; ++i)
        //         B[j][i] = A[i][j];

        // for(i = 0; i < 8; ++i)
        //     for(j = 0; j < 8; ++j) {
        //         B[j + 8][i + 8] = A[i][j];
        //     }

        // for(i = 8; i < N; ++i)
        //     for(j = 8; j < M; ++j) {
        //         B[j - 8][i - 8] = A[i][j];
        //     }

        // for(i = 8; i < N; ++i) {
        //     temp0 = B[i][8];
        //     temp1 = B[i][9];
        //     temp2 = B[i][10];
        //     temp3 = B[i][11];
        //     temp4 = B[i][12];
        //     temp5 = B[i][13];
        //     temp6 = B[i][14];
        //     temp7 = B[i][15];
        //     for(j = 8; j < M; ++j)
        //         B[i][j] = B[i - 8][j - 8];
            
        //     B[i - 8][0] = temp0;
        //     B[i - 8][1] = temp1;
        //     B[i - 8][2] = temp2;
        //     B[i - 8][3] = temp3;
        //     B[i - 8][4] = temp4;
        //     B[i - 8][5] = temp5;
        //     B[i - 8][6] = temp6;
        //     B[i - 8][7] = temp7;
        // }
    }
    else if(M == 32) { //32x32 matrix
        for(i = 0; i < 1; ++i) {
                for(j = 0; j < 4; ++j)
                    for(k = 0; k < 8; ++k)
                        B[i * 8 + 8 + j][i * 8 + 8 + k] = A[i * 8 + 4 + j][i * 8 + k];

                for(j = 0; j < 4; ++j) {
                    temp0 = A[i * 8 + j][i * 8 + 0];
                    temp1 = A[i * 8 + j][i * 8 + 1];
                    temp2 = A[i * 8 + j][i * 8 + 2];
                    temp3 = A[i * 8 + j][i * 8 + 3];
                    temp4 = A[i * 8 + j][i * 8 + 4];
                    temp5 = A[i * 8 + j][i * 8 + 5];
                    temp6 = A[i * 8 + j][i * 8 + 6];
                    temp7 = A[i * 8 + j][i * 8 + 7];

                    
                    B[i * 8 + j][i * 8 + 0] = temp0;
                    B[i * 8 + j][i * 8 + 1] = temp1;
                    B[i * 8 + j][i * 8 + 2] = temp2;
                    B[i * 8 + j][i * 8 + 3] = temp3;
                    B[i * 8 + j][i * 8 + 4] = temp4;
                    B[i * 8 + j][i * 8 + 5] = temp5;
                    B[i * 8 + j][i * 8 + 6] = temp6;
                    B[i * 8 + j][i * 8 + 7] = temp7;
                }
            }
    }
    
}

int main() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            A[i][j] = i * 32 + j;
        }
    }
    transpose_submit(32, 32);
    for(int i = 0; i < 32; ++i) {
        for(int j = 0; j < 32; ++j)
            printf("%d ", B[i][j]);
        printf("\n");
    }
}