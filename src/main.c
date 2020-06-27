#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

//명령어들
typedef enum {
	HLT, // 0   hlt              프로그램 종료
	PSH, // 1   psh val          `val` 을 stack에 푸시
	POP, // 2   pop              스택에서 팝
	ADD, // 3   add              스택에 맨 위 2원소를 더해서 push
	MUL, // 4   mul              스택에 맨 위 2원소를 곱해서 push
	DIV, // 5   div              스택에 맨 위 2원소를 나누어서 push
	SUB, // 6   sub              스택에 맨 위 2원소를 빼서 push
	SLT, // 7   slt reg_a, reg_b 스택에 (reg_a < reg_b) 푸시
	MOV, // 8   mov reg_a, reg_b reg_a를 reg_b에 대입
	SET, // 9   set reg, val     reg를 val로 설정
	LOG, // 10  log a            a 레지스터 출력
	IF,  // 11  if reg val ip    만약 reg == val 이면 현제 IP를 ip로 이동
	IFN, // 12  ifn reg val ip   만약 reg != val 이면 현제 IP를 ip로 이동
	GLD, // 13  gld reg          reg를 스택에 푸시
	GPT, // 14  gpt reg          스택 맨 위를 reg에 
	NOP  // 15  nop              아무것도 안함
} InstructionSet;

typedef enum {
	A, B, C, D, E, F,
	EX, EXA, 
	IP, //Instruction pointer
	SP, //StackPointer
	NUM_OF_REGISTERS
} Registers;

int ip = 0;
bool bRunning = true;
bool bIsJump = false;

//stack
int sp = -1;
int stack[256];
int registers[NUM_OF_REGISTERS];

InstructionSet instructions[1024];

#define SP (registers[SP])
#define IP (registers[IP])

int fetch()
{
	return instructions[IP];
}

void eval(const int instruction)
{
	switch (instruction)
	{
	case HLT:
		bRunning = false;
		printf("End Program\n");
		break;
	case PSH:
		SP++;
		IP++;
		stack[SP] = instructions[IP];
		break;
	case POP:
		SP--;
		break;
	case ADD:
		registers[A] = stack[SP--];
		registers[B] = stack[SP];
		registers[C] = registers[B] + registers[A];
		stack[SP] = registers[C];
		printf("(register B : %d) + (register A : %d) = (register C : %d)\n", registers[B], registers[A], registers[C]);
		break;
	case MUL:
		registers[A] = stack[SP--];
		registers[B] = stack[SP];
		registers[C] = registers[B] * registers[A];
		stack[SP] = registers[C];
		printf("(register B : %d) * (register A : %d) = (register C : %d)\n", registers[B], registers[A], registers[C]);
		break;
	case DIV:
		registers[A] = stack[SP--];
		registers[B] = stack[SP];
		registers[C] = registers[B] / registers[A];
		stack[SP] = registers[C];
		printf("(register B : %d) / (register A : %d) = (register C : %d\n)", registers[B], registers[A], registers[C]);
		break;
	case SUB:
		registers[A] = stack[SP--];
		registers[B] = stack[SP];
		registers[C] = registers[B] - registers[A];
		stack[SP] = registers[C];
		printf("(register B : %d) - (register A : %d) = (register C : %d\n)", registers[B], registers[A], registers[C]);
		break;
	case SLT:
		stack[--SP] = stack[SP + 1] < stack[SP];
		break;
	case MOV:
		registers[instructions[IP + 2]] = registers[instructions[IP + 1]];
		IP += 2;
		break;
	case SET:
		registers[instructions[IP + 1]] = instructions[IP + 2];
		printf("SET : registers %c = %d\n", 'A' + instructions[IP + 1], instructions[IP + 2]);
		IP += 2;
		break;
	case LOG:
		printf("registers is %d\n", registers[instructions[++IP]]);
		break;
	case IF:
		if (registers[instructions[IP + 1]] == instructions[IP + 2])
		{
			IP = instructions[IP + 3];
			bIsJump = true;
		}
		else
		{
			IP = IP + 3;
		}
		break;
	case IFN:
		if (registers[instructions[IP + 1]] != instructions[IP + 2])
		{
			IP = instructions[IP + 3];
			bIsJump = true;
		}
		else
		{
			IP = IP + 3;
		}
		break;
	case GLD:
		SP++;
		IP++;
		stack[SP] = registers[instructions[IP]];
		break;
	case GPT:
		registers[instructions[IP + 1]] = stack[SP];
		IP++;
		break;
	case NOP:
		break;
	default:
		assert(false);
	}
}

int main(int argc, char** argv)
{
	SP = -1;
	FILE* file = fopen(argv[1], "r");
	assert(file != NULL);
	int num, instructionCnt = 0;
	while (fscanf(file, "%d", &num) > 0)
	{
		instructions[instructionCnt] = (InstructionSet)num;
		printf("%d\n", instructions[instructionCnt++]);
	}
	while (bRunning && IP < instructionCnt)
	{
		bIsJump = false;
		eval(fetch());
		if (!bIsJump)
		{
			IP++;
		}
	}

	fclose(file);
	return 0;
}

