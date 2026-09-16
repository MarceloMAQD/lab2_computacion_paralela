import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados_mult_clasica.csv")

fig, ax = plt.subplots(figsize=(7, 5))

ax.plot(df["tamano"], df["tiempo"], marker="o", color="tab:red",
        label="Multiplicación clásica (i-j-k)")

ax.set_xlabel("Tamaño de la matriz (n)")
ax.set_ylabel("Tiempo de ejecución (s)")
ax.set_title("Tiempo de ejecución vs. tamaño de matriz — multiplicación clásica")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.5)

fig.tight_layout()
fig.savefig("grafica_mult_clasica.png", dpi=200)