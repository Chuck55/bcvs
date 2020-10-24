
Mistakes in the source code :
In this exploit, we take advantage of the fact that this code lets us run the program in a different
directory, and that the paths to certain files are local paths.


How we constructed our inputs:

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

What happens when an ordinary user runs sploit1.sh:
1. The script directs us to the bcvs folder and then creates a new directory called .bcvs
2. We enter into .bcvs and create a new block.list and a new passwd file. The script then redirects us outside of the directory
3. The script creates a symbolic link between /etc/passwd and a passwd file 
4. The script then sets a variable PASSWORD to the path of ./bcvs/passwd and fill the file with the permission we want
5. The script then creates an expect file expfile.exp that spawns an instance of ./bcvs, where we checkout passwd
6. The script then creates another expect file expfile2.exp that logs us out and back into student to refresh our permissions
7. The script then runs the script that checks out the passwd file, and since it contains all the permissions we want and being copied into /etc/passwd, /etc/passwd will contain all the permissions we want
8. The script then logs us out and back into student 