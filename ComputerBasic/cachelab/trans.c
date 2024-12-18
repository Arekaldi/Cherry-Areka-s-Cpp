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
#include "cachelab.h"

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */

void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /*
     * Please define your local variables here. 
     * You are allowed to define at most 12 local variables.
    */

    int i, j, k, temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;
    
    if(M == 16) { //16x16 matrix
        for(i = 0; i < 8; ++i)
            for(j = 0; j < 8; ++j)
                B[i][j + 8] = A[i][j];

        for(i = 0; i < 8; ++i)
            for(j = 8; j < M; ++j)
                B[j - 8][i] = B[i][j];

        for(i = 8; i < N; ++i)
            for(j = 0; j < 8; ++j)
                B[j][i] = A[i][j];

        for(i = 8; i < N; ++i)
            for(j = 8; j < M; ++j)
                B[i][j - 8] = A[i][j];
        
        for(i = 8; i < N; ++i)
            for(j = 0; j < 8; ++j)
                B[j + 8][i] = B[i][j];

        for(j = 8; j < M; ++j)
            for(i = 0; i < 8; ++i)
                B[j][i] = A[i][j];


        // for(j = 0; j < 8; ++j)
        //     for(i = 0; i < 8; ++i)
        //         B[j + 8][i + 8] = A[i][j];

        // for(j = 8; j < M; ++j)
        //     for(i = 8; i < N; ++i)
        //         B[j - 8][i - 8] = A[i][j];



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
        for(k = 1; k < 4; ++k)
            for(i = 0; i < k; ++i) {
                for(j = 0; j < 4; ++j) {
                    B[k * 8 + 0][i * 8 + j] = A[i * 8 + j][k * 8 + 0];
                    B[k * 8 + 1][i * 8 + j] = A[i * 8 + j][k * 8 + 1];
                    B[k * 8 + 2][i * 8 + j] = A[i * 8 + j][k * 8 + 2];
                    B[k * 8 + 3][i * 8 + j] = A[i * 8 + j][k * 8 + 3];

                    B[k * 8 + 0][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 0 + 4];
                    B[k * 8 + 1][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 1 + 4];
                    B[k * 8 + 2][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 2 + 4];
                    B[k * 8 + 3][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 3 + 4];
                }

                for(j = 0; j < 4; ++j) {
                    temp0 = B[k * 8 + j][i * 8 + 4];
                    temp1 = B[k * 8 + j][i * 8 + 5];
                    temp2 = B[k * 8 + j][i * 8 + 6];
                    temp3 = B[k * 8 + j][i * 8 + 7];
                    temp4 = A[i * 8 + 4][k * 8 + j];
                    temp5 = A[i * 8 + 4 + 1][k * 8 + j];
                    temp6 = A[i * 8 + 4 + 2][k * 8 + j];
                    temp7 = A[i * 8 + 4 + 3][k * 8 + j];

                    B[k * 8 + j][i * 8 + 4] = temp4;
                    B[k * 8 + j][i * 8 + 5] = temp5;
                    B[k * 8 + j][i * 8 + 6] = temp6;
                    B[k * 8 + j][i * 8 + 7] = temp7;

                    B[k * 8 + j + 4][i * 8 + 0] = temp0;
                    B[k * 8 + j + 4][i * 8 + 1] = temp1;
                    B[k * 8 + j + 4][i * 8 + 2] = temp2;
                    B[k * 8 + j + 4][i * 8 + 3] = temp3;
                }

                for(j = 4; j < 8; ++j) {
                    B[k * 8 + 4][i * 8 + j] = A[i * 8 + j][k * 8 + 4];
                    B[k * 8 + 5][i * 8 + j] = A[i * 8 + j][k * 8 + 5];
                    B[k * 8 + 6][i * 8 + j] = A[i * 8 + j][k * 8 + 6];
                    B[k * 8 + 7][i * 8 + j] = A[i * 8 + j][k * 8 + 7];
                }
            }

        
        for(k = 0; k < 3; ++k)
            for(i = k + 1; i < 4; ++i) {
                for(j = 0; j < 4; ++j) {
                    B[k * 8 + 0][i * 8 + j] = A[i * 8 + j][k * 8 + 0];
                    B[k * 8 + 1][i * 8 + j] = A[i * 8 + j][k * 8 + 1];
                    B[k * 8 + 2][i * 8 + j] = A[i * 8 + j][k * 8 + 2];
                    B[k * 8 + 3][i * 8 + j] = A[i * 8 + j][k * 8 + 3];

                    B[k * 8 + 0][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 0 + 4];
                    B[k * 8 + 1][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 1 + 4];
                    B[k * 8 + 2][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 2 + 4];
                    B[k * 8 + 3][i * 8 + j + 4] = A[i * 8 + j][k * 8 + 3 + 4];
                }

                for(j = 0; j < 4; ++j) {
                    temp0 = B[k * 8 + j][i * 8 + 4];
                    temp1 = B[k * 8 + j][i * 8 + 5];
                    temp2 = B[k * 8 + j][i * 8 + 6];
                    temp3 = B[k * 8 + j][i * 8 + 7];
                    temp4 = A[i * 8 + 4][k * 8 + j];
                    temp5 = A[i * 8 + 4 + 1][k * 8 + j];
                    temp6 = A[i * 8 + 4 + 2][k * 8 + j];
                    temp7 = A[i * 8 + 4 + 3][k * 8 + j];

                    B[k * 8 + j][i * 8 + 4] = temp4;
                    B[k * 8 + j][i * 8 + 5] = temp5;
                    B[k * 8 + j][i * 8 + 6] = temp6;
                    B[k * 8 + j][i * 8 + 7] = temp7;

                    B[k * 8 + j + 4][i * 8 + 0] = temp0;
                    B[k * 8 + j + 4][i * 8 + 1] = temp1;
                    B[k * 8 + j + 4][i * 8 + 2] = temp2;
                    B[k * 8 + j + 4][i * 8 + 3] = temp3;
                }

                for(j = 4; j < 8; ++j) {
                    B[k * 8 + 4][i * 8 + j] = A[i * 8 + j][k * 8 + 4];
                    B[k * 8 + 5][i * 8 + j] = A[i * 8 + j][k * 8 + 5];
                    B[k * 8 + 6][i * 8 + j] = A[i * 8 + j][k * 8 + 6];
                    B[k * 8 + 7][i * 8 + j] = A[i * 8 + j][k * 8 + 7];
                }
            }
        
        for(i = 0; i < 4; ++i) {
            for(j = i * 8; j < i * 8 + 8; ++j)
                for(k = i * 8; k < i * 8 + 8; ++k)
                    B[j][k] = A[k][j];
        }
    }
    
}




