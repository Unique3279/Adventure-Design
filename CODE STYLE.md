**어벤디 코드스타일 규칙**
============================

1. 중괄호는 붙여쓴다. Start of brace must be next to the condition brace.
```c
if(condition){
    // code block
}
```

2. 변수명은 camel case를 사용한다. Use camelCase
```c
int thisIsVariable;
```

3. 축약어는 2자 이하는 대문자로, 3자 이상은 첫글자만 대문자로 작성한다. Abbreviation under 2 letters in CAPs, over 3 letters -> only first letter CAP
```c
void GetFTSensorData() = O
void GetFtSensorData() = X

void GetImuSensorData() = O
void GetIMUSensorData() = X
```

4. 함수명은 동사로 시작한다. Function must starts with verb
```c
void doThis();
```

5. 4번에서 변환함수는 aTob 형식으로 선언한다. Converting function must be "A to B" format
```c
int inchToCm();
float degToRad();
```

6. 상수는 대문자로 선언한다. Constants must be declared with ONLY CAPITALS
```c
#define PI 3.14
const float E = 2.71;
```
