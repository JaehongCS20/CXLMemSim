// Created by victoryang00 on 1/14/23.
//

#ifndef CXL_MEM_SIMULATOR_INCORE_H
#define CXL_MEM_SIMULATOR_INCORE_H
#include "helper.h"
#include "perf.h"
#include <sys/types.h>
union CPUID_INFO {
    int array[4];
    struct {
        unsigned int eax, ebx, ecx, edx;
    } reg;
};

class Incore {
public:
    PerfInfo perf[4];

    Incore(const pid_t pid, const int cpu);
    ~Incore();
    int start_pmc();
    int stop_pmc();
    int init_all_dram_rds(const pid_t pid, const int cpu);
    int init_cpu_l2stall(const pid_t pid, const int cpu);
    int init_cpu_llcl_hits(const pid_t pid, const int cpu);
    int init_cpu_llcl_miss(const pid_t pid, const int cpu);

    int read_cpu_elems(struct __incore *inc, struct __cpu_elem *cpu_elem);
};

void pcm_cpuid(unsigned leaf, CPUID_INFO *info);
bool get_cpu_info(struct CPUInfo *);

#endif // CXL_MEM_SIMULATOR_INCORE_H
