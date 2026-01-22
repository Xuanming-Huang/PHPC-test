#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <string>
#include <functional>

#include "kernels_cpu.hpp"

template<typename Func, typename... Args>
double simple_test(const std::string& name, Func&& kernel,
    int warmup = 5, int repeat = 20, Args&&... args)
{
    std::cout << "Running simple time cost test: " << name
              << " for " << repeat << " times.\n";

    // warmup
    for (int i = 0; i < warmup; ++i)
        kernel(std::forward<Args>(args)...);

    double total_time = 0.0;

    for (int i = 0; i < repeat; ++i) {
        auto t0 = std::chrono::steady_clock::now();
        kernel(std::forward<Args>(args)...);
        auto t1 = std::chrono::steady_clock::now();
        total_time += std::chrono::duration<double>(t1 - t0).count();
    }

    double avg = total_time / repeat;
    std::cout << name << ": Average time = " << avg << " s\n";
    return avg;
}

void roofline_test();

void bandwidth_test();

void bandwidth_cache_test(cpu_kernels::CacheLevel level, int repeat = 10);