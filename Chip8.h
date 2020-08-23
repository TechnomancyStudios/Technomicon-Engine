#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

const unsigned int MEMORY_SIZE = 4096;
const unsigned int ROM_LOC = 0x200;
const unsigned int FONT_START = 0x50;
const unsigned int FONT_END = 0xA0;
const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;

using std::cout;
using std::endl;

struct CPU
{
	uint8_t memory[MEMORY_SIZE]{ 0 };

	uint8_t V[16];
	uint16_t I = 0;
	uint16_t PC = ROM_LOC;
	uint16_t stack[16];
	uint8_t SP = 0;
	uint8_t DT = 0;
	uint8_t ST = 0;
	uint16_t opcode;
	uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT];
	uint8_t keypad[16]{0};

	uint8_t font[FONT_START]
	{
		0xF0,0x90,0x90,0x90,0xF0,// 0
		0x20,0x60,0x20,0x20,0x70,// 1
		0xF0,0x10,0xF0,0x80,0xF0,// 2
		0xF0,0x10,0xF0,0x10,0xF0,// 3
		0x90,0x90,0xF0,0x10,0x10,// 4
		0xF0,0x80,0xF0,0x10,0xF0,// 5
		0xF0,0x80,0xF0,0x90,0xF0,// 6
		0xF0,0x10,0x20,0x40,0x40,// 7
		0xF0,0x90,0xF0,0x90,0xF0,// 8
		0xF0,0x90,0xF0,0x10,0xF0,// 9
		0xF0,0x90,0xF0,0x90,0x90,// A
		0xE0,0x90,0xE0,0x90,0xE0,// B
		0xF0,0x80,0x80,0x80,0xF0,// C
		0xE0,0x90,0x90,0x90,0xE0,// D
		0xF0,0x80,0xF0,0x80,0xF0,// E
		0xF0,0x80,0xF0,0x80,0x80 // F
	};

	std::default_random_engine randGen;
	std::uniform_int_distribution<int> randByte;

	CPU();

	void LoadROM(char const* filename);
	void Cycle();
	void Timer();

	void Table0();
	void Table8();
	void TableE();
	void TableF();

	void OP_00E0();//CLS
	void OP_00EE();//RET
	void OP_1nnn();//JMP
	void OP_2nnn();//CALL
	void OP_3xkk();//SE Vx, kk
	void OP_4xkk();//SNE Vx, kk
	void OP_5xy0();//SE Vx, Vy
	void OP_6xkk();//LD Vx, kk
	void OP_7xkk();//ADD Vx, kk
	void OP_8xy0();//LD Vx, Vy
	void OP_8xy1();//OR Vx, Vy
	void OP_8xy2();//AND Vx, Vy
	void OP_8xy3();//XOR Vx, Vy
	void OP_8xy4();//ADD Vx, Vy Carry
	void OP_8xy5();//SUB Vx, Vy
	void OP_8xy6();//SHR Vx {, Vy}
	void OP_8xy7();//SUBN Vx, Vy
	void OP_8xyE();//SHL Vx {, Vy}
	void OP_9xy0();//SNE Vx, Vy
	void OP_Annn();//LD I, addr
	void OP_Bnnn();//JP V0, addr
	void OP_Cxkk();//RND Vx, byte
	void OP_Dxyn();//DRW Vx, Vy, nibble
	void OP_Ex9E();//SKP Vx
	void OP_ExA1();//SKNP Vx
	void OP_Fx07();//LD Vx, DT
	void OP_Fx0A();//LD Vx, K
	void OP_Fx15();//LD DT, Vx
	void OP_Fx18();//LD ST, Vx
	void OP_Fx1E();//ADD I, Vx
	void OP_Fx29();//LD F, Vx
	void OP_Fx33();//LD B, Vx
	void OP_Fx55();//LD [I], Vx
	void OP_Fx65();//LD Vx, [I]
	void OP_NULL();

	typedef void (CPU::* Chip8Func)();
	Chip8Func table[0xF + 1]{ &CPU::OP_NULL };
	Chip8Func table0[0xE + 1]{ &CPU::OP_NULL };
	Chip8Func table8[0xE + 1]{ &CPU::OP_NULL };
	Chip8Func tableE[0xE + 1]{ &CPU::OP_NULL };
	Chip8Func tableF[0x65 + 1]{ &CPU::OP_NULL };
};
