import pandas as pd
import matplotlib.pyplot as plt

def plot_results():
    # Read CSVs with headers inferred from file content
    df_pow2 = pd.read_csv("results_pow2.csv", names=["stride", "MUpdates/s", "elapsed", "repeats"])
    df_pow1p2 = pd.read_csv("results_pow1p2.csv", names=["stride", "MUpdates/s", "elapsed", "repeats"])

    # Sort by stride just in case
    df_pow2 = df_pow2.sort_values(by="stride")
    df_pow1p2 = df_pow1p2.sort_values(by="stride")

    # Plot
    plt.figure(figsize=(10, 6))
    plt.plot(df_pow2["stride"], df_pow2["MUpdates/s"], 'o-', label="Power-of-2")
    plt.plot(df_pow1p2["stride"], df_pow1p2["MUpdates/s"], 's--', label="8·1.2ⁿ")
    plt.xscale("log")
    plt.xlabel("Stride", fontsize=12)
    plt.ylabel("Performance [MUpdates/s]", fontsize=12)
    plt.title("Strided Vector Update Performance", fontsize=14)
    plt.legend()
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig("performance_vs_stride.png", dpi=300)
    plt.show()

if __name__ == "__main__":
    plot_results()
