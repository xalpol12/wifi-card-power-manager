#include "globals.h"
#include <linux/if.h>
#include <linux/wireless.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/*
 * Reads the transmit power and signal level of the specified wireless interface
 * using the ioctl system call and stores them in the provided power and signal
 * variables respectively.
 */
int read_signal_levels(const char *interface, int *power, int *signal) {
  int sfd;
  struct iwreq iw;
  struct iw_statistics iw_stats;

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Error creating socket");
    return EXIT_FAILURE;
  }

  strncpy(iw.ifr_name, interface, IFNAMSIZ);
  if (ioctl(sfd, SIOCGIWTXPOW, &iw) == -1) {
    perror("Error reading transmit power level");
    close(sfd);
    return EXIT_FAILURE;
  }
  *power = iw.u.txpower.value;

  iw.u.data.pointer = &iw_stats;
  iw.u.data.length = sizeof(struct iw_statistics);
  iw.u.data.flags = 1;
  if (ioctl(sfd, SIOCGIWSTATS, &iw) == -1) {
    perror("Error reading wireless statistics");
    close(sfd);
    return EXIT_FAILURE;
  }
  *signal = (int8_t)iw_stats.qual.level;

  close(sfd);
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
 * This function adjusts the transmission power level of a specified wireless
 * interface by using the ioctl system call.
 */
void adjust_power_level(char *interface, int power) {
  int sfd;
  struct iwreq iw;

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Error creating socket");
    return;
  }

  strncpy(iw.ifr_name, interface, IFNAMSIZ);
  if (ioctl(sfd, SIOCGIWTXPOW, &iw) == -1) {
    perror("Error reading transmit power level");
    close(sfd);
    return;
  }
  iw.u.txpower.value = power;

  if (ioctl(sfd, SIOCSIWTXPOW, &iw) == -1) {
    perror("Error setting transmit power level");
    close(sfd);
    return;
  };

  close(sfd);
}
