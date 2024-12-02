#include"custom_queue.h"

#include <stdlib.h>
#include"log.h"

void queue_init(queue *mQueue)
{
  memset(mQueue, 0, sizeof(queue));
}

bool queue_pop(queue *mQueue, uint8_t *value)
{
  if (queue_is_empty(mQueue))
  {
    return false;
  }
  *value = mQueue->data[mQueue->head++];
  mQueue->head %= QUEUE_MAX_SIZE;
  return true;
}

bool queue_pop_arr(queue *mQueue, uint8_t *value, uint16_t len)
{
  if (QUEUE_MAX_SIZE -  queue_get_space(mQueue) - 1 < len)
  {
    return false;
  }
  while (len > 0)
  {
    queue_pop(mQueue,value++);
    len--; 
  }
  return true;
}

bool queue_peek(queue *mQueue, uint8_t *value)
{
  if (queue_is_empty(mQueue))
  {
    return false;
  }
  *value = mQueue->data[mQueue->head];
  return true;
}

bool queue_push(queue *mQueue, uint8_t value)
{
  if (queue_is_full(mQueue))
  {
    return false;
  }
  mQueue->data[mQueue->tail++] = value;
  mQueue->tail %= QUEUE_MAX_SIZE;
  return true;
}

bool queue_push_arr(queue *mQueue, uint8_t *value, uint16_t len)
{
  if (queue_get_space(mQueue) < len)
  {
    printf("not enough space to push \n");
    return false;
  }
  while (len >0)
  {
    mQueue->data[mQueue->tail] = *value;
    mQueue->tail = ( mQueue->tail+1)%QUEUE_MAX_SIZE;
    len--;
    value++; 
  }
  return true;
}

bool queue_is_full(queue *mQueue)
{
  if ((mQueue->tail + 1) % QUEUE_MAX_SIZE == mQueue->head)
  {
    return true;
  }
  return false;
}

bool queue_is_empty(queue *mQueue)
{
  if (mQueue->head == mQueue->tail)
  {
    return true;
  }
  return false;
}

uint8_t queue_get_space(queue *mQueue)
{
  if (mQueue->head > mQueue->tail)
  {
    return mQueue->head - mQueue->tail - 1;
  }

  if (mQueue->head < mQueue->tail)
  {
    return QUEUE_MAX_SIZE - mQueue->tail + mQueue->head - 1;
  }
  if (mQueue->head == mQueue->tail)
  {
    return QUEUE_MAX_SIZE - 1;
  }
  return 0;
}

bool queue_reset_push(queue *mQueue, uint8_t idx)
{
  if (mQueue->head < mQueue->tail)
  {
    if (idx >= mQueue->head && idx <= mQueue->tail)
    {
      mQueue->tail = idx;
      return true;
    }
  }

  if (mQueue->head < mQueue->tail)
  {
    if ((idx >=0 &&idx <= mQueue->tail) || (idx <=  QUEUE_MAX_SIZE && idx >= mQueue->head))
    {
      mQueue->tail = idx;
      return true;
    }
  }

  if (mQueue->head == mQueue->tail && idx == mQueue->head)
  {
    return true;
  }
  return false;
}

