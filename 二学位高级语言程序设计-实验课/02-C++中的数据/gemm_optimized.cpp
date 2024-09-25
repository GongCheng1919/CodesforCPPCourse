#include <immintrin.h>
#include <omp.h>

template<typename T>
void gemm_optimized(const T* A, const T* B, T* C, int m, int n, int k) {
    const int L1BlockSize = 48;  // Adjust this value to fit your L1 cache
    const int L2BlockSize = 192; // Adjust this value to fit your L2 cache

    T* B_reordered = new T[L2BlockSize*L2BlockSize];

    #pragma omp parallel for
    for (int i = 0; i < m; i += L2BlockSize) {
        for (int j = 0; j < n; j += L2BlockSize) {
            // Reorder B in blocks to improve cache utilization
            for (int p = 0; p < k; ++p) {
                for (int jj = j; jj < j + L2BlockSize && jj < n; ++jj) {
                    B_reordered[(jj-j)*k+p] = B[p*n+jj];
                }
            }
            for (int ii = i; ii < i + L2BlockSize && ii < m; ii += L1BlockSize) {
                for (int jj = j; jj < j + L2BlockSize && jj < n; jj += L1BlockSize) {
                    for (int iii = ii; iii < ii + L1BlockSize && iii < m; iii += 3) {
                        for (int jjj = jj; jjj < jj + L1BlockSize && jjj < n; jjj += 4) {
                            __m256 c[3][4] = {{_mm256_setzero_ps()}};
                            for (int p = 0; p < k; ++p) {
                                for (int x = 0; x < 3; ++x) {
                                    for (int y = 0; y < 4; ++y) {
                                        __m256 a = _mm256_set1_ps(A[(iii+x)*k+p]);
                                        __m256b = _mm256_load_ps(&B_reordered[(jjj-j+y)*k+p]);
                                        c[x][y] = _mm256_fmadd_ps(a, b, c[x][y]);
                                    }
                                }
                            }
                            for (int x = 0; x < 3; ++x) {
                                for (int y = 0; y < 4; ++y) {
                                    _mm256_storeu_ps(&C[(iii+x)*n+(jjj+y)], _mm256_add_ps(_mm256_loadu_ps(&C[(iii+x)*n+(jjj+y)]), c[x][y]));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    delete[] B_reordered;
}