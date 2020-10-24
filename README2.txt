Mistakes in the source code :

In this exploit, we find that bcvs only checks the path of the file given in the beginning of the program, when it checks the 
file that we passed in.
After the initial check of the file, where the program checks if the file's real path is in the block list, 
the file's real path is not inspected further. They also offer an opportunity, when they ask for an
input, to pause the program by using Ctrl-z and do what ever we want to the file that we passed in,
like deleting the file and adding in a symlink that has the same path as name as the original
so when it goes in to check in or checkout the file, the one that is checked in or out is different from the one that we passed in.


How we constructed our inputs:

We took advantage of this exploit by checking in an empty file, specifically file.txt, which was going to be the file later replaced by a symlink. We also checked in a file
called passwd, which contained the contents that we wanted to overwrite the /etc/passwd file with. 
We then checked out file.txt, but when it asked for a log message, we made the program sleep for a certain amount of time. This is so that can call our python function, which 
deletes file.txt and then creates a new file called file.txt, which is a symlink from .bcvs/block.list. We do this so that when we send a message to the log, the program will resume and start to 
copy the contents of the file.txt stored in it's repository to the file.txt that we own, however, because file.txt is now a symlink to .bcvs/block.list, and since the program does not check
the real path of file.txt, when the program starts to copy the contents of the file.txt in it's repository, it now writes it all to .bcvs/block.list, and since our origional file.txt was empty,
this means that .bcvs/block.list is now empty as well. 

Now because block.list is now empty, this means that we can check in and checkout any of the blocked files from before. This means that we can checkout /etc/passwd. 
But this would not do anything right now, since checking out the passwd we checked in at the beginning of the script wouldn't do anything. We now need to delete the passwd file that we have, and create
a new passwd file that is a symlink to the /etc/passwd file, so that now, when we checkout passwd, it will overwrite everything in /etc/passwd with the contents of our previous passwd file.

Once we do this, all we need to do now is to log out of our user, which refreshes the permssions of our student account, and we now have root permissions.

Something that was weird was that when a program was spawned, the spawn_id 
was null. We approached the professor about this issue, and he suggested me instead of using
the spawn_id and spawning a new program inside of the same exp file, to run 2 
exp files at the same time, and have each of them sleep for a certain amount of time
so that when the program asks for a log input, we sleep, then the python program wakes up, 
it will add the symlink, then the original program will continue. 

What happens when an ordinary user runs sploit2.sh:

1. The script will first navigate to the /opts/bcvs directory
2. The script will create both the python file that creates a symlink, and the empty file.txt
3. The script will create the script run.sh that will run the python program, but will first sleep for a certain amount of time
4. We then check in file.txt into .bcvs with an log input of "HELLO"
5. The script will create a passwd file, create a variable that stores the path to passwd, and stores the root permissions into the variable
6. The script will create the expect script stuff.exp which checks in the passwd file with a log input "anything3/r"
7. The script will create another expect script both.exp, which will run both the expect scrip that checks out file.txt and the script that creates a symlink between file.txt and .bcvs/block.list
8. The script will then create the expect script firstexp.exp that will check out file.txt, but will sleep when expecting a certain input, so that the symlink can be created. Afterwords, will send "anything/r"
9. The script will then create an expect script secondexp.exp that will check out the passwd file that we checked in earlier
9. The script will create an expect script thirdexp.exp that will log the student out and back in to refresh the permissions
10. The script will run the command chmod +X on all the scripts
11. The script will run the script that checks in the passwd file
12. The script will run the script that runs the script that checks out the file.txt and creates a symlink
13. The script removes the passwd file and creates a symlink between the etc/passwd file and a newly created passwd file
14. The script will run the script that checks out the passwd file, so that the contents of the previous passwd file are overwritten to the etc/passwd file, as the passwd file now is a symlink
15. The script will run the script that will log the user out and back in to refresh permissions