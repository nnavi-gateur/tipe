// #include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdlib.h>
#include "complete_case.c"
// #include <time.h>


void convolution(int **test, int ** t,int height,int width) {
  printf("%d\n", 1);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      t[i][j] = completer_case_enroule(i, j, test,height,width);
    }
  }
}

void free_mat(int **m, int height) {
  for (int i = 0; i < height; i++) {
    free(m[i]);
  }
  free(m);
}

void recup_image_bw(int **mat,int height,int width) {
  unsigned char blue;
  unsigned char red;
  unsigned char green;

  fgetc(stream);
  printf("%d,%d\n", width, height);
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      unsigned int grey;
      fscanf(stream, "%c", &red);
      fscanf(stream, "%c", &green);
      fscanf(stream, "%c", &blue);
      grey = 0;
      grey += 299 * red; // red
      printf("%d ", red);
      grey += 586 * blue; // green
      printf("%d ", green);
      grey += 114 * green; // blue
      printf("%d\n", blue);
      grey /= 1000;
      mat[j][i] = grey;
    }
  }
}

void copier_mat(int **test, int **t,int height,int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      t[i][j] = test[i][j];
    }
  }
}

void print_canvas(FILE *fa, int **test,int height,int width) {
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      for (int k = 0; k < 3; k++) {
        fprintf(fa, "%d ", test[j][i]);
        fprintf(fa, "\n");
      }
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
  int i = 0;
  sprintf(str, "%d", i);

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
    int **test = malloc(sizeof(int *) * height);
    int **t = malloc(sizeof(int *) * height);
    for(int i=0;i<height;i++){
      test[i]=malloc(sizeof(int)*width);
      t[i]=malloc(sizeof(int)*width);
    }

    recup_image_bw(test,height,width);

    eisofhns = fopen("test.ppm", "w");
    fprintf(eisofhns, "P3\n");
    fprintf(eisofhns, "%d %d\n", width, height);
    fprintf(eisofhns, "255");
    fprintf(eisofhns, "\n");

    for (int i = 0; i < 0; i++) {
      convolution(test, t,height,width);
      copier_mat(t, test,height,width);
    }

    print_canvas(eisofhns, test,height,width);
    fclose(eisofhns);
    free_mat(test,height);
    free_mat(t,height);
    return 0;
  }
}