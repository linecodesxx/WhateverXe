#include "kern_display13_fb_memory.hpp"
#include "kern_display13_fb_topology.hpp"
#include <cassert>
#include <initializer_list>
int main(){
 using namespace Display13FBMemory;Pool p{};p.base=0;p.bytes=14847U*4096;
 AlderLakeN::configureRplEDPMode0(0xA7A08086,4,true,false);
 assert(!apertureRange(p,0,16988160,0x10000000));
 AlderLakeN::configureRplEDPMode0(0xA7A08086,4,true,true);
 assert(apertureRange(p,0,16988160,0x10000000));
 assert(!apertureRange(p,1,16988160,0x10000000));
 assert(!apertureRange(p,0,16988161,0x10000000));
 assert(!apertureRange(p,0,0,0x10000000));
 assert(!apertureRange(p,0,16988160,16988160));
 p.bytes=16988160;assert(!apertureRange(p,0,16988160,0x10000000));
 for(unsigned id:{0x46A68086U,0xA7A18086U}){
  AlderLakeN::configureRplEDPMode0(id,4,true,true);p.bytes=14847U*4096;
  assert(!apertureRange(p,0,16988160,0x10000000));
 }
 Display13OutputWiring w;w.valid=true;w.panel=1;w.dp=8;w.typeC=8;
 assert(Display13FBTopology::panelOnlyClock(w,0,true,false,false));
 assert(!Display13FBTopology::panelOnlyClock(w,0,true,true,false));
 assert(!Display13FBTopology::panelOnlyClock(w,0,true,false,true));
 assert(!Display13FBTopology::panelOnlyClock(w,3,true,false,false));
 assert(!Display13FBTopology::panelOnlyClock(w,0,false,false,false));
}
