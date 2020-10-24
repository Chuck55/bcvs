Mistakes in the source code :

In this exploit, we take advantage of the fact that for some reason, the developers thought it would be
a good idea to put the block.list file inside the repository. So, the block.list file basically prevents
us from editing or reading from block.list. However, if we create a file with the same name, "block.list"
inside the directory /opt/bcvs/bcvs, then if we run the command "./bcvs co block.list" we can read from
the forbidden block.list, and if we run the command "./bcvs ci block.list", we can write to the forbidden
block.list.

How we constructed our inputs:

This is a bug that is almost too obvious that it might be easily overlooked. 
Basically, all we need to do is to create an empty file block.list inside of our directory /opt/bcvs/bcvs. 
Then we can check in that file to the repository. Since the real block.list is inside the repository, it will be replaced by the one
that we wrote, and it has no checks in place to prevent that.

Now, we have corrupted block.list! What's the next step? Basically, what we have done in other exploits,
which is to create a passwd file, edit it to what we want /etc/passwd to look like, check it in to the
repository, remove the passwd file we just created, create a symlink to the /etc/passwd, then we can
checkout the passwd file we just checked in. And now /etc/passwd is corrupted.

If we do su student, we should be able to see the new root shell.

What happens when an ordinary user runs sploit3.sh:

1. The script will first navigate to the /opts/bcvs directory
2. The script will create a file called block.list
4. The script will then create an expect script exp1.exp that will check in block.list and run it
5. The script will create a passwd file, create a variable that stores the path to passwd, and stores the permissions into the file
4. The script will then create an expect script exp2.exp that will check in passwd and run it
8. The script will then remove the passwd file and create a symlink between passwd(dst) and etc/passwd(src)
9. The script will then create an expect script exp3.exp that will check out the passwd file, replacing the contents of /etc/passwd with the contents of the previous passwd file
10. The script will create an expect script exp4.exp that will log the student out and back in to refresh the permissions
13. The script will run the expect script that checks out the passwd file, so that the contents of the previous passwd file are overwritten to the etc/passwd file, as the passwd file now is a symlink
14. The script will run the script that will log the user out and back in to refresh permissions