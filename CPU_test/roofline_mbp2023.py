import matplotlib.pyplot as plt
import numpy as np

peak_flops_theory = 47.0  # GFLOP/s
peak_bw = 90               # GB/s

peak_flops_measured = 33.55
bandwidth_measured = 91

AI = np.logspace(-2, 2, 200)

roofline_theory = np.minimum(AI * peak_bw, peak_flops_theory)

roofline_measured = np.minimum(AI * bandwidth_measured, peak_flops_measured)

AI_mem = 1/24
perf_mem = bandwidth_measured * AI_mem

# Compute-bound
AI_comp = 100
perf_comp = peak_flops_measured

# ----------------
plt.figure(figsize=(8,6))
plt.loglog(AI, roofline_theory, label='Theoretical Roofline (advertised)', color='blue', linewidth=2)
plt.loglog(AI, roofline_measured, label='Measured Roofline', color='orange', linewidth=2, linestyle='--')
plt.scatter(AI_mem, perf_mem, color='red', s=50, label='Memory-bound kernel')
plt.scatter(AI_comp, perf_comp, color='green', s=50, label='Compute-bound kernel')

AI_cross_theory = peak_flops_theory / peak_bw
plt.axvline(AI_cross_theory, color='blue', linestyle=':', label=f'Theory AI crossover ≈ {AI_cross_theory:.2f}')

plt.xlabel('Arithmetic Intensity [FLOPs/Byte]')
plt.ylabel('Performance [GFLOP/s]')
plt.title('Roofline: Theory vs Measured (MacBook Pro 2023 Single-Core)')
plt.grid(True, which='both', ls='--', alpha=0.5)
plt.legend()
plt.show()
