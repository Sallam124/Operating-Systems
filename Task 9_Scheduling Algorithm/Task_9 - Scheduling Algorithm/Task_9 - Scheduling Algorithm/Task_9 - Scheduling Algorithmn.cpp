#include <iostream>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <queue>

using namespace std;
vector <int> Arrival;

// Proccess class that holds all the information about a process
class Proccess {
public:
	int id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turnaround_time;
	int completion_time;
	int remaining_time;

	Proccess(int Proccess_id, int arr_time, int burst_t)
	{
		id = Proccess_id;
		arrival_time = arr_time;
		burst_time = burst_t;
		waiting_time = 0;
		turnaround_time = 0;
		completion_time = 0;
		remaining_time = burst_t;

		Arrival.push_back(arrival_time);
	}
};

vector<Proccess> Proccess_List;  // List to keep track of all processes


void addProcess(int id, int arrival, int burst)// Adds a new process to the list of processes while creating an object aswell
{
	Proccess_List.push_back(Proccess(id, arrival, burst));
}

//AI

bool compareArrival(const Proccess& a, const Proccess& b) // Comparison function that returns true if process 'a' arrives earlier than process 'b'
{
	return a.arrival_time < b.arrival_time;
}
//

void First_Come_First_Serve() 
{
	// Sorts the process list based on arrival time in ascending order
	sort(Proccess_List.begin(), Proccess_List.end(), compareArrival);


	int current_time = 0;

	for (Proccess &Proc : Proccess_List) 
	{
		if (current_time < Proc.arrival_time) // if the current time still hasn't reached the set time for the proccess ex. time is 2, proccess starts at 3;  
			current_time = Proc.arrival_time; 


		Proc.completion_time = current_time + Proc.burst_time;  

		Proc.turnaround_time = Proc.completion_time - Proc.arrival_time; //Turn Around Time = Completion Time – Arrival Time

		Proc.waiting_time = Proc.turnaround_time - Proc.burst_time; //Waiting Time = Turn Around Time – Burst Time

		current_time += Proc.burst_time;
	}

    
    
    double average_turn = 0;
	double average_wait = 0;
	cout << "First Come First Serve Algorithmn :-" << endl << endl;
	for (Proccess Proc : Proccess_List)
	{
	
		cout << "Proccess " << Proc.id << " Turn Around Time was : " << Proc.turnaround_time << " and Waiting time was : " << Proc.waiting_time << endl;
		average_turn += Proc.turnaround_time;
		average_wait += Proc.waiting_time;
	}

	average_turn /= Proccess_List.size();
	average_wait /= Proccess_List.size();

	cout << "The Average Turn Around Time was: " << average_turn  << endl;
	cout << "The Average Waiting time was :: " << average_wait  << endl << endl;

}
// solved some issues with ai ( queue should be of type pointers to a class and passing by reference )
void Round_Robin_Algorithm(int Time_Quantum)
{
    vector<Proccess> local_proccess_list = Proccess_List; // Create a local copy
    queue<Proccess*> queue;
    int current_time = 0;

    // Push all processes into the queue
    for (Proccess& proc : local_proccess_list)
    {
        queue.push(&proc);
    }

    while (!queue.empty())
    {
        Proccess* Proc = queue.front();
        queue.pop();

        if (current_time < Proc->arrival_time)
        {
            current_time = Proc->arrival_time;
        }

        if (Proc->remaining_time > Time_Quantum)
        {
            Proc->remaining_time -= Time_Quantum;
            current_time += Time_Quantum;
            queue.push(Proc);  // Re-add process to queue
        }
        else
        {
            current_time += Proc->remaining_time;
            Proc->completion_time = current_time;
            Proc->turnaround_time = Proc->completion_time - Proc->arrival_time;
            Proc->waiting_time = Proc->turnaround_time - Proc->burst_time;
            Proc->remaining_time = 0;
        }
    }

    double average_turn = 0;
    double average_wait = 0;
    cout << "Round Robin Algorithm :-" << endl << endl;

    for (Proccess Proc : local_proccess_list)
    {
        cout << "Proccess " << Proc.id << " Turn Around Time was : "
            << Proc.turnaround_time << " and Waiting time was : "
            << Proc.waiting_time << endl;
        average_turn += Proc.turnaround_time;
        average_wait += Proc.waiting_time;
    }

    average_turn /= local_proccess_list.size();
    average_wait /= local_proccess_list.size();

    cout << "The Average Turn Around Time was: " << average_turn << endl;
    cout << "The Average Waiting time was :: " << average_wait << endl << endl;
}

void Shortest_Job_First()
{
    vector<Proccess> local_Proccess_List = Proccess_List; 
    int current_time = 0;
    int completed = 0;
    int n = local_Proccess_List.size();

    while (completed < n)
    {
        Proccess* shortest = nullptr;

        // Find the process with the shortest remaining time that has arrived
        for (Proccess& proc : local_Proccess_List)
        {
            if (proc.arrival_time <= current_time && proc.remaining_time > 0) // Only consider processes that have arrived and are not yet completed
            {
                if (!shortest || proc.remaining_time < shortest->remaining_time) // Update if it's the first process found or has a shorter remaining time than the current shortest
                    shortest = &proc;
            }
        }
        if (shortest)
        {
            current_time += shortest->remaining_time;
            shortest->completion_time = current_time;
            shortest->turnaround_time = shortest->completion_time - shortest->arrival_time;
            shortest->waiting_time = shortest->turnaround_time - shortest->burst_time;
            shortest->remaining_time = 0;
            completed++;
        }
        else
        {
            current_time++;
        }
    }

    double average_turn = 0;
    double average_wait = 0;

    cout << "Shortest Job First Algorithm :-" << endl << endl;
    for (Proccess Proc : local_Proccess_List)
    {
        cout << "Proccess " << Proc.id << " Turn Around Time was : "
            << Proc.turnaround_time << " and Waiting Time was : "
            << Proc.waiting_time << endl;
        average_turn += Proc.turnaround_time;
        average_wait += Proc.waiting_time;
    }

    average_turn /= local_Proccess_List.size();
    average_wait /= local_Proccess_List.size();

    cout << "Avg Turnaround Time: " << average_turn << endl;
    cout << "Avg Waiting Time: " << average_wait << endl << endl;
}




int main()
{
	addProcess(1, 0, 5);
	addProcess(2, 0, 3);
	addProcess(3, 0, 8);

	First_Come_First_Serve();
    Shortest_Job_First();
    Round_Robin_Algorithm(3);

}