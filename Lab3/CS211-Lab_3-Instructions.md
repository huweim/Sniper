# Goal

In Lab 3, you would have up to four targets with respect to CPU cache coherency (the first one has no point, and the last one is **optional**).
1. Find two sample files for Lab 3. One is config-sample-lab3.cfg, and the other one is lab3-multithreads-sample.c. Compile the c file using command `gcc lab3-multithreads-sample.c -o mt.exe -Wall -pthread' and you would get an executable file named mt.exe. Run it with Sniper using the sample configure file config-sample-lab3.cfg and sampling. Note that these two files are just for sampling. To achieve targets 2--4, you may need to modify either or both of them, or replace either or both of them. For example, in lab3-multithreads-sample.c, all threads use the same function but do not have much data shared. You need to consider how to trigger coherency traffics for following targets.
2. Develop test cases to show the impact of **false sharing** of cache lines among multiple threads with Sniper. You need to consider varying cache block size, cache size, cache coherency policy and so on. Make a comprehensive, quantitative evaluation and presentation.
3. Through Lab 1, you shall be able to configure a multi-level cache to be inclusive or non-inclusive. The original Sniper simulator contains three options for cache coherency, i.e., MSI, MESI, and MESIF. Configure such coherency protocols with your inclusive and non-inclusive multi-level caches with multi-threading program(s) for possible compositions, and make a comprehensive, quantitative evaluation and presentation.
4. The MESIF protocol contained in Sniper is a cache coherency and memory coherence protocol developed by Intel for cache coherent non-uniform memory architectures. AMD64 has another coherency protocol called MOESI. You can find more details on MOESI protocol by referring to [link](https://www.amd.com/system/files/TechDocs/24593.pdf).


# Due date for Lab 3
23:59:59 (UTC+8), Sunday, 13th December, 2020


# Deliverables
1. A report about how/why you develop test cases and what you modify/add in the source code of Sniper, including the file(s) and function(s), how you achieve the targets, your observations in implementating and testing, the challenges you faces, and so on. Make a readable and neat report.

2. Source codes of all test cases. Organize them in a structured layout.

3. Source codes of modified and/or newly-added files, and a README on which folder(s) to put these files into and how to compile your modified Sniper. This is for reproduction of your results. You can provide a downloadable link of your source codes. However, only put your link of source codes in the report. Do never share it with others.


# Guidelines

Although you are given 24 days to do Lab 3, it is strongly recommended that you start this lab **as early as possible**.

Submitted source codes must be with comments and descriptions.

Bonus points would be accredited to students who submit interesting and reasonable results. For example, students who correctly accomplish the fourth target with MOESI protocol would receive bonus points.

