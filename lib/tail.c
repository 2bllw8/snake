#include "directions.h"
#include "display.h"
#include "tail.h"

#include <stdlib.h>

struct tail_t {
	uint8_t x;
	uint8_t y;
	uint16_t depth;
	uint16_t max_depth;
	tail_t *next;
};

void _remove_last(tail_t *tail, uint16_t depth)
{
	if (!tail) {
		return;
	}
	if (depth == 0) {
		tail_destroy(tail->next);
		tail->next = 0;
		return;
	}
	_remove_last(tail->next, depth - 1);
}

tail_t *tail_new(uint8_t x, uint8_t y, tail_t *next)
{
	tail_t *tail = (tail_t *)malloc(sizeof(tail_t));
	if (!tail) {
		return 0;
	}
	tail->x = x;
	tail->y = y;
	tail->depth = next ? next->depth + 1 : 1;
	tail->max_depth = next ? next->max_depth : TAIL_INITIAL_MAX_DEPTH;
	tail->next = next;
	return tail;
}

void tail_destroy(tail_t *tail)
{
	if (!tail) {
		return;
	}

	if (tail->next) {
		tail_destroy(tail->next);
	}
	tail->next = 0;
}

uint8_t tail_x(tail_t *tail)
{
	return tail->x;
}

uint8_t tail_y(tail_t *tail)
{
	return tail->y;
}

void tail_increase_max_depth(tail_t *tail)
{
	tail->max_depth++;
}

tail_t *tail_prepend(tail_t *current, direction_t direction)
{
	uint8_t next_x;
	uint8_t next_y;
	switch (direction) {
	case DIRECTION_UP:
		next_x = current->x;
		next_y = current->y - 1;
		break;
	case DIRECTION_RIGHT:
		next_x = current->x + 1;
		next_y = current->y;
		break;
	case DIRECTION_DOWN:
		next_x = current->x;
		next_y = current->y + 1;
		break;
	case DIRECTION_LEFT:
		next_x = current->x - 1;
		next_y = current->y;
		break;
	}

	tail_t *next = tail_new(next_x, next_y, current);
	if (next->depth > current->max_depth) {
		_remove_last(next, current->max_depth);
	}
	return next;
}

bool tail_contains(tail_t *tail, uint8_t x, uint8_t y)
{
	return tail && ((x == tail->x && y == tail->y) ||
			tail_contains(tail->next, x, y));
}

game_display_t tail_display(tail_t *tail, uint8_t x, uint8_t y)
{
	if (!tail)
		return DISPLAY_NONE;
	if (x == tail->x && y == tail->y)
		return DISPLAY_SNAKE_TAIL;
	return tail_display(tail->next, x, y);
}
