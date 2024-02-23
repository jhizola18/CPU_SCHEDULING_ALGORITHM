#include<iostream>
#include<vector>
#include "windows.h"
class Process{
private:
    int position_in_cpu;
    float arrival_time;
    float burst_time;
    float completion_time;
    float turn_aroundtime;
    float waiting_time;
public:
    Process(int pos, float at, float bt)
    {
        position_in_cpu = pos;
        arrival_time = at;
        burst_time = bt;
        completion_time = 0.0f;
        turn_aroundtime = 0.0f;
        waiting_time = 0.0f;
    };
    

    void setTAT(float TAT)
    {
        turn_aroundtime = TAT;
    };

    float getTAT()
    {
        return turn_aroundtime;
    }

    void setWT(float wt)
    {
        waiting_time = wt;
    }

    float getWT()
    {
        return waiting_time;
    }

    void setCT(float ct)
    {
        completion_time = ct;
    };

    float getCT()
    {
        return completion_time;
    };

    float get_AT()
    {
        return arrival_time;
    };

    float get_BT()
    {
        return burst_time;
    };

    int get_Pos()
    {
        return position_in_cpu;
    }
};

class CPU_scheduler
{
    public:
    CPU_scheduler(){};

    void sorting_processor(std::vector<Process>& proc, int size)
    {
        bool swapped;
        do{
            swapped = false;

            for(int i = 0; i < size; ++i)
            {
                if(proc[i].get_AT() > proc[i + 1].get_AT())
                {
                    Process temp = proc[i];
                    proc[i] = proc[i + 1];
                    proc[i + 1] = temp;
                    swapped = true;
                }else if(proc[i].get_AT() == proc[i + 1].get_AT())
                {
                    if(proc[i].get_Pos() > proc[i + 1].get_Pos())
                    {
                        Process temp = proc[i];
                        proc[i] = proc[i + 1];
                         proc[i + 1] = temp;
                        swapped = true;
                    }       
                }
            }

        }while(swapped);
     }

    void show_CompletionTime(std::vector<Process>& proc)
    {
        for(int i = 0; i < proc.size(); ++i)
        {
            std::cout << "Completion time for Process " << proc[i].get_Pos() << " is: ";
            
            std::cout << proc[i].getCT() << "\n";
        }
    }

    void calculate_completion_Time(std::vector<Process>& proc)
    {
        sorting_processor(proc, proc.size() - 1);
        int result;
        for(int i = 0; i < proc.size(); ++i)
        {
            if(proc[0].get_AT() > 0)
            {
                result = proc[0].get_AT() + proc[0].get_BT();
                proc[0].setCT(result);

            }else if(proc[i - 1].get_BT() < proc[i].get_AT() && i + 1 != proc.size()){
                //this is the problem
                result = proc[i].get_AT() + proc[i].get_BT();
                proc[i].setCT(result);

            }else if(proc[i].get_BT() < proc[i + 1].get_AT()){

                result = proc[i - 1].getCT() + proc[i].get_BT();
                proc[i].setCT(result);

            }else{
                result = proc[i - 1].getCT() + proc[i].get_BT();
                proc[i].setCT(result);
            }
            if(proc[i].get_Pos() == 2)
            {
                std::cout << " AT ->  " << proc[i].get_AT() << ", BT-> " << proc[i].get_BT() << ", Previous CT-> " << proc[i].getCT();
            }
        }
    }
    
    void calculate_turn_Aroundtime(std::vector<Process>& proc)
    {
        sorting_processor(proc, proc.size() - 1);
        for(int i = 0; i < proc.size(); ++i)
        {
            float result_of_turnaroundTime = turn_Aroundtime(proc[i].getCT(), proc[i].get_AT());
            proc[i].setTAT(result_of_turnaroundTime); 
        }
    }

