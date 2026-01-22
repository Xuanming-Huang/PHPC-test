#include "time_cost.hpp"

void roofline_test() {
    constexpr int N = 10'000'000;
    std::cout << "Test Peak FLOPS: " << "flops_peak_kernel" << " for " << N << " times.\n";
    
    constexpr int VEC_SIZE = 64;
    std::vector<double> sink(VEC_SIZE);
    int repeat_1 = 100;
    int repeat_2 = N / repeat_1;
    double time = simple_test("Peak FLOPS Kernel", cpu_kernels::flops_peak_kernel, 1, 10, sink, repeat_1, repeat_2);
    double total_flops = VEC_SIZE * 2 * repeat_1 * repeat_2;
    std::cout << "FLOPS = " << total_flops / time / 1e9 << " GFLOP/s\n";
}

void bandwidth_test() {
    constexpr int N = 10'000'000;
    std::vector<double> a(N), b(N), c(N);
    std::cout << "Test Peak Bandwidth: " << "bandwidth_kernel" << " for " << N << " elements.\n";
    double time = simple_test("bandwidth_kernel", cpu_kernels::bandwidth_kernel, 1, 10, a.data(), b.data(), c.data(), N);
    double bandwidth = 3.0 * N * sizeof(double) / time;
    std::cout << "Bandwidth = " << bandwidth / 1e9 << " GB/s\n";
}

void bandwidth_cache_test(cpu_kernels::CacheLevel level, int repeat) {
    size_t N;
    std::string name;

    switch(level) {
        case cpu_kernels::CacheLevel::L1:
            N = 16*1024; // 16K doubles < 192 KB
            name = "L1 Bandwidth";
            break;
        case cpu_kernels::CacheLevel::L2:
            N = 128*1024; // 128K doubles < 1 MB
            name = "L2 Bandwidth";
            break;
        case cpu_kernels::CacheLevel::L3:
            N = 3*1024*1024; // 3M doubles < 24 MB
            name = "L3 Bandwidth";
            break;
        case cpu_kernels::CacheLevel::DRAM:
            N = 10*1024*1024; // > L3
            name = "DRAM Bandwidth";
            break;
    }

    std::vector<double> a(N), b(N), c(N);

    std::cout << "Test Peak Bandwidth of " << name << ": " << "bandwidth_kernel" << " for " << N << " elements.\n";

    double time = simple_test(name, cpu_kernels::bandwidth_kernel, 1, repeat,
                              a.data(), b.data(), c.data(), (int)N);

    double bandwidth = 3.0 * N * sizeof(double) / time; // bytes/sec
    std::cout << name << " = " << bandwidth / 1e9 << " GB/s\n";
}