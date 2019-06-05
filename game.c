#include <stdio.h>
#include <stdlib.h>

#define DIM 20

#ifdef _WIN32
#define CLEARCMD "CLS"
#else
#define CLEARCMD "clear"
#endif

int grid[DIM][DIM] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void loop_wait()
{
    size_t i, j;

    for (i = 0; i < 10000; i++) {
        for (j = 0; j < 10000; j++)
            ;
    }
}

void copy_grid(int dest[DIM][DIM])
{
    int i, j;

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            dest[i][j] = grid[i][j];
        }
    }
}

void show_grid(void)
{
    int i, j;

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            if (grid[i][j]) {
                printf("%2s", "o");
            }
            else {
                printf("%2s", ".");
            }
        }
        puts("");
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

int main(int argc, char **argv)
{
    int turns;

    if (argc == 2) {
        turns = atoi(argv[1]);
    }

    if (!turns) turns = 1;

    while (turns > 0) {
#ifdef CLEARCMD
        loop_wait();
        system(CLEARCMD);
#endif
        show_grid();
        puts("");
        update_grid();
        turns--;
    }

    return 0;
}

