#include <iostream>
#include <time.h>
class MyArray;
class Int;
class MyArray{
  friend Int;

  const int dim;
  int *size;
  struct Address{
    int level;
    void* next;
  };
  Address* top;
public:
  MyArray(int dim, int* size):dim(dim)
  {
    this->size = new int[dim];
    for(int i = 0; i < dim; i++)
      this->size[i] = size[i];
    top = new Address;
    top -> level = 0;
    InitializeAddress(top);
  }
  void InitializeAddress(Address* curr)
  {
    if (!curr) return;
    if(curr->level == dim - 1)
    {
      curr->next = new int[size[dim - 1]];
      return;
    }
    curr->next = new Address[size[curr->level]];
    for(int i = 0; i < size[curr->level]; i++)
    {
      (static_cast<Address*>(curr->next) + i)->level = curr->level + 1;
      InitializeAddress(static_cast<Address*>(curr->next) + i);
    }
  }
  void FreeAddress(Address* curr)
  {
    if(curr->level == dim - 1)
    {
      delete[] static_cast<int*>(curr->next);
      return;
    }
    for(int i = 0; i < size[curr->level]; i++)
    {
      static_cast<Address*>(curr->next)[i].level = curr->level + 1;
      FreeAddress(static_cast<Address*>(curr->next) + i);
    }
    delete[] static_cast<Address*>(curr);
  }
  ~MyArray()
  {
    delete[] size;
    FreeAddress(top);
  }
  Int operator[](const int& n);
};

class Int{
  void* data;
  int level;
  MyArray* arr;
public:
  Int(int level, int index, MyArray* arr): level(level), arr(arr)
  {
    data = arr->top;
    if(level == arr->dim)
    {
      data = (static_cast<int*>(static_cast<MyArray::Address*>(data)->next)) + index;
    }
    else
    data = (static_cast<MyArray::Address*>(static_cast<MyArray::Address*>(data)->next)) + index;
  }
  Int& operator[](const int& n)
  {
    level++;
    if(level == arr->dim)
    {
      data = (static_cast<int*>(static_cast<MyArray::Address*>(data)->next)) + n;
    }
    else
    data = (static_cast<MyArray::Address*>(static_cast<MyArray::Address*>(data)->next)) + n;
    return *this;
  }
  int operator=(const int& n)
  {
    *static_cast<int*>(data) = n;
    return n;
  }
  operator int(){ //읽을때만 사용가능.
  return *static_cast<int *>(data);
  }
};
Int MyArray::operator[](const int& n)
  {
    Int num(1, n, this);
    return num;
  }
int main()
{
   clock_t start = clock();
  int size[3] = {2, 3, 4};
  MyArray arr(3, size);
 for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                  << std::endl;
      }
    }
  }
  clock_t end = clock();
  printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
}