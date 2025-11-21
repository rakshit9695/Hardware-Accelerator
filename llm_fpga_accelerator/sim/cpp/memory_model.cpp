#include "memory_model.h"
#include "Vgemm_accelerator.h"
#include <cstring>

MemoryModel::MemoryModel(size_t size) : memory_size(size) {
    memory = new uint8_t[size];
    std::memset(memory, 0, size);
}

MemoryModel::~MemoryModel() {
    delete[] memory;
}

void MemoryModel::update(Vgemm_accelerator* dut) {
}

void MemoryModel::write_int16(uint32_t addr, int16_t value) {
    if (addr + 1 < memory_size) {
        int16_t* ptr = reinterpret_cast<int16_t*>(&memory[addr]);
        *ptr = value;
    }
}

int16_t MemoryModel::read_int16(uint32_t addr) {
    if (addr + 1 < memory_size) {
        return *reinterpret_cast<int16_t*>(&memory[addr]);
    }
    return 0;
}

void MemoryModel::write_int32(uint32_t addr, int32_t value) {
    if (addr + 3 < memory_size) {
        int32_t* ptr = reinterpret_cast<int32_t*>(&memory[addr]);
        *ptr = value;
    }
}

int32_t MemoryModel::read_int32(uint32_t addr) {
    if (addr + 3 < memory_size) {
        return *reinterpret_cast<int32_t*>(&memory[addr]);
    }
    return 0;
}

uint16_t MemoryModel::read_uint16(uint32_t addr) {
    if (addr + 1 < memory_size) {
        return *reinterpret_cast<uint16_t*>(&memory[addr]);
    }
    return 0;
}
