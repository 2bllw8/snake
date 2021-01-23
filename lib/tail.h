#ifndef SNAKE_TAIL_H
#define SNAKE_TAIL_H

#include "directions.h"
#include "display.h"

#include <stdbool.h>
#include <stdint.h>

#define TAIL_INITIAL_MAX_DEPTH 6

typedef struct tail_t tail_t;

tail_t *tail_new(uint8_t x, uint8_t y, tail_t *next);
void tail_destroy(tail_t *);

uint8_t tail_x(tail_t *);
uint8_t tail_y(tail_t *);

void tail_increase_max_depth(tail_t *);
tail_t *tail_prepend(tail_t *, direction_t);
bool tail_contains(tail_t *, uint8_t x, uint8_t y);

game_display_t tail_display(tail_t *, uint8_t x, uint8_t y);

#endif