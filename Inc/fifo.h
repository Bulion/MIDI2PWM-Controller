/*
 * fifo.hpp
 *
 *  Created on: 05.11.2017
 *      Author: Dawid Sliwa
 */

#include <stdint.h>

#ifndef FIFO_H
#define FIFO_H

typedef struct {
	uint8_t status;
	uint8_t channel;
	uint8_t data1;
	uint8_t data2;
}midiData_t;

typedef struct {
	uint16_t head;
	uint16_t tail;
	uint16_t size;
	midiData_t *midiData;
} midiFifo;

void initFifo(midiFifo *fifo);
uint8_t push(midiFifo *fifo, midiData_t *newData);
midiData_t pop(midiFifo *fifo);
void clear(midiFifo *fifo);

#endif /* FIFO_H */
