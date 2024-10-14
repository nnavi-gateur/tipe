// #include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdlib.h>
#include "complete_case.c"
#include <time.h>

// gcc -Wall -Wextra -Werror -Wvla -fsanitize=address,undefined -lm -o
// convolutioncolor convolution_color.c && ./convolutioncolor

pixel *creer_pixel(int width, int height) {
  pixel *p = malloc(sizeof(pixel));
  p->height = height;
  p->width = width;
  int **matb = malloc(sizeof(int *) * height);
  int **matr = malloc(sizeof(int *) * height);
  int **matg = malloc(sizeof(int *) * height);
  int **matb2 = malloc(sizeof(int *) * height);
  int **matr2 = malloc(sizeof(int *) * height);
  int **matg2 = malloc(sizeof(int *) * height);
  printf("test2\n");
  for (int i = 0; i < height; i++) {
    matb[i] = malloc(sizeof(int) * width);
    matr[i] = malloc(sizeof(int) * width);
    matg[i] = malloc(sizeof(int) * width);
    matb2[i] = malloc(sizeof(int) * width);
    matr2[i] = malloc(sizeof(int) * width);
    matg2[i] = malloc(sizeof(int) * width);
  }
  p->matr = matr;
  p->matb = matb;
  p->matg = matg;
  return p;
}

void free_mat(int **m, int height) {
  for (int i = 0; i < height; i++) {
    free(m[i]);
  }
  free(m);
}

void free_pixel(pixel *p) {
  free_mat(p->matb, p->height);
  free_mat(p->matr, p->height);
  free_mat(p->matg, p->height);
  free(p);
}
void convolution2(int **test, int **t, int height, int width,int** ker,int taillek,int divise) {
  // printf("%d\n", 1);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      t[i][j] = completer_case_rogner(i, j, test, height, width,ker,taillek,divise);
    }
  }
}

void convolution(pixel* p_norm,pixel* p_temp,int** ker,int taillek,int divise) {
  convolution2(p_norm->matr,p_temp->matr, p_norm->height, p_norm->width,ker,taillek,divise);
  convolution2(p_norm->matb, p_temp->matb, p_norm->height, p_norm->width,ker,taillek,divise);
  convolution2(p_norm->matg, p_temp->matg, p_norm->height, p_norm->width,ker,taillek,divise);
}

void recup_image_color(pixel *p) {
  int width = p->width;
  int height = p->height;
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

      p->matr[j][i] = red;
      p->matg[j][i] = green;
      p->matb[j][i] = blue;
    }
  }
}

double moyenne_coul_img (int ** mat,int height,int width){
  double sol= 0;for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      sol +=+ mat[i][j];
    }
  }
  return (sol/((double) (height * width)));

}
void copier_mat(int **old, int **new, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      new[i][j] = old[i][j];
    }
  }
}

void print_canvas2(FILE *fa,pixel* p) {
  int width = p->width;
  int height = p->height;
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      fprintf(fa, "%d ", p->matr[j][i]);
      fprintf(fa, "\n");
      fprintf(fa, "%d ", p->matg[j][i]);
      fprintf(fa, "\n");
      fprintf(fa, "%d ", p->matb[j][i]);
      fprintf(fa, "\n");
    }
  }
}

void nb_conv(pixel *p_norm, pixel *p_temp, int j,int** ker,int taillek,int divise) {
  for (int i = 0; i < j; i++) {
    convolution(p_norm, p_temp, ker, taillek,divise);
    copier_mat(p_temp->matb, p_norm->matb, p_norm->height, p_norm->width);
    copier_mat(p_temp->matg, p_norm->matg, p_norm->height, p_norm->width);
    copier_mat(p_temp->matr, p_norm->matr, p_norm->height, p_norm->width);
  }
}

void test(int **matr, int **matg, int **matb, int height, int width) {
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      printf("%d %d %d\n", matr[j][i], matg[j][i], matb[j][i]);
    }
  }
}

