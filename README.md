# Philosophers

## Table of Contents
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Running the Project](#running-the-project)
- [Concepts](#concepts)
  - [Concurrent Programming](#Concurrent-Programming)
  - [Threads](#threads)
  - [Mutexes](#mutexes)
  - [Deadlocks](#deadlocks)
  - [Data Races](#data-races)
  - [Semaphores](#semaphores)
- [Resources](#Resources)

## Project Overview
The **Philosophers** project is part of the 1337 school curriculum, designed to teach the basics of concurrent programming through the classic Dining Philosophers Problem. This problem introduces key concepts like synchronizing actions, avoiding deadlocks, and managing shared resources among threads.

In this example, several philosophers sit around a table with a bowl of spaghetti in the center. Each philosopher alternates between thinking, eating, and sleeping. Their behavior follows a few simple rules:

- **Eating Requires Two Forks**: To eat, each philosopher must pick up both forks beside them at the same time.
- **Mutual Exclusion**: A philosopher can only do one action at a time, like eating or thinking, without overlap.
- **Starvation Prevention**: The setup ensures every philosopher eventually gets a turn to eat.
- **No Communication**: The philosophers do not communicate or know each other’s actions, adding a challenge to managing fair access to resources.


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
- **number_of_times_each_philosopher_must_eat**: Number of meals for each philosopher.

## Concepts

### Concurrent Programming
Concurrent programming is a way of organizing code so that multiple tasks can run at the same time, sharing resources without causing conflicts. This allows a program to perform different tasks "concurrently" or simultaneously, which is important for applications that require efficiency, like servers or complex calculations. In the *Dining Philosophers* project, we use concurrency to let each philosopher operate independently, thinking or eating without waiting on others (unless they need the same resource, like a fork).

### Threads
A **thread** is like a small program within a program, running tasks independently but sharing the same memory space as the main program. For example, in this project, each philosopher is created as a separate thread, so all philosophers can "think" and "eat" concurrently without waiting on each other’s actions (unless they both need the same fork).

#### Example: Creating and Joining Threads
Using POSIX threads (or pthreads), we can create, run, and manage threads in C. Here’s a simple example:

```c
#include <pthread.h>
#include <stdio.h>

void    *philosopher_routine(void* arg)
{
    printf("Philosopher is thinking...\n");
    return (NULL);
}

int main(void)
{
    pthread_t thread;
    pthread_create(&thread, NULL, philosopher_routine, NULL);
    pthread_join(thread, NULL); // Waits for the thread to finish
    return (0);
}
```
- **`pthread_create`** starts a new thread with the specified function (e.g., `philosopher_routine`).
- **`pthread_join`** waits for the thread to finish before the program continues. This is helpful when you want to ensure the thread completes.

Alternatively, **`pthread_detach`** allows a thread to run independently and release its resources automatically when done, but it can't be joined later. Use `join` when you need results from the thread and `detach` when it’s a standalone task.

## Mutexes

A **mutex** (short for "mutual exclusion") is a locking mechanism that allows only one thread to access a resource at a time. In this project, mutexes prevent multiple philosophers from holding the same fork.

### Example: Locking and Unlocking Mutexes

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t fork_mutex;

void    *philosopher_routine(void* arg)
{
    pthread_mutex_lock(&fork_mutex); // Lock the fork
    printf("Philosopher is eating...\n");
    pthread_mutex_unlock(&fork_mutex); // Unlock the fork
    return (NULL);
}

int main(void)
{
    pthread_mutex_init(&fork_mutex, NULL); // Initialize the mutex
    pthread_t philosopher;
    pthread_create(&philosopher, NULL, philosopher_routine, NULL);
    pthread_join(philosopher, NULL);
    pthread_mutex_destroy(&fork_mutex); // Destroy the mutex when done
    return (0);
}
```
- **`pthread_mutex_lock`** locks the mutex, making sure no other thread can access the resource until it’s unlocked.
- **`pthread_mutex_unlock`** unlocks the mutex so other threads can use the resource.
- **`pthread_mutex_destroy`** frees the mutex resources when you’re done.

## Deadlocks

Deadlocks happen when two or more threads are stuck waiting for each other to release resources, creating a standstill. For example, if each philosopher picks up one fork and waits for the other, none of them can proceed, resulting in a deadlock.

## Data Races

A **data race** occurs when two threads access the same shared variable at the same time, with at least one of them modifying it. This can lead to unpredictable results. To prevent data races, mutexes are used to lock the shared variable, allowing only one thread to access it at a time.

```c
pthread_mutex_t data_mutex;
int shared_data = 0;

void    *increment_data(void* arg)
{
    pthread_mutex_lock(&data_mutex);
    shared_data++; // Safe access with mutex
    pthread_mutex_unlock(&data_mutex);
    return (NULL);
}
```

## Semaphores

**Semaphores** are counters that allow a certain number of threads to access a resource simultaneously. They can be used to limit the number of philosophers that can pick up forks at the same time, preventing deadlocks.

A **counting semaphore** keeps track of the number of available resources, decrementing each time a thread accesses a resource and incrementing when the resource is released.

### Example: Using Counting Semaphores

```c
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t semaphore;

void    *philosopher_routine(void* arg)
{
    sem_wait(&semaphore); // Decrement the semaphore
    printf("Philosopher is eating...\n");
    sem_post(&semaphore); // Increment the semaphore
    return (NULL);
}

int main(void)
{
    sem_init(&semaphore, 0, 2); // Allow 2 philosophers to eat at the same time
    pthread_t philosopher1, philosopher2;
    pthread_create(&philosopher1, NULL, philosopher_routine, NULL);
    pthread_create(&philosopher2, NULL, philosopher_routine, NULL);
    pthread_join(philosopher1, NULL);
    pthread_join(philosopher2, NULL);
    sem_destroy(&semaphore); // Clean up semaphore
    return (0);
}
```

- **`sem_wait`** decreases the semaphore, blocking if the count is zero (meaning no resources are available).
- **`sem_post`** increases the semaphore, allowing other threads to access the resource.
- **`sem_init`** initializes the semaphore with a specific count (2 here, allowing two philosophers to access the resource).
- **`sem_destroy`** cleans up the semaphore when it’s no longer needed.

## Resources

- [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [The Dining Philosophers Problem](https://www.youtube.com/watch?v=FYUi-u7UWgw)
- [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
- [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)
- [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)