In this exploit, we aim for the real path function. We find that the real function finds the absolute path that the file is pointing to,
for example, when given a symlink, the real path function will pass back the path to the file that the symlink is pointing to. However, the 
name of the file that is passed in is never changed or modified, so that when bcvs goes to check in and checkout the file, it will checkout 
and check in the file that was passed in, not the file that was being pointed to by the symlink.

So in this case, we passed in a file called block.list, which was a symlink to a file called file.txt, which had nothing in it.
When bcvs went to go and check that the file path was not one of the file paths in the block list, it saw the file.txt path instead of the 
block.list file path. So it let us write a log, check in and check out. However, when it came time for the program to check out and check in the 
file, it checked out and checked in block.list file, which we used to wipe our block.list, so that no files were blocked anymore

This let us be able to check in a modified passwd file which granted the student user root privieges. We then checked out that passwd file, which 
modified our own passwd file to the modified on that we sent in. 

We ran su student, which logged us out and back in, and when we came back, we had root privieges