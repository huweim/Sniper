#include "simulator.h"
#include "perceptron_branch_predictor.h"
#include <vector>
#include <iterator>
using namespace std;

PerceptronBranchPredictor::PerceptronBranchPredictor(String name, core_id_t core_id, UInt32 size)
    :BranchPredictor(name, core_id)
{  // TODO 先实例化
    weight.resize(size_set);
    globalhistory.resize(size_set);
    for(int i=0;i<size_set;i++){
        weight[i].push_back(1);   // w0 is always 1
        for(int j=0;j<num_of_history;j++){
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

PerceptronBranchPredictor::~PerceptronBranchPredictor(){
}


bool PerceptronBranchPredictor::predict(IntPtr ip, IntPtr target){  //predict后会执行function update  ip和target能对应
    UInt32 index = ip % size_set;
    y=0;
    for(int i=0;i<num_of_history;i++){
        y+=weight[index][i+1]*globalhistory[index][i];
    }
    y+=weight[index][0];  //(sum of weight[i])+weight[0]
    //printf("called predict %d %d %d %d %d",ip,target,index,y,result);
    return (y>=0)? 1 : 0;
}
//int count = 0;
void PerceptronBranchPredictor::update(bool predicted, bool actual, IntPtr ip, IntPtr target)
{
    updateCounters(predicted, actual);   
    UInt32 index = ip % size_set;  
    int temp;
    
    if(actual)
        temp=1;
    else
        temp=-1;
    //printf("called update %d %d %d %d %d %d \n",predicted,actual,ip,target,index,y);
    if(predicted != actual || y < threshold){
        //count++;
        //printf("called update %d %d %d %d %d %d \n",actual,predicted,index,weight[index][15],globalhistory[index][15],count);
        for(int i = 1; i < num_of_history+1; i++){
            //if(weight[index][i]<50&&weight[index][i]>-50)   //防止weight过大
                weight[index][i] += globalhistory[index][i-1]*temp;
        }
    }  
    globalhistory[index].push_back(temp);
    globalhistory[index].erase(globalhistory[index].begin()+1); 
    //weight[index].push_back(1);
    //weight[index].erase(weight[index].begin()+1); 
}