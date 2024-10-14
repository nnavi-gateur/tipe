// #include <math.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <stdlib.h>
//  #include <time.h>

#define TAILLEM 1600
#define TAILLEK 3
#define TAILLEK2 3
#define PUISSANCE 10

// #define height 512
// #define width 512

int mat[TAILLEM][TAILLEM];
typedef int rgb[3];
FILE *fptr;
FILE *fpt;
FILE *eisofhns;
FILE *eisofhn2Es;
FILE *stream;
FILE *sol_coul;
FILE *sol_coul_aft;
FILE *final_results;

rgb canvas[TAILLEM][TAILLEM];

typedef struct pixel {
  int **matr;
  int **matg;
  int **matb;
  int height;
  int width;
} pixel;

int **fill_ker(int taillek) {
  int **ker = malloc(sizeof(int *) * taillek);
  for (int i = 0; i < taillek; i++) {
    ker[i] = malloc(sizeof(int) * taillek);
  }
  ker[0][0] = 1;
  ker[0][1] = 1;
  ker[0][2] = 1;
  // ker[0][3] =1;
  // ker[0][4] = 1;
  ker[1][0] = 1;
  ker[1][1] = 1;
  ker[1][2] = 1;
  // ker[1][3] = 1;
  // ker[1][4] = 1;
  ker[2][0] = 1;
  ker[2][1] = 1;
  ker[2][2] = 1;
  // ker[2][3] = 1;
  // ker[2][4] = 1;
  // ker[3][0] = 1;
  // ker[3][1] = 1;
  // ker[3][2] = 1;
  // ker[3][3] = 1;
  // ker[3][4] = 1;
  // ker[4][0] = 1;
  // ker[4][1] = 1;
  // ker[4][2] = 1;
  // ker[4][3] = 1;
  // ker[4][4] = 1;
  return ker;
}

int **fill_ker2(int taillek) {
  int **ker2 = malloc(sizeof(int *) * taillek);
  for (int i = 0; i < taillek; i++) {
    ker2[i] = malloc(sizeof(int) * taillek);
  }
  ker2[0][0] = 1;
  ker2[0][1] = 2;
  ker2[0][2] = 1;
  // ker2[0][3] =1;
  // ker2[0][4] = 1;
  ker2[1][0] = 2;
  ker2[1][1] = 4;
  ker2[1][2] = 2;
  // ker2[1][3] = 1;
  // ker2[1][4] = 1;
  ker2[2][0] = 1;
  ker2[2][1] = 2;
  ker2[2][2] = 1;
  // ker2[2][3] = 1;
  // ker2[2][4] = 1;
  // ker2[3][0] = 1;
  // ker2[3][1] = 1;
  // ker2[3][2] = 1;
  // ker2[3][3] = 1;
  // ker2[3][4] = 1;
  // ker2[4][0] = 1;
  // ker2[4][1] = 1;
  // ker2[4][2] = 1;
  // ker2[4][3] = 1;
  // ker2[4][4] = 1;
  return ker2;
}

double critere(pixel *p_old, pixel *p_new) {
  // categorical cross enthropy
  double val = 0;
  double val2 = 0;
  int width = p_old->width;
  int height = p_old->height;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      val2 += 3 * 255;
      val += abs(p_old->matr[j][i] - p_new->matr[j][i]);
      val += abs(p_old->matb[j][i] - p_new->matb[j][i]);
      val += abs(p_old->matg[j][i] - p_new->matg[j][i]);
    }
  }
  val = (10 * val) / (256 * 3 * width * height);
  return val;
}

