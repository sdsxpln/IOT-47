//
// Created by song on 17-5-7.
//


#include "Queue.h"
void queue_init(Queue *queue, uint8_t size) {

    queue->size = 0;
    queue->cap = size;
    queue->front = 0;
    queue->rear = 0;


}

void queue_in(Queue *queue, uint16_t data) {

    queue->size++;
    queue->s[queue->front] = data;
    queue->front++;
    if (queue->front >= queue->cap) {
        queue->front = queue->front % queue->cap;
    }

}

uint16_t queue_out(Queue *queue) {

    queue->size--;
    uint16_t a = queue->s[queue->rear];
    queue->rear++;
    if (queue->rear >= queue->cap) {
        queue->rear = queue->rear % queue->cap;
    }
    return a;
}