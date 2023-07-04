# philosophers
<div align="center">
<img width="267" alt="DALL·E 2023-06-14" src="https://github.com/liz753/philosophers/assets/114035440/df5888c6-f80b-493e-98a1-6e014809a1fa">
</div> <div align="center"><sub>Image generated by Dall·E Online Generator</sub></div> 


## Table of Contents

* [How to use the Program](#how-to-use-the-program)
* [Project Overview](#project-overview)
* [Divide and Conquer](#divide-and-conquer)
* [Result](#result)
* [Tips for 42 students](#tips-for-42-students)
* [What I learned](#what-i-learned)

## How to use the Program

Git clone the project and compile using ```make```. 

Run the program with the following arguments:
```./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat] ```
If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten ```number_of_times_each_philo_must_eat```, if specified.

## Project Overview

The assignment is designed around Edsger Dijkstra's famous dining philosophers problem. 

The subject describes the problem as follows:
* One or more philosophers sit at a round table.
    There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking. 
* There are also forks on the table. There are as many forks as philosophers. 
* Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand. 
* When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation. 
* Every philosopher needs to eat and should never starve. 
* Philosophers don’t speak with each other. 
* Philosophers don’t know if another philosopher is about to die. 
* No need to say that philosophers should avoid dying!

  
The program takes 5 to 6 arguments:
* ```number_of_philosophers```: The number of philosophers and also the number of forks. 
* ```time_to_die``` (in milliseconds): If a philosopher didn’t start eating ```time_to_die``` milliseconds since the beginning of their last meal or the beginning of the simulation, they die. 
* ```time_to_eat``` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks. 
* ```time_to_sleep``` (in milliseconds): The time a philosopher will spend sleeping. 
* ```number_of_times_each_philosopher_must_eat``` (optional argument): If all philosophers have eaten at least ```number_of_times_each_philosopher_must_eat``` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
  
The programs outputs a message each time a philosopher takes an action, which is formatted as follows:
* [ms since the beginning of the simulation] [philosopher number] has taken a fork
* [ms since the beginning of the simulation]  [philosopher number]  is eating
* [ms since the beginning of the simulation]  [philosopher number]  is sleeping
* [ms since the beginning of the simulation]  [philosopher number]  is thinking
* [ms since the beginning of the simulation]  [philosopher number]  died

## Divide and Conquer 
I got started with identifying the concepts that were new to me.

<ins>1. Research</ins>
*   The dining philosophers problem by Edsger Dijkstra
*   concept of threads and mutexes
*   Linux Programmer Manual: 
      *  hread_create(3)
      *  pthread_join(3)
      *  pthread_mutex_init/lock/unlock(3)
      *  gettimeofday(2)
* research on timeval type + how dates work
* datarace 
* deadlock
* difference between [routine and process](https://www.geeksforgeeks.org/difference-between-routine-and-process/) 

<ins>2. Code Structure</ins>
*   creating a Makefile that doesn't relink
*   creating a header file 

<ins>3. Implementation</ins>
Parsing: 
* take the arguments and turn them into int with ```atoi```
* check if the numbers are positive and not bigger than ```INT_MAX```, otherwise throw an error 
* check if the number of philosophers given is under 200 
*   set up gettime

Execution:
* creation of threads: In the mandatory part, each philosopher is a thread and each fork is protected by a mutex. There is exactly one fork between each philosopher and a philosopher must take the forks to his immediate left and right in order to eat.
* Use of mutexes (first lock, then read or modify the shared resources, then unlock): protect the shared resources since the philosophers can’t communicate with each other, also protect the ```printf```functions to prevent message from overlapping.
* Attribution of forks: the mutex corresponding to a fork is locked as long as a philosopher uses it. Forks are taken one after the other.
* Routine: The elements of this program which form the routine are obviously eat, sleep and think. When the program starts, the philosophers with even numbers check if their forks are available, one after the other and eat. After they ate ```time_to_eat```ms, they’re going to sleep. Afterwards, they’re going to think until they can eat again. The others do the same, with one particularity, the odd ones wait a bit before starting. This make sure that all the even philosophers starts and ensure the synchronization. At each step, I implemented a check to see if there is a dead philosopher. The execution will stop if it the case. Since the philosophers can die during an action, I implemented a ```suspend thread function``` that uses multiple short ```usleep```  functions in a loop.


## Result 

Here are examples of commands and their execution with my program: 

```./philo 4 310 200 100```:


<img width="237" alt="0 1 has taken a fork" src="https://github.com/liz753/philosophers/assets/114035440/3fa03eb8-f5cf-4059-ba43-f95571e25e1d"> <img width="204" alt="Screen Shot 2023-07-04 at 10 41 17 AM" src="https://github.com/liz753/philosophers/assets/114035440/537bc46e-c705-4435-862e-4c9a16b81720">



```./philo 3 400 100 100 3```:

<img width="606" alt="Screen Shot 2023-07-04 at 10 34 35 AM" src="https://github.com/liz753/philosophers/assets/114035440/422c99ca-acf2-4d88-a551-a516db85ed50">

```./philo 5 800 200 200```:

<img width="1809" alt="Screen Shot 2023-07-04 at 10 35 55 AM" src="https://github.com/liz753/philosophers/assets/114035440/237e3a31-50b3-46d3-8fb5-f1e8ff8934af">

```./philo 20 400 300 100```:

<img width="253" alt="Screen Shot 2023-07-04 at 10 38 25 AM" src="https://github.com/liz753/philosophers/assets/114035440/b93355df-23a3-4b5d-8608-6f315bbc259c">


For the visualization, I used the [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/) by Nafuka11. 


## Tips for 42 students 
*   you can add ```-fsanitize=thread```to your flags in your makefile to check if there are data races, however, I recommend to only use this flag during the evaluation since it causes a high CPU usage
*   an excellent source to understand threads and mutexes: [codevault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
*  debugging: make sure to unlock your mutexes after locking them
*  prevent leaks: For a thread to free their resources they must always return their routine function otherwise you will leak their allocated memory. To do that, you can either detach or join it. If you join a thread you're making sure the main thread waits for the created thread to return its routine and consequently free its resources. 
*  error detection possible with valgrind --tool=drd ./philo <args>
* attribution of forks: I first tried to let the philosophers check if forks are available and take them at the same time, but this led to problems when there was an odd number of philosophers
* The subject states: “Replace timestamp_in_ms with the current timestamp in milliseconds  and X with the philosopher number.” As I understand it, it refers to the [epoch time](https://stackoverflow.com/questions/1090869/why-is-1-1-1970-the-epoch-time). So, normally, we should print the Unix epoch time, but it’s easier to do debugging and the evaluations if we use the ms elapsed since the beginning of the simulation, i.e. ```timestamp – time start of simulation’’’

## What I learned 
While working on this project, I deepened my understanding of multithreading and synchronization concepts. Managing concurrent access to shared resources was completely new to me, but easier than I thought at the beginning. I learned how to use mutexes to ensure thread safety and prevent race conditions. Furthermore, I delved into the intricacies of deadlock detection and avoidance. Lastly, I discovered the concept of epoch time which made me feel like a entered a bit more in the progamming world. I really liked the project, even though it was kind of long in the end, final learning: spaghetti comes to those who wait!

