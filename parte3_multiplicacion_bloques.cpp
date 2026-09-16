#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using Clock = chrono::high_resolution_clock;
using Matriz = vector<vector<double>>;

double multiplicacionClasica(const Matriz& A, const Matriz& B, Matriz& C) {
    int n = (int)A.size();
    for (auto& fila : C) fill(fila.begin(), fila.end(), 0.0);

    auto inicio = Clock::now();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++)
                suma += A[i][k] * B[k][j];
            C[i][j] = suma;
        }
    auto fin = Clock::now();

    return chrono::duration<double>(fin - inicio).count();
}

double multiplicacionPorBloques(const Matriz& A, const Matriz& B, Matriz& C,
                                 int bs) {
    int n = (int)A.size();
    for (auto& fila : C) fill(fila.begin(), fila.end(), 0.0);

    auto inicio = Clock::now();
    for (int ii = 0; ii < n; ii += bs) {
        for (int jj = 0; jj < n; jj += bs) {
            for (int kk = 0; kk < n; kk += bs) {

                int iMax = min(ii + bs, n);
                int jMax = min(jj + bs, n);
                int kMax = min(kk + bs, n);

                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        double suma = C[i][j];
                        for (int k = kk; k < kMax; k++) {
                            suma += A[i][k] * B[k][j];
                        }
                        C[i][j] = suma;
                    }
                }

            }
        }
    }
    auto fin = Clock::now();

    return chrono::duration<double>(fin - inicio).count();
}

Matriz generarMatrizAleatoria(int n, mt19937& rng) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    Matriz M(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = dist(rng);
    return M;
}

void experimento1_variarTamano(mt19937& rng) {
    vector<int> tamanos = {64, 128, 256, 512, 1024, 1536};
    const int bloqueFijo = 64;
    const int repeticiones = 2;

    ofstream csv("resultados_bloques_vs_clasica.csv");
    csv << "tamano,tiempo_clasica,tiempo_bloques\n";

    for (int n : tamanos) {
        Matriz A = generarMatrizAleatoria(n, rng);
        Matriz B = generarMatrizAleatoria(n, rng);
        Matriz C(n, vector<double>(n, 0.0));

        double tClasicaTotal = 0.0, tBloquesTotal = 0.0;
        for (int r = 0; r < repeticiones; r++) {
            tClasicaTotal += multiplicacionClasica(A, B, C);
            tBloquesTotal += multiplicacionPorBloques(A, B, C, bloqueFijo);
        }
        double tClasica = tClasicaTotal / repeticiones;
        double tBloques = tBloquesTotal / repeticiones;

        cout << "[Exp1] n=" << n
                  << "  clasica=" << tClasica << "s"
                  << "  bloques(bs=" << bloqueFijo << ")=" << tBloques << "s\n";

        csv << n << "," << tClasica << "," << tBloques << "\n";
    }
    csv.close();
}

void experimento2_variarBloque(mt19937& rng) {
    const int nFijo = 1024; 
    vector<int> bloques = {8, 16, 32, 64, 128, 256, 512, 1024};
    const int repeticiones = 2;

    Matriz A = generarMatrizAleatoria(nFijo, rng);
    Matriz B = generarMatrizAleatoria(nFijo, rng);
    Matriz C(nFijo, vector<double>(nFijo, 0.0));

    ofstream csv("resultados_bloques_tam_bloque.csv");
    csv << "bloque,tiempo\n";

    for (int bs : bloques) {
        double tTotal = 0.0;
        for (int r = 0; r < repeticiones; r++) {
            tTotal += multiplicacionPorBloques(A, B, C, bs);
        }
        double tProm = tTotal / repeticiones;

        cout << "[Exp2] n=" << nFijo << "  bloque=" << bs
                  << "  tiempo=" << tProm << "s\n";

        csv << bs << "," << tProm << "\n";
    }
    csv.close();
}

int main() {
    mt19937 rng(42);

    experimento1_variarTamano(rng);
    experimento2_variarBloque(rng);

    return 0;
}