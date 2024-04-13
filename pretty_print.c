#include "globals.h"
#include <stdio.h>

/*
 * Prints the transmission power and signal level to the provided file pointer.
 * If stdout is provided as a FILE pointer, then function also
 * prints status bars and resets cursor each frame instead of printing multiple
 * lines.
 */
void print_signal_levels(int power, int signal, FILE *file) {
  if (file == stdout) {
    // Clear the screen and move cursor to the beginning
    fprintf(file, "\033[2J\033[H");
  }

  fprintf(file, "Tx-Power: %2d dBm\t\tSignal level: %3d dBm\n", power, signal);

  if (file == stdout) {
    // Calculate and print power bar
    int power_progress = (power - MIN_PWR) * 10 / (MAX_PWR - MIN_PWR);
    fprintf(file, "%d dBm [", MIN_PWR);
    for (int i = 0; i < 10; i++) {
      if (i < power_progress) {
        fprintf(file, "\033[32m#");
      } else {
        fprintf(file, "\033[31m-");
      }
    }
    // Reset color after power bar
    fprintf(file, "\033[0m] %d dBm\t", MAX_PWR);

    // Calculate and print signal level bar
    int signal_progress = (signal - MIN_SIG) * 10 / (MAX_SIG - MIN_SIG);
    fprintf(file, "%d dBm [", MIN_SIG);
    for (int i = 0; i < 10; i++) {
      if (i < signal_progress) {
        fprintf(file, "\033[32m#");
      } else {
        fprintf(file, "\033[31m-");
      }
    }
    // Reset color after progress bar
    fprintf(file, "\033[0m] %d dBm\n", MAX_SIG);
  }

  fflush(file);
}
