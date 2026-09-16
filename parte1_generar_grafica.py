import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados_bucles.csv")

fig, ax = plt.subplots(figsize=(7, 5))

ax.plot(df["tamano"], df["tiempo_v1"], marker="o", label="Versión 1 (por filas)")
ax.plot(df["tamano"], df["tiempo_v2"], marker="s", label="Versión 2 (por columnas)")

ax.set_xlabel("Tamaño de la matriz (MAX)")
ax.set_ylabel("Tiempo de ejecución (s)")
ax.set_title("Comparación de tiempo de ejecución según orden de los bucles")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.5)

fig.tight_layout()
fig.savefig("grafica_bucles.png", dpi=200)