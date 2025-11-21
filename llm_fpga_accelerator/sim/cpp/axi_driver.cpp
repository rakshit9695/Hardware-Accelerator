#include "axi_driver.h"
#include <iostream>
#include "Vgemm_accelerator.h"

AXIDriver::AXIDriver(Vgemm_accelerator* dut_) : dut(dut_) {
    dut->s_axi_awvalid = 0;
    dut->s_axi_wvalid = 0;
    dut->s_axi_bready = 1;
    dut->s_axi_arvalid = 0;
    dut->s_axi_rready = 1;
}

void AXIDriver::write_register(uint32_t addr, uint32_t data) {
    dut->s_axi_awaddr = addr;
    dut->s_axi_awvalid = 1;
    dut->s_axi_wdata = data;
    dut->s_axi_wstrb = 0xf;
    dut->s_axi_wvalid = 1;
}

uint32_t AXIDriver::read_register(uint32_t addr) {
    dut->s_axi_araddr = addr;
    dut->s_axi_arvalid = 1;
    return 0;
}

void AXIDriver::clock_tick() {
    dut->clk = 1;
    dut->eval();
    dut->clk = 0;
    dut->eval();
}
