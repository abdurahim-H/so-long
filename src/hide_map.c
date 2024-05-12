#include "so_long.h"

void hide_exit() {
	if (exit_x != -1 && exit_y != -1) {
		printf("Hiding exit at [%d, %d].\n", exit_x, exit_y); // Debug output
		map->data[exit_y][exit_x] = '0'; // Hide the exit
	}
}

void reveal_map(t_map *map) {
	if (exit_x != -1 && exit_y != -1) {
		printf("Revealing exit at [%d, %d].\n", exit_x, exit_y); // Debug output
		map->data[exit_y][exit_x] = 'E'; // Reveal the exit
	}
}