#ifndef AXI_DRIVER_H
#define AXI_DRIVER_H

#include <cstdint>

class Vgemm_accelerator;

class AXIDriver {
public:
    explicit AXIDriver(Vgemm_accelerator* dut_);
    void write_register(uint32_t addr, uint32_t data);
    uint32_t read_register(uint32_t addr);
    void clock_tick();
private:
    Vgemm_accelerator* dut;
};

#endif
