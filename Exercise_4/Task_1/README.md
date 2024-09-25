
## How to run the code?
Inside the 'scripts' folder, you will find one script for compiling and another one for running the program. They are named 'compile.sh' and 'run.sh', so it should be obvious what each script does.

## Verify that the program prints to standard error
If you look inside 'run.sh', you will see that standard output is routed to /dev/null.
Thus if you see any output from the program on the command line, it can only be output from standard error.
Try routing standard error to /dev/null instead, and you will not see any output from the program.

## Verify that the program returns an error code
The programs exit code is printed by the script 'run.sh'. Note that this is not considered a part of the programs output, since it is coming from a call to 'echo' after the program has exited.