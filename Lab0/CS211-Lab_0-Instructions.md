# Goal
Through this lab, you would compile Sniper, a next-generation parallel, 
high-speed and accurate x86 simulator **[0.5 points]**. Then you need to modify the source code of Sniper to show expected output and upload a summary to BlackBoard **[1.5 points]**. Total is 2 points.


# Due date for Lab0
23:59:59pm (UTC+8), Wednesday, 23rd September, 2020


# Deliverable
A summary about what you modify in the source code of Sniper, including 
the file(s) and function(s).


# Instruction on how to compile Sniper

## Main Page of Sniper
<https://snipersim.org/w/The_Sniper_Multi-Core_Simulator>


## Prerequisites
    OS: Ubuntu 16.04, 18.04, or 20.04
    gcc: 7.5.0 or 9.3.0


## Compile Sniper
1. Get the Sniper source code from Blackboard, or from [link](http://pan.shanghaitech.edu.cn/cloudservice/outerLink/decode?c3Vnb24xNTk5NTY2MTAwOTgzc3Vnb24=), or find it alongside this instruction file.
2. Uncompress the Sniper compressed file.
3. Input these commands in terminal
```
$ cd $PATH-to-SNIPER 
$ sudo dpkg --add-architecture i386
$ sudo apt-get install binutils build-essential curl git libboost-dev libbz2-dev libc6:i386 libncurses5:i386 libsqlite3-dev libstdc++6:i386 python wget zlib1g-dev
$ make
$ cd test/fft; make run
```

##Notes：
1. Use python2, if there are errors about python, check the version of python.
2. If with "make" you see following error, please type "chmod -R +x ./" and retry.
```
Building for x86 (intel64)
/bin/sh: 1: ./tools/checkdependencies.py: Permission denied
make: *** [Makefile:175: package_deps] Error 126
```



# The task of Lab 0

Two files are provided for Lab 0. One is a config file, i.e., config-lab0.cfg.
The other one is toy-lab0.c, which is a C file. Use GCC to compile the C file,
$ gcc toy-lab0.c -o lab0.exe -Wall -O3
and run lab0.exe with your local machine, you should see following outputs.
```
$ ./lab0.exe
User program begins
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
User program ends
$
```
We note that clflush is an interesting instruction of x86. In toy-lab0.c,
it is called for four times to flush four cache lines. Read Lines 17-25 of
toy-lab0.c for details.


Now, if you use unmodified Sniper to run the executable file with the 
config-lab0.cfg config file, you should see following output.
```
$ ./run-sniper -c $PATH-TO-LAB0/config-lab0.cfg -- $PATH-to-LAB0/lab0.exe
[SNIPER] Warning: Unable to use physical addresses for shared memory simulation.
[SNIPER] Start
[SNIPER] --------------------------------------------------------------------------------
[SNIPER] Sniper using SIFT/trace-driven frontend
[SNIPER] Running full application in DETAILED mode
[SNIPER] --------------------------------------------------------------------------------
[SNIPER] Enabling performance models
[SNIPER] Setting instrumentation mode to DETAILED
[RECORD-TRACE] Using the Pin frontend (sift/recorder)
User program begins
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
<toy-lab0.c, clflush, 21> clflush to be run
User program ends
[TRACE:0] -- DONE --
[SNIPER] Disabling performance models
[SNIPER] Leaving ROI after 4.97 seconds
[SNIPER] Simulated 0.2M instructions, 0.4M cycles, 0.52 IPC
[SNIPER] Simulation speed 44.7 KIPS (44.7 KIPS / target core - 22374.4ns/instr)
[SNIPER] Setting instrumentation mode to FAST_FORWARD
[SNIPER] End
[SNIPER] Elapsed time: 5.12 seconds
$
```

<i>What you need to do is modify the source code of Sniper, recompile and rerun 
the above toy example</i>. What is expected to see is as follows.
```
$ ./run-sniper -c $PATH-TO-LAB0/config-lab0.cfg -- $PATH-to-LAB0/lab0.exe
[SNIPER] Warning: Unable to use physical addresses for shared memory simulation.
[SNIPER] Start
[SNIPER] --------------------------------------------------------------------------------
[SNIPER] Sniper using SIFT/trace-driven frontend
[SNIPER] Running full application in DETAILED mode
[SNIPER] --------------------------------------------------------------------------------
[SNIPER] Enabling performance models
[SNIPER] Setting instrumentation mode to DETAILED
[RECORD-TRACE] Using the Pin frontend (sift/recorder)
User program begins
<toy-lab0.c, clflush, 21> clflush to be run
[STUDENT-EMAIL-ACCOUNT, function, line number] CLFLUSH instruction executed
<toy-lab0.c, clflush, 21> clflush to be run
[STUDENT-EMAIL-ACCOUNT, function, line number] CLFLUSH instruction executed
<toy-lab0.c, clflush, 21> clflush to be run
[STUDENT-EMAIL-ACCOUNT, function, line number] CLFLUSH instruction executed
<toy-lab0.c, clflush, 21> clflush to be run
[STUDENT-EMAIL-ACCOUNT, function, line number] CLFLUSH instruction executed
User program ends
[TRACE:0] -- DONE --
[SNIPER] Disabling performance models
[SNIPER] Leaving ROI after 4.99 seconds
[SNIPER] Simulated 0.2M instructions, 0.4M cycles, 0.52 IPC
[SNIPER] Simulation speed 44.5 KIPS (44.5 KIPS / target core - 22471.6ns/instr)
[SNIPER] Setting instrumentation mode to FAST_FORWARD
[SNIPER] End
[SNIPER] Elapsed time: 5.14 seconds
$
```

Note: <i>Replace [STUDENT-EMAIL-ACCOUNT, function, line number] using your ShanghaiTech account,
the function you modify, and the line number in the modified file(s) of Sniper, respectively.</i>



