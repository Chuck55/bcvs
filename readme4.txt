Stack smashing is difficult. But I would like to explain what we tried, what we did, and how far we got.

(Even though are sploit doesn't really work, we spent two straight days trying to make it work. We worked
about 24 hours each on this exploit alone. The thing is, we didn't know that the stack smashing exploit
was required until Thursday (yesterday), the day before the assignment was due because of the unclear
wording in the assignment instructions, so we didn't even try it until the day before, and we kept
working on it non-stop until the deadline. We hope that this readme will be able to give us some partial
credit possibly. It would be really nice to know that all that hard work was not for nothing)

Honestly, this stack smashing was a journey. It was difficult to know where to start, but after reading
and re-reading Aleph One's Smashing The Stack For Fun And Profit, there were some things we tried.

Before I discovered that link, I tried a couple other things based on my understanding of stack smashing
from the lectures. First of all, inside the CopyFile function is a strcpy() call that takes in a src
buffer which is 72 characters long and also an argument - which is the file name. The strcpy() copies
the argument into the src buffer.

Now, to try to find the return address, I first used printf statements, with format of %x and %p, and
even though I counted the bytes. 72 for the src buffer, 4 for the chmodString, 8 and 8 for each of the
pointers, 72 for the tempString, 16 for the user, 4 for the status, 4 for the pid, 4 for i and 4 for c,
which adds up to a total of 196 bytes, I found something strange.

It turned out that the return address for the copyFile function occurred at the 81st byte in the stack.
In addition, in order to write to it to override it, you would have to write until the 55th byte.

None of those numbers matched. Even when I successfully overwrote the return address with something else,
it wouldn't work.

That's when I found Aleph One's Smashing The Stack For Fun And Profit.

In the sploit4.sh file, there's a C file written in there that is basically pulled from that website,
with a few modifications. That code uses a shellcode and a NOP sled to get at a memory address and
return something we have control over.

The buffer that we have created, filled with a NOP sled and a shellcode that will execute a bash,
is now to be put in an environment variable, labeled as EGG.

We then use EGG to be returned into our bcvs executable. So, we run ./bcvs ci $EGG, and for the most
part, it was able execute, but sometimes it would seg fault or have an illegal command.

(Also, as a sidenote, initially we tried the one about the smaller buffer where we use RET instead
of EGG as an argument command, but for some reason RET was turning out empty every time I used it
so it didn't work, even though EGG wasn't coming out empty, so we ended up going with the one
without RET, which seemed to at least be able to put a buffer in an environment variable successfully)

In the end, I believe we were close to getting it to work, but it was a matter of finding the right
numbers to put in as the buffer and as the offset, as well as probably a few other factors that 
hadn't been considered.

At first, we had thought that we were successfully overwriting the memory address (according to the
printf's), so we looked at the shellcode.

When we ran the shellcode by itself without the bcvs executable, we found that every shellcode we
pulled off the Internet resulted in a seg fault. I checked that we were using Linux Intel x86_64
shellcodes, and still, they all resulted in a seg fault. But finally, after tons of tries, I was able to 
get one to work.

So now that we confirmed that the shellcode worked, and we thought the return address had been overwritten
correctly, I continually tried to do different combinations of numbers, some of them educated guesses
based on my knowledge of the stack, our buffer, and what is in the function.

Some of them were more random guesses. But every single one of them had issues. We were not able to get
any of them to work.

So, now, that we have run out of time, I think that the issue lies in either the C file itself. Maybe
there are more modifications to be made specific to our machine or to the function itself. Or the issue
could lie in not knowing what numbers to put in for buffer and offset.

If there was more time, we could probably get this to work, but seeing as we have run out of time, it
is time to turn this in and hope for the best.
