import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados_bloques_tam_bloque.csv")

fig, ax = plt.subplots(figsize=(7, 5))

ax.plot(df["bloque"], df["tiempo"], marker="o", color="tab:green")

ax.set_xlabel("Tamaño de bloque (bs)")
ax.set_ylabel("Tiempo de ejecución (s)")
ax.set_title("Tiempo de multiplicación por bloques según tamaño de bloque (n fijo)")
ax.grid(True, linestyle="--", alpha=0.5)

ax.set_xscale("log", base=2)
ax.set_xticks(df["bloque"])
ax.set_xticklabels(df["bloque"])

fig.tight_layout()
fig.savefig("grafica_bloques_tam_bloque.png", dpi=200)