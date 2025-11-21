#ifndef GEMM_TESTBENCH_H
#define GEMM_TESTBENCH_H

#include <vector>
#include <cstdint>
#include <cstddef>

class Vgemm_accelerator;
class AXIDriver;
class MemoryModel;

class GEMMTestbench {
public:
    explicit GEMMTestbench(Vgemm_accelerator* dut, AXIDriver* axi);
    ~GEMMTestbench();
    int run();
    std::vector<int16_t> generate_test_matrix(size_t rows, size_t cols, uint32_t seed);
    std::vector<int32_t> compute_reference_gemm(const std::vector<int16_t>& A,
                                                 const std::vector<int16_t>& B,
                                                 size_t M, size_t N, size_t K);
    bool verify_results(const std::vector<int32_t>& actual,
                        const std::vector<int32_t>& reference);
private:
    Vgemm_accelerator* dut;
    AXIDriver* axi;
    MemoryModel* memory;
};

#endif
