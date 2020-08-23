#include "Chip8.h"

CPU::CPU() : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
	//Load Font Data into Memory
	for (int i = 0; i < FONT_END - FONT_START; i++)
		memory[FONT_START + i] = font[i];

	//Initialize RNG
	randByte = std::uniform_int_distribution<int>(0, 255U);

	table[0x0] = &CPU::Table0;
	table[0x1] = &CPU::OP_1nnn;
	table[0x2] = &CPU::OP_2nnn;
	table[0x3] = &CPU::OP_3xkk;
	table[0x4] = &CPU::OP_4xkk;
	table[0x5] = &CPU::OP_5xy0;
	table[0x6] = &CPU::OP_6xkk;
	table[0x7] = &CPU::OP_7xkk;
	table[0x8] = &CPU::Table8;
	table[0x9] = &CPU::OP_9xy0;
	table[0xA] = &CPU::OP_Annn;
	table[0xB] = &CPU::OP_Bnnn;
	table[0xC] = &CPU::OP_Cxkk;
	table[0xD] = &CPU::OP_Dxyn;
	table[0xE] = &CPU::TableE;
	table[0xF] = &CPU::TableF;

	table0[0x0] = &CPU::OP_00E0;
	table0[0xE] = &CPU::OP_00EE;

	table8[0x0] = &CPU::OP_8xy0;
	table8[0x1] = &CPU::OP_8xy1;
	table8[0x2] = &CPU::OP_8xy2;
	table8[0x3] = &CPU::OP_8xy3;
	table8[0x4] = &CPU::OP_8xy4;
	table8[0x5] = &CPU::OP_8xy5;
	table8[0x6] = &CPU::OP_8xy6;
	table8[0x7] = &CPU::OP_8xy7;
	table8[0xE] = &CPU::OP_8xyE;

	tableE[0xE] = &CPU::OP_Ex9E;
	tableE[0x1] = &CPU::OP_ExA1;

	tableF[0x07] = &CPU::OP_Fx07;
	tableF[0x0A] = &CPU::OP_Fx0A;
	tableF[0x15] = &CPU::OP_Fx15;
	tableF[0x18] = &CPU::OP_Fx18;
	tableF[0x1E] = &CPU::OP_Fx1E;
	tableF[0x29] = &CPU::OP_Fx29;
	tableF[0x33] = &CPU::OP_Fx33;
	tableF[0x55] = &CPU::OP_Fx55;
	tableF[0x65] = &CPU::OP_Fx65;
}

void CPU::LoadROM(char const* filename)
{
	std::ifstream romReader;
	romReader.open(filename, std::ios::binary | std::ios::ate);


	if (romReader.is_open())
	{
		//Get size of file and allocate a buffer to hold the contents
		std::streampos size = romReader.tellg();
		char* buffer = new char[size];

		//Go back to the beginning of the file to fill in the buffer
		romReader.seekg(0, std::ios::beg);
		romReader.read(buffer, size);
		romReader.close();

		//Load ROM into Memory
		for (long i = 0; i < size; ++i)
			memory[ROM_LOC + i] = buffer[i];

		delete[] buffer;
	}
}

void CPU::Cycle()
{
	for (int i = 0; i < 60000; i++)
	{
	}
	//Fetch
	opcode = (memory[PC] << 8u) | memory[PC + 1];// m[pc] = 0xA4 << 8u = 0xA400 OR 0x0056 = 0xA456
	//Increment the PC before we execute anything
	PC += 2;
	//Decode and Execute
	(this->*table[(opcode & 0xF000u) >> 12u])();
}

void CPU::Timer()
{
	//Decrement the delay timer if it's been set
	if (DT > 0)
		DT--;
	//Decrement the sound timer if it's been set
	if (ST > 0)
		ST--;
}

void CPU::Table0()
{
	(this->*table0[opcode & 0x000Fu])();
}

void CPU::Table8()
{
	(this->*table8[opcode & 0x000Fu])();
}

void CPU::TableE()
{
	(this->*tableE[opcode & 0x000Fu])();
}

void CPU::TableF()
{
	(this->*tableF[opcode & 0x00FFu])();
}

void CPU::OP_NULL()
{}



void CPU::OP_00E0()
{
	//Clear Video Memory
	memset(video, 0, sizeof(video));
}

void CPU::OP_00EE()
{
	//Return from Subroutine
	--SP;
	PC = stack[SP];
}

void CPU::OP_1nnn()
{
	//Jump to Address nnn
	uint16_t address = opcode & 0x0FFF;//Ex: 0x1250 AND 0x0FFF = 0x0250

	PC = address;
}

void CPU::OP_2nnn()
{
	//Call to Subroutine
	uint16_t address = opcode & 0x0FFFu;//Ex: 0x1250 AND 0x0FFF = 0x0250

	//Put current PC address into the Stack
	stack[SP] = PC;
	++SP;
	//Set PC to new address
	PC = address;
}

void CPU::OP_3xkk()
{
	//Skip next instruction if Vx == kk
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	/*
		0x3422
		0x0F00
		------
		0x0400 Bit shift to the right by 8 bits
		0x0004
	*/
	uint8_t byte = (opcode & 0x00FFu);

	if (V[x] == byte)
		PC += 2;
}

void CPU::OP_4xkk()
{
	//Skip next instruction if Vx != kk
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	uint8_t byte = (opcode & 0x00FFu);

	if (V[x] != byte)
		PC += 2;
}

