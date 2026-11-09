#include "kern_alderlake_n.hpp"
#include <cassert>
#include <initializer_list>
#include <cstdio>
using namespace AlderLakeN;
static DisplayReadout snapshot() {
    DisplayReadout r;
    r.status=ReadoutStatus::Complete;r.poweredPipes=7;r.activePipes=1;
    const Register regs[]={
        {0x60400,0x8a000106},{0x60404,8},{0x64000,0x80000006},
        {0x60540,0x80040300},{0x46140,0x10000000},
        {0x60030,0x7e7f360b},{0x60034,0x00800000},
        {0x60040,0x000a99d6},{0x60044,0x00080000},
        {0x78000,0},{0x78004,0}};
    for(auto v:regs)r.registers[r.count++]=v;
    return r;
}
static void set(DisplayReadout &r,unsigned offset,unsigned value) {
    for(unsigned i=0;i<r.count;++i)if(r.registers[i].offset==offset){r.registers[i].value=value;return;}
    assert(false);
}
int main() {
    auto r=snapshot();
    assert(!dpSource(r,0,0,nullptr,true)); // default is unchanged
    configureRplEDPCTL2Bit3(0xa7a08086,4,true,false);
    assert(!dpSource(r,0,0,nullptr,true));
    configureRplEDPCTL2Bit3(0xa7a08086,4,true,true);
    assert(dpSource(r,0,0,nullptr,true));
    assert(!dpSource(r,0,0,nullptr,false)); // external DP unchanged
    for(unsigned ctl:{1U,2U,4U,9U,16U,24U,32U,0xffffffffU}) {
        auto bad=r;set(bad,0x60404,ctl);assert(!dpSource(bad,0,0,nullptr,true));
    }
    const Register badRegs[]={{0x60400,0x8a008106},{0x60400,0x8a000306},
        {0x64000,0x80000002},{0x78000,0x80000000},{0x60034,0}};
    for(auto reg:badRegs){auto bad=r;set(bad,reg.offset,reg.value);assert(!dpSource(bad,0,0,nullptr,true));}
    for(unsigned id:{0xa7a18086U,0x46a08086U,0xa7a88086U}) {
        configureRplEDPCTL2Bit3(id,4,true,true);assert(!dpSource(r,0,0,nullptr,true));
    }
    configureRplEDPCTL2Bit3(0xa7a08086,3,true,true);assert(!dpSource(r,0,0,nullptr,true));
    configureRplEDPCTL2Bit3(0xa7a08086,4,false,true);assert(!dpSource(r,0,0,nullptr,true));
    set(r,0x60404,0);assert(dpSource(r,0,0,nullptr,true));
    std::puts("PASS: observed eDP snapshot, opt-in identity/OS scope and rejection guards");
}
