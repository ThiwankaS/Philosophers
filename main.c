#include "includes/philosopher.h"

int main(int argc, char **argv)
{
	t_thread monitor;
	t_thread meal;
	t_rules rules = {0};

	if (argc != 5 && argc != 6)
		return (print_error(USAGE_MSG));
	if (!args_are_valid(argc, argv))
		return (print_error("Invalid arguments."));
	if (simulation_init(&rules, argc, argv) != 0)
		return (exit_after_partial_init(&rules,
				"Could not initialize simulation."));
	if (spawn_death_monitor(&rules, &monitor) != 0)
		return (exit_after_failed_threads(&rules,
				"Could not start death monitor thread."));
	if (spawn_philosopher_threads(&rules, &monitor) != 0)
		return (exit_after_failed_threads(&rules,
				"Could not start philosopher threads."));
	if (spawn_meal_monitor(&rules, &meal, &monitor) != 0)
		return (exit_after_failed_threads(&rules,
				"Could not start meal monitor thread."));
	join_all_threads(&rules, &meal, &monitor);
	simulation_destroy(&rules);
	return (0);
}
