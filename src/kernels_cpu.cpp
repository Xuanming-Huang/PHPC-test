#include "kernels_cpu.hpp"

namespace cpu_kernels {
    void example_kernel() {
        static double x = 1.0;
        for (int i = 0; i < 1000000; ++i)
            x = x * 1.0000001 + 0.0000001;
    }

    void flops_peak_kernel(std::vector<double>& sink, int repeat_outer, int repeat_inner) {
        constexpr int VEC_SIZE = 64;
        double x[VEC_SIZE];

        for(int i=0;i<VEC_SIZE;i++) x[i] = i+1.0;

        for(int r=0; r<repeat_outer; r++) {
            for(int i=0; i<repeat_inner; i++) {
                for(int j=0;j<VEC_SIZE;j++)
                    x[j] = x[j] * 1.0000001 + 0.0000001;
            }
        }

        for(int i=0;i<std::min(VEC_SIZE,(int)sink.size());i++)
            sink[i] = x[i];
    }


    void bandwidth_kernel(double* a, double* b, double* c, const int N) {
        for (int i = 0; i < N; ++i)
            a[i] = b[i] + c[i];
    }
    

} // namespace cpu_kernels