Create a file named Deadlock.txt in the same directory as the program. The file should have the following structure: 
5 3 .                // 5 = Number of processes (P1 to P5), 3 = Number of resource types (R1, R2, R3)

3 2 2 .              // 3 = Available units of resource R1, 2 = Available units of resource R2, 2 = Available units of resource R3

1 0 2                // Process 1 (P1) has 1 unit of R1, 0 units of R2, 2 units of R3
1 1 1                // Process 2 (P2) has 1 unit of R1, 1 unit of R2, 1 unit of R3
2 1 1                // Process 3 (P3) has 2 units of R1, 1 unit of R2, 1 unit of R3
1 1 1                // Process 4 (P4) has 1 unit of R1, 1 unit of R2, 1 unit of R3
1 0 0 .               // Process 5 (P5) has 1 unit of R1, 0 units of R2, 0 units of R3; End of allocationg matrix


2 1 1                // Process 1 (P1) is requesting 2 units of R1, 1 unit of R2, 1 unit of R3
1 1 0                // Process 2 (P2) is requesting 1 unit of R1, 1 unit of R2, 0 units of R3
2 1 1                // Process 3 (P3) is requesting 2 units of R1, 1 unit of R2, 1 unit of R3
1 0 2                // Process 4 (P4) is requesting 1 unit of R1, 0 units of R2, 2 units of R3
2 1 1 .              // Process 5 (P5) is requesting 2 units of R1, 1 unit of R2, 1 unit of R3; End of request matrix


string filename = "/path/to/your/Deadlock.txt";  // Update this with your actual path


To compile using linux terminal:
Create the cpp file, create the text file.

g++ -o compling file file name .cpp

./compling file

