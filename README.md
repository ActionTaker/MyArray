# MyArray

## struct Address{ int level; void* next;};
>
레벨 0인 Address는 레벨 1짜리의 Address 배열의 주소이다. arr[2][3][4] 가있다면 2는 레벨 1, 3은 레벨2, 레벨2의 next 에서는 int 4개짜리 배열을 가르키고 있어야한다. 즉 n차원 배열일때 n-1레벨의 Address의 next 에 int 배열을 가지고있어야 한다.

## void InitializeAddress(Address* curr) 
>
```
void InitializeAddress(Address* curr)
  {
    if(curr->level == dim - 1) //재귀함수 종료 조건
    {
      curr->next = new int[size[dim - 1]];
      return;
    }
    curr->next = new Address[size[curr->level]];  //재귀함수 타고 내려갈때
    for(int i = 0; i < size[curr->level]; i++)    //재귀함수 호출 부분
    {
      static_cast<Address*>(curr->next)[i].level = curr->level + 1;
      InitializeAddress(static_cast<Address*>(curr->next) + i);
    }
  }
```

## void FreeAddress(Address* curr)
>
```
void FreeAddress(Address* curr)
{
  if(curr->level == dim - 1)                     //재귀함수 종료조건
  {
      delete[] static_cast<int*>(curr->next);
      return;
  }
  for(int i = 0; i < size[curr->level]; i++)               //재귀함수 호출부분
  {
      static_cast<Address*>(curr->next)[i].level = curr->level + 1;
      FreeAddress(static_cast<Address*>(curr->next) + i);
  }
   delete[] static_cast<Address*>(curr);           //재귀함수호출 이후에 있으므로 올라갈때
}
  ```
  어떤 코드가 재귀함수 호출 부분 기준으로 위에있냐 아래있느냐에 따라서 올라갈때 실행되는지 내려갈때 실행되는지 바뀐다.

## 재귀함수 특징
>
1. 재귀함수 종료조건 + 명령문
2. 재귀함수 호출부분
3. 명령문
>
재귀함수 종료조건은 대부분 함수 처음에 등장한다. 재귀함수 호출부분을 다음에 어떤 명령문이 쓰여있다면 그 명령문은 바닥을 찍고 올라가는 도중에 실행된다. 재귀함수 호출부분 전에 어떤 명령문이 쓰여 있다면 그명령문은 바닥을 향해 내려가면서 실행된다. 예를들어 
```
int ary[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
void PrintArray(int index)
{
  if(index == 8){cout << ary[8]; return;}
  PrintArray(index+1);
  cout << ary[index];
} 
```
라면 987654321이 출력되고
```
int ary[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
void PrintArray(int index)
{
  if(index == 8){cout << ary[8]; return;}
  cout << ary[index];
  PrintArray(index+1);
} 
```
라면 123456789 가 출력된다.
```
int ary[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
void PrintArray(int index)
{
  if(index == 8){cout << ary[8]; return;}
  PrintArray(index+1);
  cout << ary[index];
  PrintArray(index+1);
} 
```
라면 12345678987654321 이출력된다. 헷갈리면 재귀함수 호출부분에 재귀함수 종료조건의 명령문을 넣어보자.

## class Int{};
>
```
class Int {
  void* data;
  int level;
  Array* array;
};
```
Array의 [] 연산자만 가지고는 제한이 많다 왜냐하면 다중배열의 경우 반환값을 그때마다 다르게 해야하기때문이다. Int 클래스를통해서 현재 어떤배열의 몇번째 배열인지 저장을 하고 최종적으로 int 값을 리턴할수있게 도와준다. 즉, 여러번의 []연산끝에는 data에 int 배열을 가르키는 주소가 남아있게되고 operator int(), Int& operator=(const int& a) 를통해 언제든지 int 형으로 읽히고 쓸준비가 된다.



