#ifndef SNAKE_TAIL_H
#define SNAKE_TAIL_H

#include "directions.h"
#include "display.h"

#include <stdbool.h>
#include <stdint.h>

#define TAIL_INITIAL_MAX_DEPTH 4

typedef struct tail_t tail_t;

/*
 * Make a new (piece of) tail
 */
tail_t *tail_new(uint8_t x, uint8_t y, tail_t *next);

/*
 * Destroy a (piece of) tail
 */
void tail_destroy(tail_t *);

/*
 * Get x coordinate of a (piece of) tail
 */
uint8_t tail_x(tail_t *);

/*
 * Get y coordinate of a (piece of) tail
 */
uint8_t tail_y(tail_t *);

/*
 * Increase the tail max depth
 */
void tail_increase_max_depth(tail_t *);

/*
 * Prepend a piece of tail in the given direction
 */
tail_t *tail_prepend(tail_t *, direction_t);

/*
 * Check whether the tail covers the given coordinate
 */
bool tail_contains(tail_t *, uint8_t x, uint8_t y);

/*
 * Obtain display info for a given coordinate
 * It can be DISPLAY_SNAKE_TAIL or DISPLAY_NONE
 */
game_display_t tail_display(tail_t *, uint8_t x, uint8_t y);

#endif