#include<iostream>
#include<vector>
#define  SIZE 4
#define  ARRSIZE 5
#define  MEMSIZE 6

struct Partition{

    int parti_num;
    int size;
    int block_id;
    bool Used;
};

struct Mem{

    int memSize;
    bool slostUsed;
    int block_id;
    int proc_num;
};

std::vector<Partition> createProcess()
{
    std::vector<Partition> sample;
    for(int i = 0; i < SIZE; ++i)
    {
        int proc;
        int size;
        std::cout << " \nEnter Process: ";
        std::cin >> proc;
       
        std::cout << " \nEnter Size of the Process: ";
        std::cin >> size;

        Partition* partition = new Partition();
        partition->parti_num = proc;
        partition->size = size;
        partition->block_id = 0;
        partition->Used = false;
        sample.push_back(*partition);
    }
    return sample;
}

std::vector<Mem> createMem()
{
    std::vector<Mem> memory;
    for(int i = 0; i < MEMSIZE; ++i)
    {
        Mem* mem = new Mem();
        int size;

        std::cout << " \nEnter Memory Size for Block " << i + 1 << ": ";
        std::cin >> size;

        mem->memSize = size;
        mem->block_id = i + 1;
        mem->slostUsed = false;

        memory.push_back(*mem);
    }

    return memory;
}

std::vector<Mem> firstFit(std::vector<Partition>& proc, std::vector<Mem>& mem)
{
   for(auto item : proc)
   {
        for(int i = 0; i < ARRSIZE; ++i)
        {
            if(item.size <= mem[i].memSize && mem[i].slostUsed == false && item.Used == false) 
            {
                mem[i].memSize = item.size;
                item.block_id = 1;
                item.Used = true;
                mem[i].proc_num = item.parti_num;
                mem[i].slostUsed = true;
            }else{
                continue;
            }
        }
   }
       
    return mem;
}


void printData(std::vector<Partition>& proc, std::vector<Mem>& mem)
{
    std::cout << "\n Original Memory: \n";
    std::cout << "BLOCK" << "  | " << "MEMORY SIZE\n";
    for(auto item : mem)
    {
        std::cout << " ----------------\n";
        std::cout << "| " << item.block_id  << "    |  " << item.memSize << "kb" <<"  |" << "\n";
    }   
    std::cout << " ----------------\n";
    std::cout << "\nProcessors\n";
    std::cout << "Process" << "  | " << "MEMORY SIZE\n";
    for(auto items : proc)
    {
        std::cout << " ----------------\n";
        std::cout << "| " << "P" <<items.parti_num  << "    |  " << items.size << "kb" <<"  |" << "\n";
    }
     std::cout << " ----------------\n";
}
    
//Add checking of internal fragmentation
int main()
{
    
    std::vector<Mem> memHandler = createMem();
    std::vector<Partition> handler = createProcess();
    
    printData(handler, memHandler);

    firstFit(handler, memHandler);
    std::cout << "\nFirst Fit Implementation:\n";
    for(int i = 0; i < MEMSIZE; ++i)
    {
        std::cout << " ---------------------\n";
        std::cout << "| " << memHandler[i].block_id  << "    |  " << "P" << memHandler[i].proc_num << "-" <<memHandler[i].memSize << "kb" <<"     |" << "\n";
    }
    std::cout << "\nNOTE: 'P0' means the memory block is unoccupied";

    return 0;
}