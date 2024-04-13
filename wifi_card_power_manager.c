#include "calculations.c"
#include "globals.h"
#include "pretty_print.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Compilation: gcc -Wall -o ./wifi_card_power_manager ./wifi_card_power_manager.c 
 * Usage: sudo wifi_card_power_manager <if_name>
 */

int main(int argc, char **argv) {
  int power = MIN_PWR, signal = MIN_SIG;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <wifi_interface>", argv[0]);
    return EXIT_FAILURE;
  }

  while (1) {
    if (read_signal_levels(argv[1], &power, &signal) == 1) {
      perror("Error in read_signal_levels function, could not read values");
    }

    int new_power = calculate_power_level(&signal);
    if (new_power != power) {
      adjust_power_level(argv[1], new_power);
    }
    print_signal_levels(power, signal, stdout);
    sleep(2);
  }
}
