# Goal
Through Lab 2, you would modify the branch prediction subsystem of Sniper for one target:
Add a **perceptron-based** dynamic branch prediction algorithm that can be used by the simulated CPU core.
You can refer to the following research paper for how to make it.
D. A. Jimenez and C. Lin, *Dynamic branch prediction with perceptrons,* Proceedings HPCA Seventh International Symposium on High-Performance Computer Architecture, Monterrey, Nuevo Leon, Mexico, 2001, pp. 197-206, doi: 10.1109/HPCA.2001.903263.

Like Lab 1, you also need to devise test cases by yourself to justify that your perceptron-based branch predictor is sound, effective and efficient. A comparison to existing branch prediction algorithm of Sniper is essential.


# Due date for Lab2
23:59:59 (UTC+8), Wednesday, 9th December, 2020


# Deliverables
1. A report about what you modify/add in the source code of Sniper, including the file(s) and function(s), how you achieve the target, your observations in implementing and testing, the challenges you face, the overhead caused by perceptrons, and so on. In particular, you need to compare your branch prediction algorithm to Sniper's existing branch prediction algorithms with quantitative analysis. Make a readable and neat report.

2. Source codes of modified and/or newly-added files, and a README on which folder(s) to put these files into and how to compile your modified Sniper. This is for reproduction of your results. You can provide a downloadable link of your source codes. However, only put your link of source codes in the report. Do never share it with others.

3. Source codes of test cases.


# Guidelines

Refer to the aforementioned paper published in HPCA '01 for reference.

Although you are given seven weeks to do such a branch predictor, it is strongly recommended that you start this lab **as early as possible**.

You can use the config file of Lab 0 and Lab 1 for Lab 2. Make sure you add one more option for configuring `perceptron'-based branch prediction.

Submitted source codes must be with comments and descriptions.

Bonus points would be accredited to students that submit interesting and reasonable results. Just for one example, an insightful and sound discussion on different and state-of-the-art branch prediction algorithm with implementations and experiments would be a plus. 

