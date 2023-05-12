# Dining Philosophers Problem Implementation

This is an implementation of the dining philosophers problem, a classic synchronization problem in computer science. The problem involves a group of philosophers sitting around a circular table, with each philosopher having a plate of spaghetti and a fork on either side of them. The philosophers alternate between thinking and eating, but can only eat if they have both forks. The problem is to create a solution in which no philosopher will be left hungry and no deadlocks occur.

## Implementation Details

This implementation uses the monitor model and implements the solution using semaphores for synchronization. Each philosopher is represented by a separate thread, and the shared resources (forks) are protected by the monitor.

The implementation uses a `Fork` struct to represent a fork, which contains a mutex and a semaphore. The mutex is used to protect the fork from concurrent access by multiple threads, while the semaphore is used to signal when the fork is available for use by a philosopher.

The `Philosopher` struct represents a philosopher and contains a thread ID, a left fork and a right fork. When a philosopher wants to eat, they try to acquire both forks using semaphores. If both forks are available, the philosopher eats for a random period of time before releasing the forks.

To ensure that deadlocks do not occur, the program uses a variation of the standard solution to the dining philosophers problem called the resource hierarchy solution. In this variation, each philosopher tries to acquire their left fork first before trying to acquire their right fork. This ensures that at least one philosopher will always be able to acquire both forks and prevent a deadlock.

## How to Compile and Run

To compile the program, navigate to the directory containing the source code and run the `make` command:

$ make
or
$ make all


This will generate an executable file called `diningPhilosophers`.

To run the program, simply execute the `diningPhilosophers` file:

$ ./diningPhilosophers
or
$ make run


This will run the program and output the actions taken by each philosopher (e.g. thinking, eating, waiting for forks, etc.). The program will run indefinitely until manually terminated.

## Course Information

This project was developed as part of the Operating Systems I course at Universidade de São Paulo. The purpose of the project was to gain experience with synchronization mechanisms and the implementation of concurrent programs in a Linux environment.
