# Philosophers

A small **multithreaded simulation** of the [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem, written in C with **pthread** mutexes. Each philosopher runs in its own thread, shares forks (mutexes) on a round table, and must **eat**, **sleep**, and **think** without deadlocking. A separate **death monitor** ends the run if someone starves, and an optional **meal monitor** stops the program when every philosopher has eaten a target number of times.

This repository is refactored for **clarity and maintainability** (clear module boundaries, descriptive names, a single header), rather than being split to satisfy external style checkers.

---

## What the program does

- **Philosophers** are threads. Each has a **left** and **right** fork (array index on the table). They always lock the **lower-index fork first** to avoid classic circular wait deadlocks.
- **Time** is measured in **milliseconds** from a common start; log lines are `timestamp_in_ms philosopher_id action`.
- **Death**: if a philosopher’s time since the start of their last **meal** exceeds `time_to_die`, they “die” and the simulation stops (unless the optional meal goal already ended it).
- **Optional meal count**: if `meals_per_philosopher` is given, a thread watches whether everyone has reached that count; when they have, the run ends peacefully (“full”).

---

## Requirements

- A C99 compiler (`cc` / `gcc`)
- POSIX threads (`pthread`), available on Linux and macOS
- `make`

---

## Build

```bash
make
```

Produces the executable **`philo`** in the project directory.

| Target           | Purpose                                                |
|------------------|--------------------------------------------------------|
| `make` / `all`   | Release-style build (`-Wall -Wextra -Werror`)         |
| `make re`        | Clean objects/binary and rebuild                       |
| `make clean`     | Remove object files                                    |
| `make fclean`    | Remove objects **and** `philo`                         |
| `debug_leaks`    | AddressSanitizer build (memory issues)                 |
| `debug_drc`      | ThreadSanitizer build (data races / threading bugs)   |
| `debug_valgrind` | Debug symbols, light optimization (for Valgrind)      |

For the debug variants, the Makefile relinks with the appropriate flags; use them when investigating crashes or undefined behavior.

---

## Usage

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_per_philosopher]
```

All numeric arguments must be **positive integers** (and fit in `int`). Times are in **milliseconds**.

| Argument | Meaning |
|----------|---------|
| `number_of_philosophers` | How many philosophers (threads). Must be ≥ 1. |
| `time_to_die` | Max time since **starting to eat** last time before death is reported. |
| `time_to_eat` | How long “eating” lasts (held forks + simulated chew time). |
| `time_to_sleep` | How long “sleeping” lasts after eating. |
| `meals_per_philosopher` | Optional. If set, stop once **every** philosopher has eaten this many times. If omitted, the run only ends on death or external stop. |

**Example** (5 philosophers, 800 ms to die, 200 ms eat, 200 ms sleep, no meal limit):

```bash
./philo 5 800 200 200
```

**Example** with a stop condition (each must eat 7 times):

```bash
./philo 5 800 200 200 7
```

Wrong arity or invalid numbers prints an error to stderr and exits with a non-zero status.

---

## Output

Lines look like:

```text
timestamp_ms id action
```

Typical `action` strings include `is eating`, `is sleeping`, `is thinking`, `has taken a fork`, and `died`. Timestamps are **elapsed milliseconds since the simulation start**, not wall-clock epoch time.

Printing is serialized with a mutex so lines do not interleave mid-line.

---

## Project layout

| Path | Role |
|------|------|
| `main.c` | Parses CLI intent, starts threads, joins them, tears down. |
| `args.c` | String-to-number parsing and argument validation. |
| `simulation.c` | Shared state, fork and “global” mutexes, init/cleanup, death and meal **monitor** threads, thread creation/join helpers. |
| `philosopher.c` | Per-philosopher **thread routine** (eat / sleep / think), timing helpers, thread-safe logging. |
| `includes/philosopher.h` | Shared types (`t_philo`, `t_rules`) and public prototypes. |

Conceptually: **`simulation.c`** owns table-wide rules and monitors; **`philosopher.c`** owns one philosopher’s behavior and timing; **`args.c`** keeps input parsing in one place.

---

## Optional tests

A helper script `test.sh` (if present) can run automated checks. Make `philo` first, then follow any instructions in that script. It is community-style tooling, not required for a normal build.