int completer_case_rogner(int a, int b, int **test, int height, int width,
                          int **ker, int taillek,int divise) {
  double sol = 0;
  int diff = taillek / 2;
  for (int i = 0; i < taillek; i++) {
    for (int j = 0; j < taillek; j++) {
      if (i - diff < 0 && a + i - diff >= 0) {
        if (j - diff < 0 && b + j - diff >= 0) {
          sol += pow((double)(ker[i][j] * test[a + i - diff][b + j - diff]),
                     (double)PUISSANCE);
        } else {
          if (j - diff >= 0 && b + j - diff < width) {
            sol += pow((double)(ker[i][j] * test[a + i - diff][b + j - diff]),
                       (double)PUISSANCE);
          }
        }
      } else {
        if (i - diff >= 0 && a + i - diff < height) {
          if (j - diff < 0 && b + j - diff >= 0) {
            sol += pow((double)(ker[i][j] * test[a + i - diff][b + j - diff]),
                       (double)PUISSANCE);
          } else {
            if (j - diff >= 0 && b + j - diff < width) {
              sol += pow((double)(ker[i][j] * test[a + i - diff][b + j - diff]),
                         (double)PUISSANCE);
            }
          }
        }
      }
    }
  }
  sol = sol / divise;
  sol = pow((double)sol, (double)(1 / (double) PUISSANCE));
  if (sol < 0)
    return 0;
  else if (sol >= 255)
    return 255;
  return /* 255- */ (int)(sol);
}

int completer_case_etendre(int a, int b, int **test, int height, int width,
                           int **ker, int taillek,int divise) {
  double sol = 0;
  int diff = taillek / 2;
  for (int i = 0; i < taillek; i++) {
    for (int j = 0; j < taillek; j++) {
      if (i - diff < 0) {
        if (a + i - diff >= 0) {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][0],
                         (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][width - 1],
                         (double)PUISSANCE);
            }
          }
        } else {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[0][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[0][0], (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[0][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[0][width - 1],
                         (double)PUISSANCE);
            }
          }
        }
      } else {
        if (a + i - diff < height) {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][0],
                         (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][width - 1],
                         (double)PUISSANCE);
            }
          }
        } else {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[height - 1][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[height - 1][0],
                         (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[height - 1][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[height - 1][width - 1],
                         (double)PUISSANCE);
            }
          }
        }
      }
    }
  }
  sol = sol / divise;
  sol = pow((double)sol, 1 / (double)PUISSANCE);
  if (sol < 0)
    return 0;
  else if (sol > 255)
    return 255;
  return (int)(sol);
}

int completer_case_enroule(int a, int b, int **test, int height, int width,
                           int **ker, int taillek,int divise) {
  double sol = 0;
  int diff = taillek / 2;
  for (int i = 0; i < taillek; i++) {
    for (int j = 0; j < taillek; j++) {
      if (i - diff < 0) {
        if (a + i - diff >= 0) {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol +=
                  pow((double)ker[i][j] * test[a + i - diff][width + j - diff],
                      (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][j - diff],
                         (double)PUISSANCE);
            }
          }
        } else {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol +=
                  pow((double)ker[i][j] * test[height + i - diff][b + j - diff],
                      (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] *
                             test[height + i - diff][width + j - diff],
                         (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol +=
                  pow((double)ker[i][j] * test[height + i - diff][b + j - diff],
                      (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[height + i - diff][j - diff],
                         (double)PUISSANCE);
            }
          }
        }
      } else {
        if (a + i - diff < height) {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol +=
                  pow((double)ker[i][j] * test[a + i - diff][width + j - diff],
                      (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[a + i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[a + i - diff][j - diff],
                         (double)PUISSANCE);
            }
          }
        } else {
          if (j - diff < 0) {
            if (b + j - diff >= 0) {
              sol += pow((double)ker[i][j] * test[i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[i - diff][width + j - diff],
                         (double)PUISSANCE);
            }
          } else {
            if (b + j - diff < width) {
              sol += pow((double)ker[i][j] * test[i - diff][b + j - diff],
                         (double)PUISSANCE);
            } else {
              sol += pow((double)ker[i][j] * test[i - diff][j - diff],
                         (double)PUISSANCE);
            }
          }
        }
      }
    }
  }
  sol = sol / divise;
  sol = pow((double)sol, 1 / (double)PUISSANCE);
  if (sol < 0)
    return 0;
  else if (sol > 255)
    return 255;
  return (int)(sol);
}
