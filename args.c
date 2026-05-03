#include "includes/philosopher.h"

/*
 * Converts a decimal string to long. Returns a value > INT_MAX if the string
 * is not a clean integer (used so validation can reject invalid input).
 */
long parse_long(const char *str)
{
	int sign = 1;
	long long result = 0;
	int i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return ((long)INT_MAX + 1);
	return ((long)(result * sign));
}

int args_are_valid(int argc, char **argv)
{
	long vals[5];

	vals[0] = parse_long(argv[1]);
	vals[1] = parse_long(argv[2]);
	vals[2] = parse_long(argv[3]);
	vals[3] = parse_long(argv[4]);
	if (argc == 6)
		vals[4] = parse_long(argv[5]);
	else
		vals[4] = 1;
	if (vals[0] < 1)
		return (0);
	for (int i = 1; i < 4; i++)
	{
		if (vals[i] < 0 || vals[i] > INT_MAX)
			return (0);
	}
	if (vals[4] < 1 || vals[4] > INT_MAX)
		return (0);
	return (1);
}
