# Laboratorio 2 - Evaluación del desempeño de algoritmos y comportamiento de la memoria caché

Repositorio con el código fuente utilizado en el informe del Laboratorio 2
(bucles anidados, multiplicación clásica de matrices, multiplicación por
bloques, y análisis con Valgrind/Cachegrind).

## Requisitos

- **Compilador C++**: `g++` con soporte para C++17 (`sudo apt install g++` en Ubuntu).
- **Python 3** con las librerías `pandas` y `matplotlib`:
  ```bash
  pip install pandas matplotlib
  ```
- **Valgrind** y **KCachegrind** (solo para la Parte 5):
  ```bash
  sudo apt install valgrind kcachegrind
  ```

## Estructura de archivos

Todos los archivos están en la raíz del repositorio, agrupados por
prefijo según la parte del informe a la que corresponden.

| Archivo | Descripción |
|---|---|
| `parte1_bucles_anidados.cpp` | Implementa y mide el tiempo de las dos versiones de bucles anidados (por filas y por columnas) para distintos tamaños de matriz. Genera `resultados_bucles.csv`. |
| `parte1_generar_grafica.py` | Lee `resultados_bucles.csv` y genera `parte1_grafica.png`. |
| `parte1_grafica.png` | Gráfica de tiempo de ejecución vs. tamaño, para ambas versiones de bucles. |
| `parte2_multiplicacion_clasica.cpp` | Implementa la multiplicación clásica de matrices (tres bucles anidados) y mide su tiempo para distintos tamaños. Genera `resultados_mult_clasica.csv`. |
| `parte2_generar_grafica.py` | Lee `resultados_mult_clasica.csv` y genera `parte2_grafica.png`. |
| `parte2_grafica.png` | Gráfica de tiempo de ejecución vs. tamaño de matriz, multiplicación clásica. |
| `parte3_multiplicacion_bloques.cpp` | Implementa la multiplicación por bloques (seis bucles anidados) y corre dos experimentos: (1) clásica vs. bloques según tamaño de matriz, (2) tiempo según tamaño de bloque. Genera `resultados_bloques_vs_clasica.csv` y `resultados_bloques_tam_bloque.csv`. |
| `parte3_generar_grafica_vs_clasica.py` | Lee `resultados_bloques_vs_clasica.csv` y genera `parte3_grafica_vs_clasica.png`. |
| `parte3_generar_grafica_tam_bloque.py` | Lee `resultados_bloques_tam_bloque.csv` y genera `parte3_grafica_tam_bloque.png`. |
| `parte3_grafica_vs_clasica.png` | Gráfica: clásica vs. bloques según tamaño de matriz. |
| `parte3_grafica_tam_bloque.png` | Gráfica: tiempo según tamaño de bloque (n fijo). |
| `parte5_valgrind_clasica.cpp` | Versión mínima (una sola ejecución) de la multiplicación clásica, usada para el análisis con Cachegrind. |
| `parte5_valgrind_bloques.cpp` | Versión mínima (una sola ejecución) de la multiplicación por bloques, usada para el análisis con Cachegrind. |
| `parte5_generar_grafica.py` | Lee `resultados_valgrind.csv` (armado manualmente a partir de la salida de Cachegrind) y genera `parte5_grafica.png`. |
| `parte5_grafica.png` | Gráfica comparativa de fallos de caché (L1 y último nivel) entre ambas versiones. |

## Compilación y ejecución

### Parte 1 - Bucles anidados

```bash
g++ -O2 -std=c++17 parte1_bucles_anidados.cpp -o parte1_bucles_anidados
./parte1_bucles_anidados
python3 parte1_generar_grafica.py
```

### Parte 2 - Multiplicación clásica de matrices

```bash
g++ -O2 -std=c++17 parte2_multiplicacion_clasica.cpp -o parte2_multiplicacion_clasica
./parte2_multiplicacion_clasica
python3 parte2_generar_grafica.py
```

### Parte 3 - Multiplicación por bloques

```bash
g++ -O2 -std=c++17 parte3_multiplicacion_bloques.cpp -o parte3_multiplicacion_bloques
./parte3_multiplicacion_bloques
python3 parte3_generar_grafica_vs_clasica.py
python3 parte3_generar_grafica_tam_bloque.py
```

Este programa corre automáticamente dos experimentos en una sola
ejecución: variación por tamaño de matriz (bloque fijo `bs=64`) y
variación por tamaño de bloque (matriz fija `n=1024`). Ambos parámetros
se pueden ajustar al inicio del `main()`.

### Parte 5 - Análisis con Valgrind / Cachegrind / KCachegrind

```bash
g++ -g -O2 -std=c++17 parte5_valgrind_clasica.cpp -o parte5_valgrind_clasica
g++ -g -O2 -std=c++17 parte5_valgrind_bloques.cpp -o parte5_valgrind_bloques

valgrind --tool=cachegrind --cache-sim=yes ./parte5_valgrind_clasica
valgrind --tool=cachegrind --cache-sim=yes ./parte5_valgrind_bloques
```

Cada ejecución imprime en la terminal un resumen con instrucciones
ejecutadas (`I refs`), accesos a datos (`D refs`) y fallos de caché
(`D1 misses`, `LLd misses`, etc.), y además genera un archivo
`cachegrind.out.<pid>` en la carpeta actual. Para inspeccionarlo
visualmente:

```bash
kcachegrind cachegrind.out.<pid>
```

Los valores obtenidos de ambas ejecuciones se cargaron manualmente en
`resultados_valgrind.csv` para generar la gráfica comparativa:

```bash
python3 parte5_generar_grafica.py
```
