#include <stdio.h>
#include <stdbool.h>

//명령어들
typedef enum {
	PSH, //pushed to the stack
	ADD, //pops two values on top of stack, adds them pushes to stack
	POP, //pops the value on the stack, will also print it for debugging
	SET, //set register A to 0
	HLT, //stop the program
	MUL, //multiplies top two vals on stack
	DIV, //divides top two vals on stack
	SUB, //subtracts top two vals on stack
	MOV, //movs the value in reg_a to reg_b
	SET, //sets the reg to value
	LOG, //print out a
	IF, //if the register = val branch to the ip
	IFN, //if the register != val branch to the ip
	GLD, //loads a register to the stack
	GPT, //pushes top of stack to the given register
	NOP //Notihing
} InstructionSet;

typedef enum {
	A,B,C,D,E,F,
	EX,EXA, //extra
	IP, //instruction pointer
	SP, // stack pointer
	NUM_OF_REGISTERS
} Registers;

const int program[] = {
	PSH, 5,
	PSH, 6,
	ADD,
	POP,
	HLT
};

//instruction pointer
int ip = 0;
bool running = true;

//stack
int sp = -1;
int stack[256];
int registers[NUM_OF_REGISTERS];

int fetch()
{
	return program[ip];
}

void eval(int instr)
{
	switch(instr)
	{
		case HLT:
			running = false;
			printf("End Program\n");
			break;
		case PSH:
			sp++;
			stack[sp] = program[++ip];
			break;
		case POP:
			registres[A] = stack[sp--];
			printf("popped : %d\n",registers[A]);
			break;
		case ADD:
			registers[A] = stack[sp--];
			registers[B] = stack[sp--];
			registers[C] = registers[B] + registers[A];
			sp++;
			stack[sp] = registers[C];
			break;
		case MUL:
			registers[A] = stack[sp--];
			registers[B] = stack[sp--];
			registers[C] = registers[B] * registers[A];
			sp++;
			stack[sp] = registers[C];
			break;
		case DIV:
			registers[A] = stack[sp--];
			registers[B] = stack[sp--];
			registers[C] = registers[B] / registers[A];
			sp++;
			stack[sp] = registers[C];
			break;
		case SUB:
			registers[A] = stack[sp--];
			registers[B] = stack[sp--];
			registers[C] = registers[B] - registers[A];
			sp++;
			stack[sp] = registers[C];
			break;
		case MOV:
			registers[program[++ip]] = registers[program[++ip]];
			break;		
		case SET:
			registers[]
			break;
		case LOG:
			break;
		case IF:
			break;
		case IFN:
			break;
		case GLD:
			break;
		case GPT:
			sp++;
			stack[sp] 
			break;
		case NOP:
			break;
	}
}

int main()
{
	while(running)
	{
		eval(fetch());
	}
	return 0;
}
