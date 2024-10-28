# Philosophers

## Table of Contents
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Running the Project](#running-the-project)
- [Concepts](#concepts)
  - [Threads](#threads)
  - [Mutexes](#mutexes)
  - [Deadlocks](#deadlocks)
  - [Data Races](#data-races)
  - [Semaphores](#semaphores)

## Project Overview
The **Philosophers** project is a part of the 42 school curriculum designed to demonstrate the complexities of concurrent programming. It’s based on the classic *Dining Philosophers* problem, which is a fundamental exercise in understanding synchronization, avoiding deadlocks, and managing shared resources between threads. The goal is to create a program where philosophers (represented as threads) can alternate between thinking and eating without creating conflicts or deadlocks over shared resources (forks).


## Installation
To set up the project locally, follow these steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/BitWarlock/Philosophers.git
   ```
2. Navigate to project directory and compile the project:
    ```bash
    cd Philosophers && make
    ```

## Running the Project
Once project is compiled run with:
    ```
    ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat](optional)
    ```
- **number_of_philosophers**: Number of philosophers and forks.
- **time_to_die**: Time in milliseconds after which a philosopher dies if they don’t start eating.
- **time_to_eat**: Time in milliseconds it takes for a philosopher to finish eating.
- **time_to_sleep**: Time in milliseconds a philosopher spends sleeping after eating.

## Concepts

### Threads
Threads allow a program to perform multiple tasks concurrently. In this project, each philosopher is represented as a separate thread, enabling them to operate independently.

### Mutexes
A mutex (mutual exclusion) is a synchronization primitive used to prevent multiple threads from accessing a shared resource simultaneously. In the *Dining Philosophers* problem, a mutex is used to ensure that only one philosopher can hold a fork at a time.

### Deadlocks
Deadlocks occur when two or more threads are waiting indefinitely for resources held by each other, creating a standstill. This project tackles the challenge of preventing deadlocks by carefully controlling the order and timing of resource allocation.

### Data Races
A data race happens when two or more threads access a shared variable simultaneously, with at least one thread modifying it. This can lead to unpredictable behavior. Proper locking mechanisms, like mutexes, are used in this project to prevent data races.

### Semaphores
Semaphores are another synchronization tool, allowing multiple threads to access a limited number of resources. In the *Dining Philosophers* problem, semaphores can be used to control the total number of philosophers that can pick up forks at once, reducing the likelihood of deadlocks.
