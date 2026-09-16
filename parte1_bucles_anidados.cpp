#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using Clock = chrono::high_resolution_clock;

double version1(const vector<vector<double>>& A,
                const vector<double>& x,
                vector<double>& y) {
    int n = (int)x.size();
    fill(y.begin(), y.end(), 0.0);

    auto inicio = Clock::now();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    auto fin = Clock::now();

    return chrono::duration<double>(fin - inicio).count();
}

double version2(const vector<vector<double>>& A,
                const vector<double>& x,
                vector<double>& y) {
    int n = (int)x.size();
    fill(y.begin(), y.end(), 0.0);

    auto inicio = Clock::now();
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            y[i] += A[i][j] * x[j];
    auto fin = Clock::now();

    return chrono::duration<double>(fin - inicio).count();
}

int main() {
    vector<int> tamanos = {256, 512, 1024, 2048, 4096, 8192};

    const int repeticiones = 3;

    ofstream csv("resultados_bucles.csv");
    csv << "tamano,tiempo_v1,tiempo_v2\n";

    mt19937 rng(42);
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int n : tamanos) {
        vector<vector<double>> A(n, vector<double>(n));
        vector<double> x(n), y(n, 0.0);

        for (int i = 0; i < n; i++) {
            x[i] = dist(rng);
            for (int j = 0; j < n; j++)
                A[i][j] = dist(rng);
        }

        double t1_total = 0.0, t2_total = 0.0;
        for (int r = 0; r < repeticiones; r++) {
            t1_total += version1(A, x, y);
            t2_total += version2(A, x, y);
        }

        double t1_prom = t1_total / repeticiones;
        double t2_prom = t2_total / repeticiones;

        cout << "n=" << n
                  << "  v1=" << t1_prom << "s"
                  << "  v2=" << t2_prom << "s\n";

        csv << n << "," << t1_prom << "," << t2_prom << "\n";
    }

    csv.close();
    return 0;
}