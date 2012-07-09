#pragma once
#include <cstdint>

/* STXXL Parameters. */
const std::uint32_t B = 2; // Block size is 2 MB (default)

const std::uint32_t SORT_M = 64 * B; // Amount of memory used while sorting

const std::uint32_t PQ_M          = 32 * B * 1024 * 1024; // In bytes
const std::uint32_t PREFETCH_M    = 16 * B * 1024 * 1024; // In bytes
const std::uint32_t WRITE_M       = 16 * B * 1024 * 1024; // In bytes