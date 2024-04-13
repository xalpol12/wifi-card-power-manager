#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 1024

static const char iwconfig_command_template[] = "iwconfig %s";
static const char set_txpower_command_template[] = "iwconfig %s txpower %ddBm";

/*
 * Reads the power and signal level from the iwconfig output invoked for the
 * provided interface name and stores it in the provided power and signal
 * variable.
 */
int read_signal_levels(const char *interface, int *power, int *signal) {
  FILE *fp;
  char output[BUFF];
  char command[100];
  char *power_str, *signal_str;

  sprintf(command, iwconfig_command_template, interface);

  fp = popen(command, "r");
  if (fp == NULL) {
    perror("Error executing iwconfig");
    return EXIT_FAILURE;
  }

  while (fgets(output, sizeof(output), fp) != NULL) {
    power_str = strstr(output, "Tx-Power");
    if (power_str != NULL) {
      sscanf(power_str, "Tx-Power=%d dBm", power);
    }
    signal_str = strstr(output, "Signal level");
    if (signal_str != NULL) {
      sscanf(signal_str, "Signal level=%d dBm", signal);
    }
  }

  return EXIT_SUCCESS;
};

/*
 * Maps a value using a linear function defined by minimum and maximum values,
 * similar to the Arduino `map()` function.
 */
const int map_signal_to_power(int signal, int min_signal, int max_signal,
                              int min_power, int max_power) {
  return (signal - min_signal) * (max_power - min_power) /
             (max_signal - min_signal) +
         min_power;
}

/*
 * Calculates the power level based on the provided signal strength.
 * The power level is adjusted linearly between the minimum and maximum
 * power levels defined by MIN_PWR and MAX_PWR respectively.
 */
const int calculate_power_level(const int *signal) {
  int new_power =
      map_signal_to_power(*signal, MAX_SIG, MIN_SIG, MIN_PWR, MAX_PWR);

  if (new_power > MAX_PWR) {
    new_power = MAX_PWR;
  } else if (new_power < MIN_PWR) {
    new_power = MIN_PWR;
  }

  return new_power;
}

/*
 * This function constructs and executes a system command to adjust the
 * transmission power level of a wireless interface specified by the provided
 * interface name.
 */
void adjust_power_level(char *interface, int power) {
  char command[100];
  sprintf(command, set_txpower_command_template, interface, power);
  system(command);
}
