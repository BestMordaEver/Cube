#include "cube.h"
#include <iostream>
using namespace std;

Cube::Cube() {
	cubeReset();
}

Cube::Section Cube::getSection(Side s, int x, int y) {
	return cube[x + 3 * y + 9 * (int)s];
}

int Cube::getIndex(Side s, int x, int y) {
	return x + 3 * y + 9 * (int)s;
}

void Cube::setSection(Section n, Side s, int x, int y) {
	cube[x + 3 * y + 9 * s] = n;
}

void Cube::cubeReset() {
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int s = 0; s < 6; s++)
				switch (s) {
				case 0: setSection(blue, (Side)s, x, y); break;
				case 1: setSection(orange, (Side)s, x, y); break;
				case 2: setSection(green, (Side)s, x, y); break;
				case 3: setSection(red, (Side)s, x, y); break;
				case 4: setSection(white, (Side)s, x, y); break;
				case 5: setSection(yellow, (Side)s, x, y); break;
				}
}

void Cube::print(bool b) {
	for (int y = 0; y < 3; y++) {
		cout << "      ";
		for (int x = 0; x < 3; x++)
			if (b) cout << (char)getSection(U, x, y) << ' '; else cout << getIndex(U, x, y) << ' ';
		cout << endl;
	}

	for (int y = 0; y < 3; y++) {
		for (Side s = L; s != U; s = s == L ? F : (s == F ? R : U))
			for (int x = 0; x < 3; x++)
				if (b) cout << (char)getSection(s, x, y) << ' '; else cout << getIndex(s, x, y) << ' ';
		cout << endl;
	}

	for (Side s = D; s != U; s = s == D ? B : U)
		for (int y = 0; y < 3; y++) {
			cout << "      ";
			if (s == B) cout << "      ";
			for (int x = 0; x < 3; x++)
				if (b) cout << (char)getSection(s, x, y) << ' '; else cout << getIndex(s, x, y) << ' ';
			cout << endl;
		}
}

void Cube::RD() {
	Section temp1 = cube[2], temp2 = cube[5], temp3 = cube[8];

	cube[2] = cube[38]; cube[5] = cube[41]; cube[8] = cube[44];
	cube[38] = cube[20]; cube[41] = cube[23]; cube[44] = cube[26];
	cube[20] = cube[47]; cube[23] = cube[50]; cube[26] = cube[53];
	cube[47] = temp1; cube[50] = temp2; cube[53] = temp3;

	temp1 = cube[9]; temp2 = cube[10];
	cube[9] = cube[11]; cube[10] = cube[14]; cube[11] = cube[17]; cube[14] = cube[16]; cube[17] = cube[15]; cube[16] = cube[12]; cube[15] = temp1; cube[12] = temp2;
	
}

void Cube::RU() {
	Section temp1 = cube[2], temp2 = cube[5], temp3 = cube[8];
	cube[2] = cube[47]; cube[5] = cube[50]; cube[8] = cube[53];
	cube[47] = cube[20]; cube[50] = cube[23]; cube[53] = cube[26];
	cube[20] = cube[38]; cube[23] = cube[41]; cube[26] = cube[44];
	cube[38] = temp1; cube[41] = temp2; cube[44] = temp3;

	temp1 = cube[9]; temp2 = cube[10];
	cube[10] = cube[12]; cube[9] = cube[15]; cube[12] = cube[16]; cube[15] = cube[17]; cube[16] = cube[14]; cube[17] = cube[11]; cube[14] = temp2; cube[11] = temp1;
	
}

void Cube::LD() {
	Section temp1 = cube[0], temp2 = cube[3], temp3 = cube[6];
	cube[0] = cube[36]; cube[3] = cube[39]; cube[6] = cube[42];
	cube[36] = cube[18]; cube[39] = cube[21]; cube[42] = cube[24];
	cube[18] = cube[45]; cube[21] = cube[48]; cube[24] = cube[51];
	cube[45] = temp1; cube[48] = temp2; cube[51] = temp3;

	temp1 = cube[27]; temp2 = cube[28];
	cube[28] = cube[30]; cube[27] = cube[33]; cube[30] = cube[34]; cube[33] = cube[35]; cube[34] = cube[32]; cube[35] = cube[29]; cube[32] = temp2; cube[29] = temp1;
	
}

void Cube::LU() {
	Section temp1 = cube[0], temp2 = cube[3], temp3 = cube[6];
	cube[0] = cube[45]; cube[3] = cube[48]; cube[6] = cube[51];
	cube[45] = cube[18]; cube[48] = cube[21]; cube[51] = cube[24];
	cube[18] = cube[36]; cube[21] = cube[39]; cube[24] = cube[42];
	cube[36] = temp1; cube[39] = temp2; cube[42] = temp3;

	temp1 = cube[27]; temp2 = cube[28];
	cube[27] = cube[29]; cube[28] = cube[32]; cube[29] = cube[35]; cube[32] = cube[34]; cube[35] = cube[33]; cube[34] = cube[30]; cube[33] = temp1; cube[30] = temp2;
	
}

