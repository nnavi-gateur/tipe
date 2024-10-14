// #include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdlib.h>
#include "complete_case.c"
// #include <time.h>

// gcc -Wall -Wextra -Werror -Wvla -fsanitize=address,undefined -lm -o
// convolutioncolor convolution_color.c && ./convolutioncolor



void free_mat(int** m,int height){
  for (int i=0;i<height;i++){
    free(m[i]);
  }
  free(m);
}
void convolution2(int **test, int **t, int height, int width) {
  // printf("%d\n", 1);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      t[i][j] = completer_case_enroule(i, j, test, height, width);
    }
  }
}

void convolution(int **matr, int **matg, int **matb, int **matr2, int **matg2,
                 int **matb2, int height, int width) {
  convolution2(matr, matr2, height, width);
  convolution2(matb, matb2, height, width);
  convolution2(matg, matg2, height, width);
}

void recup_image_color(int **matr, int **matg, int **matb, int height,
                       int width) {

  unsigned char blue;
  unsigned char red;
  unsigned char green;

  printf("%d,%d\n", width, height);
  fflush(stdout);
  fgetc(stream);
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      fscanf(stream, "%c", &red);
      fscanf(stream, "%c", &green);
      fscanf(stream, "%c", &blue);

      matr[j][i] = red;
      matg[j][i] = green;
      matb[j][i] = blue;
    }
  }
}

void copier_mat(int** test, int** t, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      t[i][j] = test[i][j];
    }
  }
}

void print_canvas2(FILE *fa, int** matr, int **matg, int** matb, int height,
                   int width) {
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      fprintf(fa, "%d ", matr[j][i]);
      fprintf(fa, "\n");
      fprintf(fa, "%d ", matg[j][i]);
      fprintf(fa, "\n");
      fprintf(fa, "%d ", matb[j][i]);
      fprintf(fa, "\n");
    }
  }
}

void nb_conv(int** matr, int **matg, int** matb, int **matr2, int** matg2, int** matb2,
             int j, int height, int width) {
  for (int i = 0; i < j; i++) {
    convolution(matr, matg, matb, matr2, matg2, matb2,height,width);
    copier_mat(matb2, matb,height,width);
    copier_mat(matg2, matg,height,width);
    copier_mat(matr2, matr,height,width);
  }
}

void test(int** matr, int **matg, int** matb, int height, int width) {
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      printf("%d %d %d\n", matr[j][i], matg[j][i], matb[j][i]);
    }
  }
}

int main() {
  char str[12];
  char strout[12];
  fill_ker2();
  int width;
  int height;
  int max_colour;
  int i=0;
  sprintf(str,"%d",i);

  for (int i = 0; i < 2; i++) {
    sprintf(str, "%d", i);
    sprintf(strout, "%d", i);
    strcat(str, ".ppm");
    strcat(strout, "-out.ppm");
    stream = fopen(str, "rwo");
    if (stream == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", str);
        return 1;
    }
    
    fscanf(stream, "P6\n %d %d\n %d", &width, &height, &max_colour);
    printf("test\n");


    int **matb = malloc(sizeof(int*) * height);
    int **matr = malloc(sizeof(int*) * height);
    int **matg = malloc(sizeof(int*) * height);
    int **matb2 = malloc(sizeof(int*) * height);
    int **matr2 = malloc(sizeof(int*) * height);
    int **matg2 = malloc(sizeof(int*) * height);
    printf("test2\n");
    for(int i=0;i<height;i++){
      matb[i]=malloc(sizeof(int) * width);
      matr[i]=malloc(sizeof(int) * width);
      matg[i]=malloc(sizeof(int) * width);
      matb2[i]=malloc(sizeof(int) * width);
      matr2[i]=malloc(sizeof(int) * width);
      matg2[i]=malloc(sizeof(int) * width);
    }

    recup_image_color(matr, matg, matb, height, width);
    printf("test3\n");

    fflush(stdout);
    eisofhns = fopen(strout, "w");
    fprintf(eisofhns, "P3\n");
    fprintf(eisofhns, "%d %d\n", width, height);
    fprintf(eisofhns, "255");
    fprintf(eisofhns, "\n");
    nb_conv(matr, matg, matb, matr2, matg2, matb2, 30, height, width);
    printf("test4\n");
    print_canvas2(eisofhns, matr, matg, matb, height, width);
    printf("test5\n");
    fflush(stdout);
    fclose(eisofhns);
    free_mat(matb,height);
    free_mat(matr,height);
    free_mat(matg,height);
    free_mat(matb2,height);
    free_mat(matr2,height);
    free_mat(matg2,height);
    printf("test6\n");
    fflush(stdout);
  }
  return 0;
}