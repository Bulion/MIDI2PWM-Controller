/*
 * fifo.cpp
 *
 *  Created on: 05.11.2017
 *      Author: Dawid Sliwa
 */
#include "fifo.h"

#define FIFO_SIZE 255

midiData_t fifoData[FIFO_SIZE];

void initFifo(midiFifo *fifo)
{
	fifo->head = 0;
	fifo->tail = 0;
	fifo->size = FIFO_SIZE;
	fifo->midiData = fifoData;
}

uint8_t push(midiFifo *fifo, midiData_t *newData)
{
	if( (fifo->head + 1 == fifo->tail) ||
			( (fifo->head + 1 == fifo->size) && (fifo->tail == 0) ) )
	{
		return 0;
	}
	else
	{
		fifo->midiData[fifo->head++] = newData[0];
		if(fifo->head == fifo->size)
		{
			fifo->head = 0;
		}
	}
	return 1;
}

midiData_t pop(midiFifo *fifo)
{
	midiData_t returnVal = {.status = 0, .channel = 0, .data1 = 0, .data2 = 0};
	if( fifo->tail != fifo->head )
	{
		returnVal = fifo->midiData[fifo->tail++];
		if( fifo->tail == fifo->size )
		{
			fifo->tail = 0;
		}
	}
	return returnVal;
}

void clear(midiFifo *fifo)
{
	fifo->head = fifo->tail;
}



