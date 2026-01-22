#pragma once
#include <iostream>

namespace cpu_kernels {

    // 枚举缓存层
    enum class CacheLevel { L1, L2, L3, DRAM };

    void example_kernel();

    void flops_peak_kernel(std::vector<double>& a, const int repeat_1, const int repeat_2);

    void bandwidth_kernel(double* a, double* b, double* c, const int N);

} // namespace cpu_kernels