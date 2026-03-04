*This project has been created as part of the 42 curriculum by afournie.*

## Description

This project is an implementation of the classic **Dining Philosophers Problem**, a well-known concurrency problem in computer science. A given number of philosophers sit around a table. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must pick up two forks — one on each side. The goal is to simulate this scenario using threads and mutexes, ensuring that no philosopher starves and that no data races occur.

Each philosopher is a thread. Forks are shared resources protected by mutexes. A monitor thread (jarvis) continuously checks whether any philosopher has exceeded their time-to-die without eating.

## Instructions

### Compilation

```bash
make
```

### Usage

```bash
./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> [nb_meals]
```

| Argument | Description |
|---|---|
| `nb_philos` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms before a philosopher dies if they haven't eaten |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `nb_meals` | *(Optional)* Simulation stops when all philosophers have eaten this many times |

### Examples

```bash
./philo 5 800 200 200        # 5 philos, no one should die
./philo 4 310 200 100        # 4 philos, one should die
./philo 5 800 200 200 7      # stops after each philo has eaten 7 times
```

### Cleanup

```bash
make clean    # remove object files
make fclean   # remove object files and binary
```

## Resources

### Documentation & References

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads (pthreads) — man7.org](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_mutex_lock — man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday — man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Valgrind Helgrind — thread error detector](https://valgrind.org/docs/manual/hg-manual.html)

### AI Usage

Claude (Anthropic) was used during the development of this project for the following tasks:

- **Debugging**
- **Concurrency advice**