     void calculate_waitingTime(std::vector<Process>& proc)
    {
        sorting_processor(proc, proc.size() - 1);
        for(int i = 0; i < proc.size(); ++i)
        {
            float result_of_waitingTime = waiting_Time(proc[i].getTAT(), proc[i].get_BT());
            proc[i].setWT(result_of_waitingTime);
        }
    }

    void show_turnaroundTime(std::vector<Process>& handler)
    {
        for(int i = 0; i < handler.size(); ++i)
        {
            std::cout << "Turn Around time for Process " << handler[i].get_Pos() << " is " << handler[i].getTAT() << "\n";
        }
    };

   

    void show_waitingTime(std::vector<Process>& handler)
    {
        for(int i = 0; i < handler.size(); ++i)
        {
            std::cout << "\nWaiting Time for Process " << handler[i].get_Pos() << " is " << handler[i].getWT();
        }
    }
    
    float average_TAT(std::vector<Process>& handler)
    {
        float result = 0.0f;
        for(int i = 0 ; i < handler.size(); ++i)
        {
               result += handler[i].getTAT();
        }
        
        return result/(handler.size());
    }

    float average_WT(std::vector<Process>& handler)
    {
        float result = 0.0f;
        for(int i = 0 ; i < handler.size(); ++i)
        {
               result += handler[i].getWT();
        }
        
        return result/(handler.size());
    }

    float turn_Aroundtime(float ct, float at)
    {
        return ct - at;
    };

    float waiting_Time(float TAT, float bt)
    {
        return TAT - bt;
    }
};


int main()
{
    
    CPU_scheduler scheduler;

    std::vector<Process> handler;
    int num_of_proc;

    std::cout << "How Many Process to Enter into CPU? ";
    std::cin >> num_of_proc;

    for(int i = 0 ; i < num_of_proc; ++i)
    {
        int temp_pos;
        float temp_at;
        float temp_bt;
        std::cout << "Enter Position of the process inside CPU: ";
        std::cin >> temp_pos;
        std::cout << "\nEnter Arrival Time to CPU: ";
        std::cin >> temp_at;
        std::cout << "\n" << "Enter Burst Time inside CPU: ";
        std::cin >> temp_bt;
        std::cout << "\n";
       Process process = {temp_pos ,temp_at, temp_bt};

       handler.push_back(process);
    }

    //scheduler.sorting_processor(handler, handler.size() - 1);
    
    for(int i = 0; i < num_of_proc; ++i)
    {
        std::cout << "\nP" << handler[i].get_Pos() <<"\n";
        std::cout << "Arrival Time:" << handler[i].get_AT() << "\n Burst Time:" << handler[i].get_BT() << "\n";
    }

    std::cout << "Calculating all the Completion Time.....\n";
    scheduler.calculate_completion_Time(handler);
    std::cout << "\n Calculation Complete!!!\n";

    std::cout << "Completion Time for the Processes: \n";
    scheduler.show_CompletionTime(handler);

    std::cout << "\nCalculating Turn-around Time.....\n";
    Sleep(1000);
    scheduler.calculate_turn_Aroundtime(handler);
    scheduler.show_turnaroundTime(handler);

    std::cout << "\nCalculating Waiting Time.....\n";
    Sleep(1000);
    scheduler.calculate_waitingTime(handler);
    scheduler.show_waitingTime(handler);

    std::cout << "\nCalculating Average Turn-Aroung Time....\n";
    Sleep(1000);
    float result_TAT =  scheduler.average_TAT(handler);
    std::cout << "Average Turn Around Time is: " << result_TAT << "\n";

    std::cout << "\nCalculating Average Waiting Time....\n";
    Sleep(1000);
    float result_WT = scheduler.average_WT(handler);
    std::cout << "Average Waiting Time is: " << result_WT << "\n";

    //scheduler.sorting_processor(handler,handler.size() - 1);

    for(int i = 0; i < handler.size(); ++i)
    {
        std::cout << handler[i].get_Pos() << " ";
    }

}