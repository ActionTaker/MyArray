# MyArray

## struct Address{ int level; void* next;};
>
레벨 0인 Address는 레벨 1짜리의 Address 배열의 주소이다. arr[2][3][4] 가있다면 2는 레벨 1, 3은 레벨2, 레벨2의 next 에서는 int 4개짜리 배열을 가르키고 있어야한다. 즉 n차원 배열일때 n-1레벨의 Address의 next 에 int 배열을 가지고있어야 한다.