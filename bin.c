#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

#define TAILLEM 1600
#define TAILLEK 3

#define HEIGHT 512
#define WIDTH 512


int ker[TAILLEK][TAILLEK];
int mat[TAILLEM][TAILLEM];
typedef int rgb[3];
FILE *fptr;
FILE *fpt;
FILE *eisofhns;
FILE *stream;

rgb canvas[TAILLEM][TAILLEM];

void put_pixel(int x, int y, rgb c) {
  int i = TAILLEM - 1 - y;
  int j = x;
  if (i < 0 || i >= TAILLEM || j < 0 || j > TAILLEM)
    return;
  for (int k = 0; k < 3; k++) {
    canvas[i][j][k] = c[k];
  }
}

void freet(int **t) {
  for (int i = 0; i < HEIGHT; i++)
    free(t[i]);
  free(t);
}
int ker[TAILLEK][TAILLEK];
int mat[TAILLEM][TAILLEM];
typedef int rgb[3];
FILE *fptr;
FILE *fpt;
FILE *eisofhns;
FILE *stream;

rgb canvas[TAILLEM][TAILLEM];

void white_noise() {
  for (int y = 0; y < TAILLEM; y++) {
    for (int x = 0; x < TAILLEM; x++) {
      double n = (double)rand() / (double)(RAND_MAX);
      mat[y][x] = round(255.0 * n);
    }
  }
}

void fill_canva() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      for (int k = 0; k < 3; k++) {
        canvas[y][x][k] = mat[y][x];
      }
    }
  }
}
void fill_canva2(int **t) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      for (int k = 0; k < 3; k++) {
        canvas[y][x][k] = t[y][x];
      }
    }
  }
}

void fill_canva3(int test[WIDTH][HEIGHT]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      for (int k = 0; k < 3; k++) {
        canvas[y][x][k] = test[y][x];
      }
    }
  }
}


int completer_case2(int a, int b, int test[HEIGHT][WIDTH]) {
  int sol = 0;
  if (a - 1 >= 0) {
    if (b - 1 >= 0)
      sol += ker[0][0] * test[a - 1][b - 1];
    if (b + 1 < WIDTH)
      sol += ker[0][2] * test[a - 1][b + 1];
    sol += ker[0][1] * test[a - 1][b];
  }
  if (a + 1 < HEIGHT) {
    if (b - 1 >= 0)
      sol += ker[2][0] * test[a + 1][b - 1];
    if (b + 1 < WIDTH)
      sol += ker[2][2] * test[a + 1][b + 1];
    sol += ker[2][1] * test[a + 1][b];
  }
  if (b - 1 >= 0)
    sol += ker[1][0] * test[a][b - 1];
  if (b + 1 < WIDTH)
    sol += ker[1][2] * test[a][b + 1];
  sol += ker[1][1] * test[a][b];
  if (sol < 0)
    return 0;
  else if (sol / 2 > 255)
    return 255;
  return sol / 2;
}

void print_canvas(FILE *fa) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      for (int k = 0; k < 3; k++) {
        fprintf(fa, "%d ", canvas[i][j][k]);
        fprintf(fa, "\n");
      }
    }
  }
}

int completer_case_rogner(int a, int b, int test[HEIGHT][WIDTH]) { return 0; }

int **convolution(int test[HEIGHT][WIDTH]) {
  printf("%d\n", 1);
  int **sol = malloc(sizeof(int *) * HEIGHT);

  for (int i = 0; i < HEIGHT; i++)
    sol[i] = malloc(sizeof(int) * WIDTH);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      sol[i][j] = completer_case_rogner(i, j, test);
    }
  }

  return sol;
}
int maint() { return 0; }