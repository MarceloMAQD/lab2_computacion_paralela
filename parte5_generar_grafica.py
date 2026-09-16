import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados_valgrind.csv").set_index("version")

etiquetas = ["Clásica", "Bloques (bs=128)"]
colores = ["tab:red", "tab:blue"]

fig, axes = plt.subplots(1, 3, figsize=(13, 5))

valores_d1 = df["D1_misses"] / 1e6
axes[0].bar(etiquetas, valores_d1, color=colores)
axes[0].set_title("Fallos L1 de datos")
axes[0].set_ylabel("Fallos (millones)")
for i, v in enumerate(valores_d1):
    axes[0].text(i, v, f"{v:.1f}M", ha="center", va="bottom")

axes[1].bar(etiquetas, df["D1_miss_rate"], color=colores)
axes[1].set_title("Tasa de fallos L1 de datos")
axes[1].set_ylabel("Tasa de fallos (%)")
for i, v in enumerate(df["D1_miss_rate"]):
    axes[1].text(i, v, f"{v:.1f}%", ha="center", va="bottom")

axes[2].bar(etiquetas, df["LLd_misses"], color=colores)
axes[2].set_title("Fallos LL de datos\n(casi iguales: misses obligatorios)")
axes[2].set_ylabel("Fallos")
axes[2].ticklabel_format(axis="y", style="plain")
for i, v in enumerate(df["LLd_misses"]):
    axes[2].text(i, v, f"{v:,}", ha="center", va="bottom", fontsize=8)

for ax in axes:
    ax.grid(axis="y", linestyle="--", alpha=0.5)

fig.suptitle("Comparación de fallos de caché: multiplicación clásica vs. por bloques (n=512)")
fig.tight_layout()
fig.savefig("grafica_valgrind.png", dpi=200)
