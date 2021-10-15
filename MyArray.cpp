#include <iostream>
class MyArray{
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
    for(int i = 0; i < dim; i++)
      this->size[i] = size[i];
    top = new Address;
    top -> level = 0;
    InitializeAddress(top);
  }
  void InitializeAddress(Address* curr)
  {
    if(curr->level == dim - 1)
    {
      curr->next = new int[size[dim - 1]];
      return;
    }
    curr->next = new Address[size[curr->level]];
    for(int i = 0; i < size[curr->level]; i++)
    {
      static_cast<Address*>(curr->next)[i].level = curr->level + 1;
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
};
class Int{

};