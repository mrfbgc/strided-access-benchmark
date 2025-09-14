# Strided Memory Access Benchmark

This project was developed as part of the **Programming Techniques for Supercomputers** course. It focuses on benchmarking the performance impact of different memory access stride patterns and analyzing cache behavior on modern CPUs.

## Project Overview

The assignment investigates how **stride length** affects memory throughput and cache utilization. It consists of:

1. **Theoretical Analysis**  
   - Peak floating-point performance under different vectorization modes (AVX-512, AVX2, Scalar).  
   - Bandwidth and latency analysis using Hockney’s model.  
   - Cache efficiency and prefetching behavior.  

2. **Practical Benchmarking**  
   - Implementation of a vector update kernel with varying strides.  
   - Measurement of updates per second for:
     - **Power-of-2 strides** (`M = 2^0 ... 2^20`)  
     - **Non-power-of-2 strides** (`M = 8 × 1.2^n`)  

3. **Visualization and Interpretation**  
   - Performance vs stride plots.  
   - Comparison of regular vs irregular stride patterns.  
   - Explanation of cache thrashing and loss of locality.  

---

## Code Structure

### 1. `main.cpp`

- Implements the **strided vector update benchmark**:
  ```cpp
  for (size_t i = 0; i < N; i += stride) {
      a[i] *= s;
  }
  ```
- Runs two sets of experiments:
  - Power-of-2 strides
  - Non-power-of-2 strides (`8 × 1.2^n`)
- Ensures each benchmark runs for at least **0.5 seconds**.  
- Writes results to:
  - `results_pow2.csv`
  - `results_pow1p2.csv`

### 2. `timing.hpp`

- Provides `getTimeStamp()` based on `std::chrono` for precise timing.

### 3. `plot.py`

- Loads results from CSV files.  
- Plots performance curves for:
  - Power-of-2 strides
  - Non-power-of-2 strides  
- Saves the comparison figure as:
  - `performance_vs_stride.png`

### 4. `assignment_3.pdf`

- Contains the detailed write-up:
  - Peak performance calculations
  - Hockney’s model analysis
  - Stride effect interpretation
  - Experimental results with plots

---

## Compilation and Execution

### Compilation

Use g++ or icpx with optimizations:

```bash
g++ -O3 -march=native -std=c++17 main.cpp -o benchmark.out
```

### Running Benchmarks

On a compute node or locally:

```bash
./benchmark.out
```

This produces two CSV files with performance results.

### Plotting Results

Run the Python script:

```bash
python3 plot.py
```

This generates and saves the figure:

- `performance_vs_stride.png`

---

## Results Summary

- **Power-of-2 strides**: performance drops sharply due to cache conflicts and reduced locality.  
- **Non-power-of-2 strides**: more uniform distribution across cache sets, maintaining higher performance.  
- Performance stabilizes at low values once locality is lost (`M ≈ 2^13`).  

---

## File Outputs

- `results_pow2.csv` – performance for power-of-2 strides  
- `results_pow1p2.csv` – performance for non-power-of-2 strides  
- `performance_vs_stride.png` – stride vs performance plot  

---

## License

This project is available under the MIT license. See the LICENSE.md file for more info.

## Authors

Mehmet Arif Bagci - mehmet.a.bagc@fau.de