void Cube::UR() {
	Section temp1 = cube[0], temp2 = cube[1], temp3 = cube[2];
	cube[0] = cube[27]; cube[1] = cube[28]; cube[2] = cube[29];
	cube[27] = cube[18]; cube[28] = cube[19]; cube[29] = cube[20];
	cube[18] = cube[9]; cube[19] = cube[10]; cube[20] = cube[11];
	cube[9] = temp1; cube[10] = temp2; cube[11] = temp3;

	temp1 = cube[36]; temp2 = cube[37];
	cube[36] = cube[38]; cube[37] = cube[41]; cube[38] = cube[44]; cube[41] = cube[43]; cube[44] = cube[42]; cube[43] = cube[39]; cube[42] = temp1; cube[39] = temp2;
	
}

void Cube::UL() {
	Section temp1 = cube[0], temp2 = cube[1], temp3 = cube[2];
	cube[0] = cube[9]; cube[1] = cube[10]; cube[2] = cube[11];
	cube[9] = cube[18]; cube[10] = cube[19]; cube[11] = cube[20];
	cube[18] = cube[27]; cube[19] = cube[28]; cube[20] = cube[29];
	cube[27] = temp1; cube[28] = temp2; cube[29] = temp3;

	temp1 = cube[36]; temp2 = cube[37];
	cube[37] = cube[39]; cube[36] = cube[42]; cube[39] = cube[43]; cube[42] = cube[44]; cube[43] = cube[41]; cube[44] = cube[38]; cube[41] = temp2; cube[38] = temp1;
	
}

void Cube::DR() {
	Section temp1 = cube[6], temp2 = cube[7], temp3 = cube[8];
	cube[6] = cube[33]; cube[7] = cube[34]; cube[8] = cube[35];
	cube[33] = cube[24]; cube[34] = cube[25]; cube[35] = cube[26];
	cube[24] = cube[15]; cube[25] = cube[16]; cube[26] = cube[17];
	cube[15] = temp1; cube[16] = temp2; cube[17] = temp3;

	temp1 = cube[45]; temp2 = cube[46];
	cube[46] = cube[48]; cube[45] = cube[51]; cube[48] = cube[52]; cube[51] = cube[53]; cube[52] = cube[50]; cube[53] = cube[47]; cube[50] = temp2; cube[47] = temp1;
	
}

void Cube::DL() {
	Section temp1 = cube[6], temp2 = cube[7], temp3 = cube[8];
	cube[6] = cube[15]; cube[7] = cube[16]; cube[8] = cube[17];
	cube[15] = cube[24]; cube[16] = cube[25]; cube[17] = cube[26];
	cube[24] = cube[33]; cube[25] = cube[34]; cube[26] = cube[35];
	cube[33] = temp1; cube[34] = temp2; cube[35] = temp3;

	temp1 = cube[45]; temp2 = cube[46];
	cube[45] = cube[47]; cube[46] = cube[50]; cube[47] = cube[53]; cube[50] = cube[52]; cube[53] = cube[51]; cube[52] = cube[48]; cube[51] = temp1; cube[48] = temp2;
	
}

void Cube::FR() {
	Section temp1 = cube[9], temp2 = cube[12], temp3 = cube[15];
	cube[9] = cube[36]; cube[12] = cube[36]; cube[15] = cube[42];
	cube[36] = cube[27]; cube[39] = cube[30]; cube[42] = cube[33];
	cube[27] = cube[45]; cube[30] = cube[48]; cube[33] = cube[51];
	cube[45] = temp1; cube[48] = temp2; cube[51] = temp3;

	temp1 = cube[0]; temp2 = cube[1];
	cube[1] = cube[3]; cube[0] = cube[6]; cube[3] = cube[7]; cube[6] = cube[8]; cube[7] = cube[5]; cube[8] = cube[2]; cube[5] = temp2; cube[2] = temp1;
	
}

void Cube::FL() {
	Section temp1 = cube[9], temp2 = cube[12], temp3 = cube[15];
	cube[9] = cube[45]; cube[12] = cube[39]; cube[15] = cube[42];
	cube[45] = cube[27]; cube[48] = cube[30]; cube[51] = cube[33];
	cube[27] = cube[36]; cube[30] = cube[39]; cube[33] = cube[42];
	cube[36] = temp1; cube[39] = temp2; cube[42] = temp3;

	temp1 = cube[0]; temp2 = cube[1];
	cube[0] = cube[2]; cube[1] = cube[5]; cube[2] = cube[8]; cube[5] = cube[7]; cube[8] = cube[6]; cube[7] = cube[3]; cube[6] = temp1; cube[3] = temp2;
	
}

