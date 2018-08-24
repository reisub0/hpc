#include <cstdlib>
#include <iostream>
#include <omp.h>

using namespace std;

int main() {
  long double start, end, elapsed = 0.0;

  int arr1[100][100];
  int arr2[100][100];
  int c[100][100];

#pragma omp parallel for
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      arr1[i][j] = rand() % 500;
      arr2[i][j] = rand() % 500;
    }
  }
  int timeArray[] = {1,  2,  4,  6,  8,  10, 12, 14, 18, 22,
                     26, 30, 34, 38, 42, 46, 50, 54, 58, 62};

  int N = 100, s = 4, temp = 0;

  for (int J = 0; J < 20; J++) {
    start = omp_get_wtime();

    // #pragma omp parallel num_threads(timeArray[J])
    //     {
    //       for (int jj = 0; jj < N; jj += s) {
    //         for (int kk = 0; kk < N; kk += s) {
    //           for (int i = 0; i < N; i++) {
    //             for (int j = jj; j < ((jj + s) > N ? N : (jj + s)); j++) {
    //               temp = 0;
    //               for (int k = kk; k < ((kk + s) > N ? N : (kk + s)); k++) {
    //                 temp += arr1[i][k] * arr2[k][j];
    //               }
    //               c[i][j] += temp;
    //             }
    //           }
    //         }
    //       }
    //     }
#pragma omp parallel for num_threads(timeArray[J])
    for (int jj = 0; jj < N; jj += s) {
#pragma omp parallel for num_threads(timeArray[J])
      for (int kk = 0; kk < N; kk += s) {
#pragma omp parallel for num_threads(timeArray[J])
        for (int i = 0; i < N; i++) {
#pragma omp parallel for num_threads(timeArray[J])
          for (int j = jj; j < ((jj + s) > N ? N : (jj + s)); j++) {
            temp = 0;
#pragma omp parallel for num_threads(timeArray[J])
            for (int k = kk; k < ((kk + s) > N ? N : (kk + s)); k++) {
              temp += arr1[i][k] * arr2[k][j];
            }
            c[i][j] += temp;
          }
        }
      }
    }
    end = omp_get_wtime();
    elapsed = end - start;
    cout << timeArray[J] << "\t" << elapsed << endl;
  }
  return 0;
}
