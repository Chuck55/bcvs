In this exploit, we take advantage of the fact that this code lets us run the program in a different
directory.

Based on line 21:
#define BLOCK_LIST_PATH ".bcvs/block.list"

We see that the path of the block list is defined in .bcvs/block.list. So, even though we do not have
permissions to edit that specific block.list or access the directory /opt/bcvs/.bcvs, we can create a
.bcvs directory in a different directory from /opt/bcvs (such as our home directory, or in this case
we used ~/bcvs). Then, we can create a block.list file inside that .bcvs directory that we have all
permissions to (because we created the directory). We can make this block.list empty so that we aren't
blocked from anything.

Now, we can run the /opt/bcvs/bcvs executable from our ~/bcvs directory.

Because the block list path is ".bcvs/block.list", and we ran it from our ~/bcvs directory, then the
program will check for "~/bcvs/./bcvs/block.list", a.k.a the one we just created. Since it is empty,
it will allow us to do what we need.

So, we can write to /etc/passwd. And we can change student to be the root id. We do this by creating
a passwd file, writing what we want to it, checking it into the directory, then removing the passwd 
file. Then, we create a symbolic link under the same name "passwd", and then we have that link to the
/etc/passwd file. Then we can use bcvs to check out passwd, so that what we just checked into passwd
will be written to /etc/passwd.

Now, if we do su student, we should be able to see the root shell.