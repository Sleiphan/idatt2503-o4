## What happens when only the library is recompiled?
What happens is that the library binary changes without the main program binary having to change. This means that the behaviour of the library can change without the consumer program having to change. You are effectively able to change the behaviour of another program without access to its source code.

This is one of the perks of using a dynamically linked library: the developers of the library can update the code without forcing the consumers to also rebuild their own code. The users just have to download (and maybe compile) the new library, and everything should be fine.

However, this has a downside. An attacker could replace library binaries with their own binaries. When the victim runs code that is supposed to use that library, the attacker's code will be run instead. This is important to consider when choosing between dynamic and static library linkage.