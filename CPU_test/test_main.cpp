#include "time_cost.hpp"

int main() {
    // constexpr int N = 10000;    // Number of repetitions, 10000 times

    // simple_test("Example Kernel", []() {cpu_kernels::example_kernel();}, 5, N);

    roofline_test();
    // bandwidth_test();

    bandwidth_cache_test(cpu_kernels::CacheLevel::L1, 1'000'000);
    bandwidth_cache_test(cpu_kernels::CacheLevel::L2, 100'000);
    bandwidth_cache_test(cpu_kernels::CacheLevel::L3, 10'000);
    bandwidth_cache_test(cpu_kernels::CacheLevel::DRAM, 1'000);

    return 0;
}