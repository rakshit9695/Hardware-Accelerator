#include "gemm_testbench.h"
#include "axi_driver.h"
#include "memory_model.h"
#include <random>
#include <iostream>

GEMMTestbench::GEMMTestbench(Vgemm_accelerator* dut_, AXIDriver* axi_)
    : dut(dut_), axi(axi_) {
    memory = new MemoryModel(1024 * 1024);
}

GEMMTestbench::~GEMMTestbench() {
    delete memory;
}

std::vector<int16_t> GEMMTestbench::generate_test_matrix(size_t rows, size_t cols, uint32_t seed) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int16_t> dis(-128, 127);
    std::vector<int16_t> matrix;
    for (size_t i = 0; i < rows * cols; ++i) {
        matrix.push_back(dis(gen));
    }
    return matrix;
}

std::vector<int32_t> GEMMTestbench::compute_reference_gemm(const std::vector<int16_t>& A,
                                                            const std::vector<int16_t>& B,
                                                            size_t M, size_t N, size_t K) {
    std::vector<int32_t> C(M * N, 0);
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            int32_t acc = 0;
            for (size_t k = 0; k < K; ++k) {
                acc += static_cast<int32_t>(A[m * K + k]) * static_cast<int32_t>(B[k * N + n]);
            }
            C[m * N + n] = acc;
        }
    }
    return C;
}

bool GEMMTestbench::verify_results(const std::vector<int32_t>& actual,
                                    const std::vector<int32_t>& reference) {
    if (actual.size() != reference.size()) return false;
    for (size_t i = 0; i < actual.size(); ++i) {
        if (actual[i] != reference[i]) return false;
    }
    return true;
}

int GEMMTestbench::run() {
    std::cout << "GEMM testbench running..." << std::endl;
    return 0;
}