void Cube::BR() {
	Section temp1 = cube[11], temp2 = cube[14], temp3 = cube[17];
	cube[11] = cube[53]; cube[14] = cube[52]; cube[17] = cube[51];
	cube[53] = cube[33]; cube[52] = cube[30]; cube[51] = cube[27];
	cube[33] = cube[36]; cube[30] = cube[37]; cube[27] = cube[38];
	cube[36] = temp1; cube[37] = temp2; cube[38] = temp3;

	temp1 = cube[18]; temp2 = cube[19];
	cube[18] = cube[24]; cube[19] = cube[21]; cube[24] = cube[26]; cube[21] = cube[25]; cube[25] = cube[23]; cube[26] = cube[20]; cube[23] = temp1; cube[20] = temp2;
	
}

void Cube::BL() {
	Section temp1 = cube[11], temp2 = cube[14], temp3 = cube[17];
	cube[11] = cube[36]; cube[14] = cube[37]; cube[17] = cube[38];
	cube[36] = cube[33]; cube[37] = cube[30]; cube[38] = cube[27];
	cube[33] = cube[53]; cube[30] = cube[52]; cube[27] = cube[51];
	cube[53] = temp1; cube[52] = temp2; cube[51] = temp3;

	temp1 = cube[18]; temp2 = cube[19];
	cube[18] = cube[20]; cube[19] = cube[23]; cube[20] = cube[26]; cube[23] = cube[25]; cube[26] = cube[24]; cube[25] = cube[21]; cube[24] = temp1; cube[21] = temp2;
	
}

void Cube::CR() {
	Section temp1 = cube[3], temp2 = cube[4], temp3 = cube[17];
	cube[3] = cube[30]; cube[4] = cube[31]; cube[5] = cube[32];
	cube[30] = cube[21]; cube[31] = cube[22]; cube[32] = cube[23];
	cube[21] = cube[12]; cube[22] = cube[13]; cube[23] = cube[14];
	cube[12] = temp1; cube[13] = temp2; cube[14] = temp3;
	
}

void Cube::CL() {
	Section temp1 = cube[3], temp2 = cube[4], temp3 = cube[5];
	cube[3] = cube[12]; cube[4] = cube[13]; cube[5] = cube[14];
	cube[12] = cube[21]; cube[13] = cube[22]; cube[14] = cube[23];
	cube[21] = cube[30]; cube[22] = cube[31]; cube[23] = cube[32];
	cube[30] = temp1; cube[31] = temp2; cube[32] = temp3;
	
}

void Cube::CU() {
	Section temp1 = cube[1], temp2 = cube[4], temp3 = cube[7];
	cube[1] = cube[46]; cube[4] = cube[49]; cube[7] = cube[52];
	cube[46] = cube[19]; cube[49] = cube[22]; cube[52] = cube[25];
	cube[19] = cube[37]; cube[22] = cube[40]; cube[25] = cube[43];
	cube[37] = temp1; cube[40] = temp2; cube[43] = temp3;
	
}

void Cube::CD() {
	Section temp1 = cube[1], temp2 = cube[4], temp3 = cube[7];
	cube[1] = cube[37]; cube[4] = cube[40]; cube[7] = cube[43];
	cube[37] = cube[19]; cube[40] = cube[22]; cube[43] = cube[25];
	cube[19] = cube[46]; cube[22] = cube[49]; cube[25] = cube[52];
	cube[46] = temp1; cube[49] = temp2; cube[52] = temp3;
	
}

void Cube::ML() {
	Section temp1 = cube[10], temp2 = cube[13], temp3 = cube[16];
	cube[10] = cube[50]; cube[13] = cube[49]; cube[16] = cube[48];
	cube[50] = cube[34]; cube[49] = cube[31]; cube[48] = cube[28];
	cube[34] = cube[39]; cube[31] = cube[40]; cube[28] = cube[41];
	cube[39] = temp1; cube[40] = temp2; cube[41] = temp3;
	
}

void Cube::MR() {
	Section temp1 = cube[10], temp2 = cube[13], temp3 = cube[16];
	cube[10] = cube[39]; cube[13] = cube[40]; cube[16] = cube[41];
	cube[39] = cube[34]; cube[40] = cube[31]; cube[41] = cube[28];
	cube[34] = cube[50]; cube[31] = cube[49]; cube[28] = cube[48];
	cube[50] = temp1; cube[49] = temp2; cube[48] = temp3;
	
}