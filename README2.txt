In this exploit, we find that bcvs only checks the path of the file given in the beginning of the program, when it checks the 
file that we passed in.
After the initial check of the file, where the program checks if the file's real path is in the block list, 
the file's real path is not inspected further. They also offer an opportunity, when they ask for an
input, to pause the program by using Ctrl-z and do what ever we want to the file that we passed in,
like deleting the file and adding in a symlink that has the same path as name as the original
so when it goes in to check in or checkout the file, the one that is checked in or out is different from the one that we passed in.

We took advantage of this exploit by checking in an empty file, specifically 
file.txt. We then checked out that same file, but when it asked for a log, we made the program sleep for a certain amount of time.
We then deleted the file.txt and ran a python program that created a symlink from .bcvs/block.list
to a new file that was also called file.txt. This made it so that when we resumed the program,
it wrote to the .bcvs/block.list, since file.txt is a symlink to .bcvs/block.list, and it was writing to file.txt.
Because bcvs did not check the file path before checking in or checking out, it was possible for the file to write to our 
block.list file

Now because /etc/passwd is no longer on the blocklist, we were then able
to check in an file called passwd which had changes to root permissions and then 
checked out the passwd file, which replaced our passwd file to the one that we checked in, which 
changed our permissions to root.
We then ran a exp script that signed out and signed back into the student account, and we had
root permissions

Something that was weird was that when a program was spawned, the spawn_id 
was null. We approached the professor about this issue, and he suggested me instead of using
the spawn_id and spawning a new program inside of the same exp file, to run 2 
exp files at the same time, and have each of them sleep for a certain amount of time
so that when the program asks for a log input, we sleep, then the python program wakes up, 
it will add the symlink, then the original program will continue. 

