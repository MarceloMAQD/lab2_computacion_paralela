import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados_bloques_vs_clasica.csv")

fig, ax = plt.subplots(figsize=(7, 5))

ax.plot(df["tamano"], df["tiempo_clasica"], marker="o", color="tab:red",
        label="Multiplicación clásica")
ax.plot(df["tamano"], df["tiempo_bloques"], marker="s", color="tab:blue",
        label="Multiplicación por bloques")

ax.set_xlabel("Tamaño de la matriz (n)")
ax.set_ylabel("Tiempo de ejecución (s)")
ax.set_title("Multiplicación clásica vs. por bloques según tamaño de matriz")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.5)

fig.tight_layout()
fig.savefig("grafica_bloques_vs_clasica.png", dpi=200)