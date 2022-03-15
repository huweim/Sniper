# Summary of Lab 2

Name: hu weiming                    Major: Master in CS

Student No: 2020233177         E-mail: huwm1@shanghaitech.edu.cn

## perceptron-based dynamic branch prediction algorithm

​		In the Lab 2, I write two files named `perceptron_branch_predictor.h` and `perceptron_branch_predictor.cc`. I use the perceptron algorithm based on the paper `Dynamic branch prediction with perceptrons`. The perceptron algorithm would update the weight dynamically according to the history table. It is not difficult to implement in hardware, and can achieve a lower misprediction rate. Like Branch Predictor one_bit and Pentium, there are two key functions, *predict* and *update*. The function `predict` return the result of predicting, and the function `update` is used to update the the table of weight and global history according to  the result of prediction and fact. 

​		I need to insert the latest result from the tail and delete the farthest result after every prediction, so I choose a two-dimensional **vector** array. I define it in the header file and initialize the number of rows of the vector to 1024 in the constructor, because the *m_bits.size()* in *one_bit_branch_predictor* is 1024. And according to the paper, *"the best history lengths ranged from **12 to 62**, depending on the hardware budget".* So I initialize the number of columns of the two-dimensional array to 50, x0 is always set to 1, providing a “bias” input. 

​		However, the number of columns in a two-dimensional array is not fixed and can be adjusted according to different situations. In my test, I set it to 50. I think a relatively long table can reduce the contingency of prediction.

## How I Achieve it

### Ideal and Process

​		The realization idea of this algorithm is mainly based on paper `Dynamic branch prediction with perceptrons`. Now describe the process of conception and realization. First, observe the structure of Branch Predictor `one_bit` and `Pentium`. Therefore, I need to implement the two functions in the perceptron predictor. Secondly, in the function `create` of `branch_predictor.cc`,  according to the predictor type in the config file, it returns a string to decide which predictor to use. So we need to create a new if-else branch in the function `create` and the name of type is "perceptron". Besides, we can use the function `updateCounters` to print the number of correct and incorrect predictions to judge the effect of the predictor, or find the result in `sim.out` .

```c++
else if (type == "perceptron")
      {
         UInt32 size = cfg->getIntArray("perf_model/branch_predictor/size", core_id);
         return new PerceptronBranchPredictor("branch_predictor", core_id, size);
      }
```

​		About the perceptron algorithm, I use two vector arrays as the global history array and the weight array. Two-dimensional arrays are more convenient to implement dynamic updates, and their length can be modified at any time. I initialized the two arrays as follows in the constructor.

```c++
PerceptronBranchPredictor::PerceptronBranchPredictor(String name, core_id_t core_id, UInt32 size)
    :BranchPredictor(name, core_id)
{  
    weight.resize(size_set);
    globalhistory.resize(size_set);
    for(int i=0;i<size_set;i++){
        weight[i].push_back(0);  
        for(int j=0;j<num_of_history-1;j++){
            weight[i].push_back(0);
        }
    }
    for(int i=0;i<size_set;i++){
        globalhistory[i].push_back(1);   // x0 is always 1,bias
        for(int j=0;j<num_of_history-1;j++){
            globalhistory[i].push_back(0);
        }
    }    
}
```

### Implemented Code

#### Predict

```c++
bool PerceptronBranchPredictor::predict(IntPtr ip, IntPtr target){  
    UInt32 index = ip % size_set;
    y=0;
    for(int i=0;i<num_of_history;i++){
        y+=weight[index][i]*globalhistory[index][i];
    }
    return (y>0)? 1 : 0;
}
```

​		*size_set* is used to group index. The output y of a perceptron is computed as `y=W0+∑Xi*Wi`, this calculation formula is quoted from the paper provided by the Professor Wang. Besides, I always set X1 to 1 as a bias. And I return the result according to the output `y`, it is easy to understand. 

<img src="C:\Users\50683\AppData\Roaming\Typora\typora-user-images\image-20201209191626081.png" alt="image-20201209191626081" style="zoom: 67%;" />.

#### Update

```c++
void PerceptronBranchPredictor::update(bool predicted, bool actual, IntPtr ip, IntPtr target)
{
    updateCounters(predicted, actual);   
    UInt32 index = ip % size_set;  
    int temp;
    if(actual)
        temp=1;
    else
        temp=-1;
    if(predicted != actual || abs(y) < threshold){
        for(int i = 0; i < num_of_history; i++){
            if(weight[index][i]<50&&weight[index][i]>-50)   //avoid a very large weight
                weight[index][i] += globalhistory[index][i]*temp;
            else if(weight[index][i]>=50)  //avoid a very large weight and keep update
                weight[index][i]=49;
            else if(weight[index][i]<=-50)
                weight[index][i]=-49;
        }
    }  
    globalhistory[index].push_back(temp);
    globalhistory[index].erase(globalhistory[index].begin()+1); 
}
```

​		I have to say how to update is the key of *perceptron prediction*. After prediction, we need to update the arrays of global history table and weight. 
<img src="C:\Users\50683\AppData\Roaming\Typora\typora-user-images\image-20201122210612298.png" alt="image-20201122210612298" style="zoom: 50%;" />.

​		Updating the array of weight by this way which from the paper. I set the threshold `θ` to 111. θ equal to `1.93*size_set+14`. And for global history table, I just push back the latest result and erase the furthest, it also explains why I choose the **vector**. According the the paper, ` Because the training algorithm will only change a weight when the magnitude of yout is less than the threshold θ, no weight can exceed the value of θ`. So I also set a threshold of weight, let it could be updated and would not be so large.

