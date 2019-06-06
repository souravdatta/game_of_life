/* Check this repo for the code to gif encoder referenced here */
/* github: https://github.com/lecram/gifenc */
/* forked: https://github.com/souravdatta/gifenc */
/* Compile: gcc -o glife -std=c99 glife.c gifenc.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gifenc.h"

#define DIM 400

int grid[DIM][DIM];

void copy_grid(int dest[DIM][DIM])
{
    int i, j;

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            dest[i][j] = grid[i][j];
        }
    }
}

void random_init(void)
{
    int i, j, r;
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            r = rand() % 100;
            if (r > 47) {
                grid[i][j] = 1;
            }
            else {
                grid[i][j] = 0;
            }
        }
    }
}           

int ind(int x)
{
    if (x < 0)
        return DIM - 1;
    
    if (x >= DIM)
        return 0;

    return x;
}

int count_neighbors(int tgrid[DIM][DIM], int i, int j) 
{
    int p1 = tgrid[ind(i - 1)][ind(j - 1)];
    int p2 = tgrid[ind(i - 1)][ind(j)];
    int p3 = tgrid[ind(i - 1)][ind(j + 1)];
    int p4 = tgrid[ind(i)][ind(j - 1)];
    int p5 = tgrid[ind(i)][ind(j + 1)];
    int p6 = tgrid[ind(i + 1)][ind(j - 1)];
    int p7 = tgrid[ind(i + 1)][ind(j)];
    int p8 = tgrid[ind(i + 1)][ind(j + 1)];

    return p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
}

void update_grid(void)
{
    int temp_grid[DIM][DIM];
    int i, j, neighbors;
    
    copy_grid(temp_grid);

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            neighbors = count_neighbors(temp_grid, i, j);

            if (neighbors < 2) {
                grid[i][j] = 0;
            }
            else if (neighbors == 2) {
                grid[i][j] = temp_grid[i][j];
            }
            else if (neighbors == 3) {
                if (!temp_grid[i][j]) {
                    grid[i][j] = 1;
                }
            }
            else {
                grid[i][j] = 0;
            }
        }
    }
}

void add_grid_frame(ge_GIF *gif, int delay)
{
    int i, j, f;
    int grid_val;
    
    f = 0;
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) { 
            grid_val = grid[i][j];
            gif->frame[f++] = (grid_val)? 0 : 1;
        }
    }
        
    ge_add_frame(gif, delay);
}

int main(int argc, char **argv)
{
    int turns;
    ge_GIF *gif = NULL;

    if (argc == 2) {
        turns = atoi(argv[1]);
    }

    if (!turns) turns = 1;
    
    gif = ge_new_gif(
        "glife.gif", 
        DIM, DIM,
        (uint8_t []) { 
            0xFF, 0x00, 0x00, 
            0xaf, 0xbb, 0xbb,
        },
        1,             
        turns        
    );

    random_init();

    while (turns > 0) {
        add_grid_frame(gif, 10);
        update_grid();
        turns--;
    }
    
    ge_close_gif(gif);
    puts("glife.gif");

    return 0;
}