void CPU::OP_5xy0()
{
	//Skip next instruction if Vx == Vy
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (V[x] == V[y])
		PC += 2;
}

void CPU::OP_6xkk()
{
	//Load byte kk into Vx
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = (opcode & 0x00FFu);

	V[x] = byte;
}

void CPU::OP_7xkk()
{
	//Add kk to Vx
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = (opcode & 0x00FFu);

	V[x] = V[x] + byte;
}

void CPU::OP_8xy0()
{
	//Stores the value of register Vy in register Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	V[x] = V[y];
}

void CPU::OP_8xy1()
{
	//OR Vx and Vy, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	V[x] = (V[x] | V[y]);
}

void CPU::OP_8xy2()
{
	//AND Vx and Vy, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	V[x] = (V[x] & V[y]);
}

void CPU::OP_8xy3()
{
	//XOR Vx and Vy, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	V[x] = (V[x] ^ V[y]);
}

void CPU::OP_8xy4()
{
	//ADD Vx and Vy with carry, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	uint16_t sum = V[x] + V[y];

	//Check if sum is greater than 255
	(sum > 255u) ? V[0xF] = 1 : V[0xF] = 0;

	V[x] = (sum & 0xFFu);
}

void CPU::OP_8xy5()
{
	//SUB Vx and Vy with carry, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	//Check if Vx is greater than Vy
	(V[x] > V[y]) ? V[0xF] = 1 : V[0xF] = 0;

	V[x] -= V[y];
}

void CPU::OP_8xy6()
{
	//SHR Vx {, Vy}
	//If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Shift Vx to the right.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	V[0xF] = (V[x] & 0x1u);

	V[x] >>= 1;
}

void CPU::OP_8xy7()
{
	//SUBN Vy and Vx with carry, stores result in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	(V[y] > V[x]) ? V[0xF] = 1 : V[0xF] = 0;

	V[x] = V[y] - V[x];
}

void CPU::OP_8xyE()
{
	//SHL Vx {, Vy}
	//If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Shift Vx to the left.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	V[0xF] = (V[x] & 0x80u) >> 7u;

	V[x] <<= 1;
}

void CPU::OP_9xy0()
{
	//SNE if Vx != Vy skip next instuction
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;

	if (V[x] != V[y])
		PC += 2;
}

void CPU::OP_Annn()
{
	//LD I, addr
	uint16_t addr = (opcode & 0x0FFFu);
	I = addr;
}

void CPU::OP_Bnnn()
{
	//JP V0, addr Jump to addr + V0
	uint16_t addr = (opcode & 0x0FFFu);
	PC = addr + V[0];
}

void CPU::OP_Cxkk()
{
	//RND Vx. byte
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = (opcode & 0x00FFu);

	V[x] = (uint8_t)randByte(randGen) & byte;
}

void CPU::OP_Dxyn()
{
	//RND Vx. byte
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t y = (opcode & 0x00F0u) >> 4u;
	uint8_t height = (opcode & 0x000Fu);

	//Wrap if going beyond screen boundaries
	uint8_t xPos = V[x] % VIDEO_WIDTH;
	uint8_t yPos = V[y] % VIDEO_HEIGHT;

	V[0xF] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = memory[I + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> col);
			uint32_t * screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

			//Sprite pixel is on
			if (spritePixel)
			{
				//Screen Pixel is also on - Collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					V[0xF] = 1;
				}

				//XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void CPU::OP_Ex9E()
{
	//SKP Vx Skip next instruction if key with the value of Vx is pressed.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t key = V[x];

	if (keypad[key])
		PC += 2;
}

void CPU::OP_ExA1()
{
	//SKNP Vx Skip next instruction if key with the value of Vx is not pressed.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t key = V[x];

	if (!keypad[key])
		PC += 2;
}

void CPU::OP_Fx07()
{
	//LD Vx, DT Set Vx = delay timer value.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	V[x] = DT;
}

void CPU::OP_Fx0A()
{
	//LD Vx, K Wait for a key press, store the value of the key in Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	bool pressed = false;

	for (int i = 0; i < 16; i++)
	{
		if (keypad[i])
		{
			V[x] = i;
			pressed = true;
		}
	}

	if (!pressed)
		PC -= 2;

}

void CPU::OP_Fx15()
{
	//LD DT, Vx Set delay timer = Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	DT = V[x];
}

void CPU::OP_Fx18()
{
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	ST = V[x];
}

void CPU::OP_Fx1E()
{
	//ADD I, Set I = I + Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	I += V[x];
}

void CPU::OP_Fx29()
{
	//LD F, Vx Set I = location of sprite for digit Vx.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t digit = V[x];//Character Value
	//Gets the first byte of a character
	I = FONT_START + (5 * digit);
}

void CPU::OP_Fx33()
{
	//LD B, Vx Store BCD representation of Vx in memory locations I, I+1, and I+2.
	uint8_t x = (opcode & 0x0F00u) >> 8u;
	uint8_t value = V[x];

	//Ones-place
	memory[I + 2] = value % 10;
	value /= 10;
	//Tens-place
	memory[I + 1] = value % 10;
	value /= 10;
	//Hundreds-place
	memory[I] = value % 10;
}

void CPU::OP_Fx55()
{
	//LD [I], Vx Store registers V0 through Vx in memory starting at location I.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= x; ++i)
		memory[I + i] = V[i];
}

void CPU::OP_Fx65()
{
	//LD Vx, [I] Store registers V0 through Vx in memory starting at location I.
	uint8_t x = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= x; ++i)
		V[i] = memory[I + i];
}