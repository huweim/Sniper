+ 文件branch_predictor.cc的修改

  + 位置`/sniper/common/performance_model/branch_predictor.cc`

  + 加上自己写的头文件`#include "perceptron_branch_predictor.h"`

  + 函数create中添加语句，以进入分支，创建自己的感知机class
  
  + ```c++
    else if (type == "perceptron")
          {
             UInt32 size = cfg->getIntArray("perf_model/branch_predictor/size", core_id);
             return new PerceptronBranchPredictor("branch_predictor", core_id, size);
        }
    ```
  
  + 函数updateCounters用print打印测试结果
  
+ sniper文件夹下`config-lab0.cfg`

  + 文件`24`行type，把sniper用的奔腾`pentium_m`修改为自己写的算法，我用的perceptron
    <img src="D:\STU\2020-Fall\Core Courses\Computer ArchitectureII\Lab\Lab2\summary\Test\First test_perceptron_1024-30.png" alt="First test_perceptron_1024-30" style="zoom: 50%;" />

+ 自己写一个perceptron_branch_predictor.h和perceptron_branch_predictor.cc文件

+ 测试结果比奔腾优秀即可，更好的命中率可能可以通过优化（增加感知机层数）或比较特殊的case达到