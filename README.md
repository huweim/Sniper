# README

```c++
gcc toy-lab0.c -o lab0.exe -Wall -O3   //get the lab0.exe
gcc toy-lab0.c -o sort.exe -Wall -O3   //get the sort.exe
```

## 1. File IO

### (1). Initial future_list

+ In **cache.h**

+ add ``static long long int future_list[1000000][2];`` to the      //  I have **already** added it.

  ```c++
  class Cache : public CacheBase
  {public: 
  	static long long int future_list[1000000][2];
  }
  ```

+ I have **already** added it.

### (2). Write

+ Creating a file "**future_list.txt**" in the same directory as the sniper file.

+ in **cache.cc**, add the head file as follows. Only modifying in function **accessSingleLine**. 

+ First, comment out the **read file operation** and keep the **write file operation** as follows.

+ Second, make                 ``make``
  and run the program  ```./run-sniper -c ./config-lab0.cfg -- ./lab0.exe``

+ Third, we get a file "future_list.txt" with access sequence.

```c++
#include "simulator.h"
#include "cache.h"
#include "log.h"
#include <array>
#include <fstream>

long long int Cache:: future_list[1000000][2]={0};
int read_condition=0;
CacheBlockInfo*
Cache::accessSingleLine(IntPtr addr, access_t access_type,
      Byte* buff, UInt32 bytes, SubsecondTime now, bool update_replacement)
{
   //assert((buff == NULL) == (bytes == 0));

   IntPtr tag;
   UInt32 set_index;
   UInt32 line_index = -1;
   UInt32 block_offset;

   splitAddress(addr, tag, set_index, block_offset);
   CacheSet* set = m_sets[set_index];
   CacheBlockInfo* cache_block_info = set->find(tag, &line_index);  
    
   if (cache_block_info == NULL)
      return NULL;  
   // *********************************************************write file operation
   set_index=set_index%512;
   ofstream outfile;
   outfile.open("future_list.txt",ios::app);
   outfile <<set_index<<" "<< tag << endl;
   outfile.close();
   //*********************************************************write file operation

   // *******************************************read file operation
   // if(read_condition==0){  
   //    ifstream infile; 
   //    infile.open("future_list.txt",ios::in); 
   //    while (!infile.eof())
   //    {
   //       infile>>set_index>>tag;
   //       future_list[read_condition][0]=set_index;
   //       future_list[read_condition][1]=tag;
   //       read_condition++;
   //    }
   //    infile.close();
   // }
   //*******************************************read file operation

   if (access_type == LOAD)  
   {
      if (m_fault_injector)   
         m_fault_injector->preRead(addr, set_index * m_associativity + line_index, bytes, (Byte*)m_sets[set_index]->getDataPtr(line_index, block_offset), now);

      set->read_line(line_index, block_offset, buff, bytes, update_replacement);  
   }
   else
   {
      set->write_line(line_index, block_offset, buff, bytes, update_replacement);
      if (m_fault_injector)
         m_fault_injector->postWrite(addr, set_index * m_associativity + line_index, bytes, (Byte*)m_sets[set_index]->getDataPtr(line_index, block_offset), now);
   }

   return cache_block_info;
}
```

###  (3). Read

+ First, comment out the read file operation and keep the write file operation as follows.

+ Second, make                 ``make``
  and run the program  ```./run-sniper -c ./config-lab0.cfg -- ./lab0.exe``

+ Then we will get the result of OPT algorithm. View the results in the **sim.out** file.

```c++
#include "simulator.h"
#include "cache.h"
#include "log.h"
#include <array>
#include <fstream>

long long int Cache:: future_list[1000000][2]={0};
int read_condition=0;
CacheBlockInfo*
Cache::accessSingleLine(IntPtr addr, access_t access_type,
      Byte* buff, UInt32 bytes, SubsecondTime now, bool update_replacement)
{
   //assert((buff == NULL) == (bytes == 0));
   IntPtr tag;
   UInt32 set_index;
   UInt32 line_index = -1;
   UInt32 block_offset;

   splitAddress(addr, tag, set_index, block_offset); 
   CacheSet* set = m_sets[set_index];
   CacheBlockInfo* cache_block_info = set->find(tag, &line_index); 

   if (cache_block_info == NULL)
      return NULL;
   
   // *********************************************************write file operation
   // set_index=set_index%512;
   // ofstream outfile;
   // outfile.open("future_list.txt",ios::app);
   // outfile <<set_index<<" "<< tag << endl;
   // outfile.close();
   //*********************************************************write file operation
   // *******************************************read file operation
   if(read_condition==0){  
      ifstream infile; 
      infile.open("future_list.txt",ios::in); 
      while (!infile.eof())
      {
         infile>>set_index>>tag;
         future_list[read_condition][0]=set_index;
         future_list[read_condition][1]=tag;
         read_condition++;
      }
      infile.close();
   }
   //*******************************************read file operation

   if (access_type == LOAD) 
   {

      if (m_fault_injector) 
         m_fault_injector->preRead(addr, set_index * m_associativity + line_index, bytes, (Byte*)m_sets[set_index]->getDataPtr(line_index, block_offset), now);

      set->read_line(line_index, block_offset, buff, bytes, update_replacement);  
   }
   else
   {
      set->write_line(line_index, block_offset, buff, bytes, update_replacement);
      if (m_fault_injector)
         m_fault_injector->postWrite(addr, set_index * m_associativity + line_index, bytes, (Byte*)m_sets[set_index]->getDataPtr(line_index, block_offset), now);
   }

   return cache_block_info;
}
```



## 2. Policy

### (1). OPT Policy

Use the **cache_set_lru.cc** and **cache_set_lru.h** I submitted and it's OK. I have modified it to OPT algorithm.

### (2). Change to another policy, such as LRU

+ In **cache_set_lru.h**
+ modified ``UInt32* m_opt_bits;`` to ``UInt8* m_lru_bits;``   in line 42   ⭐⭐
+ In **cache_set_lru.cc**
+ Change the file to the the **original LRU** algorithm. I attached it to the file in the form of txt.

+ Now run the program, we will get the result of LRU.

## 3. If change the exe

Just ```./run-sniper -c ./config-lab0.cfg -- ./xxx.exe``    xxx can be sort.exe, and repeat above  step 1 to 3.
