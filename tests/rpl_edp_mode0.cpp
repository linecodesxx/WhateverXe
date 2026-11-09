#include "kern_alderlake_n.hpp"
#include <cassert>
#include <initializer_list>
#include <cstdio>
using namespace AlderLakeN;
int main() {
 assert(acceptedRplEDPSSTMode(1,1,0,1,false));
 assert(!acceptedRplEDPSSTMode(0,1,0,1,false));
 configureRplEDPMode0(0xa7a08086,4,true,true);
 assert(acceptedRplEDPSSTMode(0,1,0,1,false));
 assert(!acceptedRplEDPSSTMode(0,1,0,1,true));
 assert(!acceptedRplEDPSSTMode(0,1,1,2,false));
 assert(!acceptedRplEDPSSTMode(0,1,0,0,false));
 assert(!acceptedRplEDPSSTMode(0,3,0,1,false));
 for(unsigned m:{2U,3U,4U,0xffffffffU})assert(!acceptedRplEDPSSTMode(m,1,0,1,false));
 for(unsigned id:{0xa7a18086U,0x46a38086U,0xa7a88086U}) {
  configureRplEDPMode0(id,4,true,true);assert(!acceptedRplEDPSSTMode(0,1,0,1,false));
 }
 configureRplEDPMode0(0xa7a08086,3,true,true);assert(!acceptedRplEDPSSTMode(0,1,0,1,false));
 configureRplEDPMode0(0xa7a08086,4,false,true);assert(!acceptedRplEDPSSTMode(0,1,0,1,false));
 configureRplEDPMode0(0xa7a08086,4,true,false);assert(!acceptedRplEDPSSTMode(0,1,0,1,false));
 assert(acceptedRplEDPSSTMode(1,1,0,1,true));
 assert(acceptedRplEDPSSTMode(3,3,3,0,true));
 std::puts("PASS: opt-in physical/OS scope, boot-only eDP mode0, negative gates, default modes unchanged");
}
