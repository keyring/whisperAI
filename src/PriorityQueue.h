/****************************************************************************
 *
 *    PriorityQueue.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 ***************************************************************************/

#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <ostream>
#include <vector>
#include <cassert>

template <class T>
void Swap(T &a, T &b){
  T temp = a;
  a = b; 
  b = temp;
}

template <class T>
void ReorderUpwards(std::vector<T> &heap, int nd){

  while((nd > 1) && (heap[nd/2] < heap[nd])){
    Swap(heap[nd/2], heap[nd]);
    nd /= 2;
  }
}

template <class T>
void ReorderDownwards(std::vector<T> &heap, int nd, int heapSize){

  while(2 * nd <= heapSize){
    int child = 2 * nd;

    if((child < heapSize) && (heap[child] < heap[child+1])){
      ++child;
    }
    if(heap[nd] < heap[child]){
      Swap(heap[child], heap[nd]);
      nd = child;
    }
    else
      break;
  }
}


/* PriorityQ
 * basic heap based priority queue implementation.
 */
template <class T>
class PriorityQ{

 private:
  std::vector<T> m_heap;
  int m_size;
  int m_maxSize;

  void ReorderUpwards(std::vector<T> &heap, int nd){

    while((nd>1) && (heap[nd/2] < heap[nd])){
      Swap(heap[nd/2], heap[nd]);
      nd /= 2;
    }
  }

  void ReorderDownwards(std::vector<T> &heap, int nd, int heapSize){

    while(2*nd <= heapSize){
      int child = 2*nd;

      if((child < heapSize) && (heap[child] < heap[child+1])){
		  ++child;
	  }

	if(heap[nd] < heap[child]){
	  Swap(heap[child], heap[nd]);
	  nd = child;
	}
	else{
	  break;
	}
    }
  }

 public:
 PriorityQ(int maxSize): m_maxSize(maxSize), m_size(0){

    m_heap.assign(maxSize+1, T());
  }

  bool empty() const { return (m_size == 0); }

  void insert(const T item){

    assert(m_size+1 <= m_maxSize);

    ++m_size;
    m_heap[m_size] = item;
    ReorderUpwards(m_heap, m_size);
  }

  T pop(){
    Swap(m_heap[1], m_heap[m_size]);
    ReorderDownwards(m_heap, 1, m_size-1);
    return m_heap[m_size--];
  }

  const T &peek() const { return m_heap[1]; }
};


/* PriorityQLow
 * basic 2-way heap based priority queue implementation. This time the
 * priority is given to the lowest value key.
 */
template <class T>
class PriorityQLow{

 private:
  std::vector<T> m_heap;
  int m_size;
  int m_maxSize;

  void ReorderUpwards(std::vector<T> &heap, int nd){

    while((nd>1) && (heap[nd/2] > heap[nd])){
      Swap(heap[nd/2], heap[nd]);
      nd /= 2;
    }
  }

  void ReorderDownwards(std::vector<T> &heap, int nd, int heapSize){

    while(2*nd <= heapSize){
      int child = 2 * nd;

      if((child < heapSize) && (heap[child] > heap[child+1])){
	++child;
      }

      if(heap[nd] > heap[child]){
	Swap(heap[child], heap[nd]);
	nd = child;
      }
      else{
	break;
		  }
    }
  }

 public:
 PriorityQLow(int maxSize): m_maxSize(maxSize), m_size(0){

    m_heap.assign(maxSize+1, T());
  }

  bool empty() const { return (m_size == 0); }

  void insert(const T item){

    assert(m_size+1 <= m_maxSize);
    ++m_size;
    m_heap[m_size] = item;
    ReorderUpwards(m_heap, m_size);
  }

  T pop(){

    Swap(m_heap[1], m_heap[m_size]);
    ReorderDownwards(m_heap, 1, m_size-1);
    return m_heap[m_size--];
  }

  const T &peek() const { return m_heap[1]; }
};


/* IndexedPriorityQLow
 * Priority queue based on an index into a set of keys.
 * The queue is maintained as a 2-way heap.
 *
 * The priority in this implementation is the lowest vaued key. */
template <class T>
class IndexedPriorityQLow{

 private:
  std::vector<T> &m_vecKeys;
  std::vector<int> m_heap;
  std::vector<int> m_invHeap;
  int m_size;
  int m_maxSize;

  void Swap(int a, int b){

    int temp = m_heap[a];
    m_heap[a] = m_heap[b];
    m_heap[b] = temp;

    m_invHeap[m_heap[a]] = a;
    m_invHeap[m_heap[b]] = b;
  }

  void ReorderUpwards(int nd){

    while((nd>1) && (m_vecKeys[m_heap[nd/2]] > m_vecKeys[m_heap[nd]])){
      Swap(nd/2, nd);
      nd /= 2;
    }
  }

  void ReorderDownwards(int nd, int heapSize){

    while(2*nd <= heapSize){
      int child = 2 * nd;

      if((child < heapSize) && (m_vecKeys[m_heap[child]] > m_vecKeys[m_heap[child+1]])){
	++child;
      }
      if(m_vecKeys[m_heap[nd]] > m_vecKeys[m_heap[child]]){
	Swap(child, nd);
	nd = child;
      }
      else{
	break;
		  }
    }
  }

 public:
 IndexedPriorityQLow(std::vector<T> &keys, int maxSize):
  m_vecKeys(keys),
    m_maxSize(maxSize),
    m_size(0){

    m_heap.assign(maxSize+1, 0);
    m_invHeap.assign(maxSize+1, 0);
  }

  bool empty() const { return (m_size == 0); }

  void insert(const int idx){

    assert(m_size+1 <= m_maxSize);
    ++m_size;
    m_heap[m_size] = idx;
    m_invHeap[idx] = m_size;
    ReorderUpwards(m_size);
  }

  int pop(){

    Swap(1, m_size);
    ReorderDownwards(1, m_size-1);
    return m_heap[m_size--];
  }

  void ChangePriority(const int idx){

    ReorderUpwards(m_invHeap[idx]);
  }
};

#endif	/* __PRIORITYQUEUE_H__  */
