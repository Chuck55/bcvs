In this exploit, we take advantage of the fact that for some reason, the developers thought it would be
a good idea to put the block.list file inside the repository. So, the block.list file basically prevents
us from editing or reading from block.list. However, if we create a file with the same name, "block.list"
inside the directory /opt/bcvs/bcvs, then if we run the command "./bcvs co block.list" we can read from
the forbidden block.list, and if we run the command "./bcvs ci block.list", we can write to the forbidden
block.list.

This is a bug that is almost too obvious that it might be easily overlooked. Basically, all we need to do
is to create an empty file block.list inside of our directory /opt/bcvs/bcvs. Then we can checkin that
file to the repository. Since the real block.list is inside the repository, it will be replaced by the one
that we wrote, and it has no checks in place to prevent that.

Now, we have corrupted block.list! What's the next step? Basically, what we have done in other exploits,
which is to create a passwd file, edit it to what we want /etc/passwd to look like, check it in to the
repository, remove the passwd file we just created, create a symlink to the /etc/passwd, then we can
checkout the passwd file we just checked in. And now /etc/passwd is corrupted.

If we do su student, we should be able to see the new root shell.