int main() {
  char vide[256]= "";
    char str[12];
    char strout[256];
    char strout2[256];
    char temp[5];
  time_t begin = time( NULL );
  int** ker=fill_ker(TAILLEK);
  int** ker2 =fill_ker2(TAILLEK2);
  int width;
  int height;
  int max_colour;
  sol_coul= fopen("img_res/val_couleurs_imgs","w");
  sol_coul_aft= fopen("img_res/val_couleurs_imgs_conv","w");
  final_results = fopen("img_res/val_final","w");

  for (int i = 0; i < 12; i++) {
    strcpy(strout,vide);
    strcat(strout,"img_res/");
    sprintf(temp, "%d", i);
    sprintf(str, "%d", i);
    strcat(strout,temp);
    strcat(str, ".ppm");
    strcpy(strout2,strout);
    strcat(strout, "-out.ppm");
    strcat(strout2, "-out-final.ppm");
    printf("%s\n",strout);
    fflush(stdout);
    stream = fopen(str, "rwo");
    if (stream == NULL) {
      printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", str);
      return 1;
    }

    fscanf(stream, "P6\n %d %d\n %d", &width, &height, &max_colour);
    printf("test\n");

    pixel *p_old = creer_pixel(width, height);
    pixel *p_new = creer_pixel(width, height);
    pixel *p_temp = creer_pixel(width, height);

    recup_image_color(p_old);
    copier_mat(p_old->matr, p_new->matr, p_old->height, p_old->width);
    copier_mat(p_old->matb, p_new->matb, p_old->height, p_old->width);
    copier_mat(p_old->matg, p_new->matg, p_old->height, p_old->width);
    printf("test3\n");
    fflush(stdout);
    fprintf( sol_coul,"mat n°%d | r: %f | g: %f | b: %f\n",i,moyenne_coul_img(p_old->matr,  height,  width),
    moyenne_coul_img(p_old->matg,  height,  width),moyenne_coul_img(p_old->matb,  height,  width));
    eisofhns = fopen(strout, "w");
    fprintf(eisofhns, "P3\n");
    fprintf(eisofhns, "%d %d\n", width, height);
    fprintf(eisofhns, "255");
    fprintf(eisofhns, "\n");
    nb_conv(p_new,p_temp, 1,ker,TAILLEK,9);
    printf("test4\n");
    fflush(stdout);
    print_canvas2(eisofhns, p_new );
    printf("test5\n");
    fflush(stdout);
    fclose(eisofhns);
    fprintf( sol_coul_aft,"mat n°%d | r: %f | g: %f | b: %f",i,moyenne_coul_img(p_new->matr,  height,  width),
    moyenne_coul_img(p_new->matg,  height,  width),moyenne_coul_img(p_new->matb,  height,  width));
    double prem = critere(p_old,p_new);
    fprintf(sol_coul_aft," pertes -> %f\n",prem);
    printf("test6\n");
    fflush(stdout);

    nb_conv(p_new,p_temp, 1,ker2,TAILLEK,16);
    eisofhn2Es = fopen(strout2, "w");
    fprintf(eisofhn2Es, "P3\n");
    fprintf(eisofhn2Es, "%d %d\n", width, height);
    fprintf(eisofhn2Es, "255");
    fprintf(eisofhn2Es, "\n");
    print_canvas2(eisofhn2Es, p_new );
    fclose(eisofhn2Es);
    printf("test7\n");
    fflush(stdout);
    fprintf(final_results,"mat n°%d | r: %f | g: %f | b: %f",i,moyenne_coul_img(p_new->matr,  height,  width),
    moyenne_coul_img(p_new->matg,  height,  width),moyenne_coul_img(p_new->matb,  height,  width));
    double sec = critere(p_old,p_new);
    fprintf(final_results," ,pertes -> %f ,recuperation :%f\n",sec,(prem-sec)/prem);
    free_pixel(p_new);
    free_pixel(p_old);
    free_pixel(p_temp);

  } 
  time_t end = time( NULL);
  fclose (sol_coul);
  fclose (sol_coul_aft);
  fclose(final_results);
  unsigned long secondes = (unsigned long) difftime( end, begin );
    printf( "Finished in %ld sec\n", secondes );  
  return 0;
}