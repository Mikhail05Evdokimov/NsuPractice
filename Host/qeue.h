#include <stdio.h>
#define SIZE 11

typedef struct struct_xyz {
  int id;
  float x;
  float y;
  float z;
}struct_xyz;

void enQueue(int);
struct_xyz deQueue();
void display();

struct_xyz queue[SIZE];
int front = -1;
int rear = -1;

void enQueue(struct_xyz value) {
  if (rear == SIZE - 1)
    printf("Queue is full");
  else {
    if (front == -1)
      front = 0;
    rear++;
    queue[rear] = value;
  }
}

struct_xyz deQueue() {
  if (front == -1)
    printf("No queue");
  else {
    struct_xyz result = queue[front];
    front++;
    if (front > rear)
      front = rear;
      rear = -1;
  }
}