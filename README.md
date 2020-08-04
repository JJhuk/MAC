# Virtual Machine in C

## 1. 실행 방법

---

```wasm
$./main testcase1.txt
```

## 2. 설명 및 예제

### 2. 1. registers

---

```wasm
레지스터	
-------------------------------
A			
B			
C			
D			
E			
F			
EX 			엑스트라
EXA 		엑스트라2
IP			instruction pointer
SP			stack pointer
```

### 2. 2. 명령어

---

```wasm
opcode  값 usage    			   함수
---------------------------------------------------------------------
HLT  0  -- hlt               프로그램 종료
PSH  1  -- psh val           `val` 을 stack에 푸시
POP  2  -- pop               스택에서 팝
ADD  3  -- add               스택에 맨 위 2원소를 더해서 push
MUL  4  -- mul               스택에 맨 위 2원소를 곱해서 push
DIV  5  -- div               스택에 맨 위 2원소를 나누어서 push
SUB  6  -- sub               스택에 맨 위 2원소를 빼서 push
SLT  7  -- slt reg_a, reg_b  스택에 (reg_a < reg_b) 푸시
MOV  8  -- mov reg_a, reg_b  reg_a를 reg_b에 대입
SET  9  -- set reg, val      reg를 val로 설정
LOG  10 -- log a             a를 출력
IF   11 -- if reg val ip     만약 reg == val 이면 IP를 ip로 이동
IFN  12 -- ifn reg val ip    만약 reg != val 이면 IP를 ip로 이동
GLD  13 -- gld reg           reg를 스택에 푸시함
GPT  14 -- gpt reg           스택 맨 위를 reg에 저장함
NOP  15 -- nop               아무것도 안함.
```

### 2. 3. 1. TestCase 1 (1 + 2 + 3 + ... 200)

---

```wasm
9 5 1
9 6 0
13 5
13 6
3
14 6
2
1 1
3
14 5
12 5 201 6
10 6
0
```

1. 5번째 레지스터에 1을 설정
2. 6번째 레지스터에 0을 설정
3. 5번째 레지스터를 스택에 푸시 
4. 6번쨰 레지스터를 스택에 푸시
5. 스택 맨위 두 수를 더해서 다시 스택에 푸시
6. 맨 위에 있는 스택을 6번째 래지스터에 푸시
7. 스택에서 팝
8. 1을 스택에 푸시
9. 스택 맨위 두 수를 더해서 다시 스택에 푸시
10. 맨 위에 있는 스택을 5번째 레지스터에 푸시
11. 5번째 레지스터가 201이 아니면 IP 6으로 이동 (반복하라는 이야기)
12. 6번째 레지스터를 출력 (결과값 출력)
13. 종료

### Result

![1](https://user-images.githubusercontent.com/31194565/89273498-95744280-d67a-11ea-8700-ae1d834392f3.png)
### 2. 3. 2. TestCase 2 (5 + 1 , if문 작동 확인)

---

```wasm
1 5 
1 1
3 
11 1 9 1 
0
```

1. 스택에 5 푸시
2. 스택에 1 푸시
3. 스택 맨위 2개를 더해서 스택에 푸시
4. 첫번째 레지스터가 9와 같으면 SP를 1로 (당연히 안됨)
5. 종료

### Result

![2](https://user-images.githubusercontent.com/31194565/89273503-986f3300-d67a-11ea-97a8-e034d1240d9c.png)

Base : [https://felixangell.com/blogs/virtual-machine-in-c](https://felixangell.com/blogs/virtual-machine-in-c)
