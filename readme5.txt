Mistakes in the Source Code
In this exploit, we aim for the use of the real path function. We find that the real path function finds the absolute path that the file is pointing to,
for example, when given a symlink, the real path function will pass back the path to the file that the symlink is pointing to. However, the 
path that was passed in is not to the file that the realpath function returns, so that when bcvs goes to checkout the file, it will checkout the file that the passed in path 
paths to, not the file that was being pointed to by the symlink. So for example, if we pass in a symlink that has a source of file.txt and a destination of file2.txt, when we run .bcvs co file2.txt, the
real path function will recognize that file2.txt is a symlink to file.txt, but the rest of bcvs does nothing to address this, as it will continue to checkout file2.txt.

How we constructed our inputs:

So in this case, we passed in a file called block.list, which was a symlink to a file called file.txt, which had nothing in it.
When bcvs went to go and check that the file path was not one of the file paths in the block list, it saw the file.txt path instead of the 
block.list file path. So it let us write a log, check in and check out. However, when it came time for the program to check out and check in the 
file, it checked out and checked in block.list file, which we used to wipe our block.list, so that no files were blocked anymore

Now because block.list is now empty, this means that we can check in and checkout any of the blocked files from before. This means that we can checkout /etc/passwd. 
But this would not do anything right now, since checking out the passwd we checked in at the beginning of the script wouldn't do anything. We now need to delete the passwd file that we have, and create
a new passwd file that is a symlink to the /etc/passwd file, so that now, when we checkout passwd, it will overwrite everything in /etc/passwd with the contents of our previous passwd file.

Once we do this, all we need to do now is to log out of our user, which refreshes the permssions of our student account, and we now have root permissions.

What happens when an ordinary user runs sploit5.sh:

1. The script will first navigate to the /opts/bcvs directory
2. The script will create a symlink between a file called block.list and another file called file.txt
3. The script will then create an expect script exp1.exp that will check in block.list and run it
4. The script will create a passwd file, create a variable that stores the path to passwd, and stores the permissions into the file
5. The script will create the expect script exp2.exp which checks in the passwd file with a log input "anything/r" and will run the script
6. The script will then remove the passwd file and create a symlink between passwd and etc/passwd
7. The script will then create an expect script exp3.exp that will check out the passwd file, replacing the contents of /etc/passwd with the contents of the previous passwd file
8. The script will create an expect script exp4.exp that will log the student out and back in to refresh the permissions
9. The script will run the expect script that checks out the passwd file, so that the contents of the previous passwd file are overwritten to the etc/passwd file, as the passwd file now is a symlink
10. The script will run the script that will log the user out and back in to refresh permissions