## Challenge 

​	In general, the implementation of the lab is not difficult, and the results of the prepared test cases are also not bad. So I mainly want to focus on its hardware overhead. It is not difficult to implement the two functions, but the lab also encountered some difficulties this time.

1. Initialization of the size of the two-dimensional array. Strictly speaking, it is a problem in the constructor. The two-dimensional array must be initialized to a size and cannot be implemented in the header file, so it needs to be executed in the constructor.
2. Find where Sniper calls the predictor. Although the predictor can be completed using only the parameters passed in, understanding the logic of the call may be more conducive to optimization. Sniper calls the predictor in the `accessBranchPredictor` function in the `core.cc` file.
3. Consider the size of `size_set`. There are 1024 sets in `one_bit`. At the beginning, it was considered that a small exe was only about 50,000 branch predictions, such as `lab0.exe`. 1024 sets will cause the two tables in most sets to not be updated, thus failing to play the role of the perceptron algorithm. But later, considering that `one_bit` is also set to 1024, and the CPU does not always serve some small programs, so the size_set is still set to 1024.

## Testing of Result

### Hit Rate and Miss Rate

#### First 

​		I define it in the header file and initialize the number of rows of the vector to 1024 at first, then I also discovered a **problem** with this. For *lab0.exe*, a total of about 50000 branch predictions have been performed, but there are 1024 sets, and a global history table and weight table with a length of 30 (first test), which means there are many data in the table has never been updated. In other words, too many sets will cause this method to play a small role in prediction. Although its prediction accuracy is still better than Pentium (the default predictor), there is no qualitative improvement. Actually, the prediction correct rate has increased from 89.40% (41188/46593) to 92.21% (42963/46593), it can be said that there is almost no improvement. This is better than the one_bit predictor (85.59% 39878/46593). But considering the simplicity of the one_bit algorithm, this is not a comforting improvement.

​												Figure 1 perceptron(left) and pentium_m(right)

<img src="Result\First test_perceptron_1024-50.png" alt="First test_perceptron_1024-50" style="zoom: 34%;" /><img src="Result\First test_pentium_1024-50.png" alt="First test_pentium_1024-50" style="zoom: 35%;" />

#### Second

​		At this test, I changed the index grouping by **ip** to grouping by **target**. The target may be the address where the instruction is about to jump, so the grouping may be more regular. This address will be used for prediction and update in Pentium. After making this change, the hit rate has improved significantly and has reached a relatively ideal hit rate. The prediction correct rate has increased from 88.36% (41171/46593) to 97.78% (45557/46593), this is a pretty good improvement. I searched it and found that this hit rate can be put into practical use for some small-scale programs without increasing hardware overhead. But in large-scale programs or real computer, this hit rate cannot be said to be excellent.

​											Figure 2 perceptron(left) and pentium_m(right)

<img src="Result\Secondtest_perceptron_1024_50.png" alt="Secondtest_perceptron_1024_50" style="zoom:33%;" /><img src="Result\Secondtest_pentium_1024_50.png" alt="Secondtest_pentium_1024_50" style="zoom: 33%;" />

​		I searched it and found that this hit rate can be put into practical use for some small-scale programs without increasing hardware overhead. But in large-scale programs or real computer, this hit rate cannot be said to be excellent.

#### Another Case to Verify

​		**I‘m not sure if it is correct to use `target` to group, although the target is obtained during the execution of the instruction, it should be reasonable. But one_bit uses `ip` for grouping, so I still use `ip` address grouping for testing.**I used the quick sort algorithm used in lab1 for verification, and the results are as follows. This result ruled out the contingency of a single program and reached a good hit rate level (99.5%).

​			Figure 3 perceptron(target to group), perceptron(ip to group) and pentium_m

<img src="Result\Thirdtest_perceptron_sort.png" alt="Thirdtest_perceptron_sort" style="zoom: 25%;" />.<img src="Result\Thirdtest_perceptron_sort_ip.png" alt="Thirdtest_perceptron_sort_ip" style="zoom: 25%;" />

<img src="Result\Thirdtest_pentium_sort.png" alt="Thirdtest_pentium_sort" style="zoom: 25%;" />

#### Another Case

​		I used the programming homework in CS290P as a case. This `hw1.cc` is to implement the function of printing calendar. This is a relatively large program, about 600 lines of code, and will be judged many years, months and days. The hit rate can reach 99.31%. It is close to reality and has the opportunity to be put into use.

​		Figure 4 perceptron(target to group), perceptron(ip to group) and pentium_m

<img src="Result\Forthtest_perceptron_hw1.png" alt="Forthtest_perceptron_hw1" style="zoom: 25%;" /><img src="C:\Users\50683\AppData\Roaming\Typora\typora-user-images\image-20201209211257420.png" alt="image-20201209211257420" style="zoom: 25%;" />

<img src="Result\Forthtest_pentium_hw1.png" alt="Forthtest_pentium_hw1" style="zoom: 25%;" />



### Overhead

​		In general, the implementation of the lab is not difficult, and the results of the prepared test cases are also not bad. So I mainly want to focus on its hardware overhead. And the authors of paper said `Perceptrons are a natural choice for branch prediction because they can be efficiently implemented in hardware.` Therefore, no additional circuits are required on the hardware, and it will not bring great overhead. In terms of software operating efficiency, it hardly affects the speed of code running.
