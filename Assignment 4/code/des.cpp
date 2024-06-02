#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<curses.h>
#define BYTE unsigned char
#define INT unsigned int
typedef unsigned int UINT;
using namespace std;


void unpacking_bytes(BYTE *,BYTE *);
void packing_bytes(BYTE *,BYTE *);
void set_Key(int ,BYTE *,int);
void des_6_round_function(BYTE *,BYTE *,UINT r,char f);

UINT Initial_Permutation[] = {
  58,50,42, 34,26,18,10,2,
  60,52,44,36,28,20,12,4,
  62,54, 46, 38, 30, 22, 14,6,
  64, 56, 48, 40,32,24, 16, 8,
  57, 49, 41, 33,25,17, 9,1,
  59, 51,43,35,27,19,11,3,
  61,53,45,37,29,21,13, 5,
  63,55, 47,39,31,23,15,7
};
UINT Sbox[8][64]=
{
  14, 4, 13, 1, 2, 15, 11, 8, 3 , 10, 6, 12, 5, 9, 0, 7,
  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
  4, 1 , 14, 8, 13, 6, 2, 11, 15, 12, 9, 7,3, 10, 5, 0,
  15, 12, 8,2,4, 9, 1,7 , 5, 11, 3, 14, 10, 0, 6, 13 ,

  15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0,5, 10,
  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
  0, 14, 7, 11, 10, 4, 13, 1, 5, 8,12, 6, 9, 3, 2, 15,
  13, 8, 10, 1, 3, 15, 4, 2,11,6, 7, 12, 0,5, 14, 9,

  10, 0, 9,14,6,3,15,5, 1, 13, 12, 7, 11, 4,2,8,
  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,5, 10, 14, 7,
  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,

  7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
  10, 6, 9, 0, 12, 11, 7, 13, 15, 1 , 3, 14, 5, 2, 8, 4,
  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,


  2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
  14, 11,2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,



  12, 1, 10, 15, 9, 2, 6,8, 0, 13, 3, 4, 14, 7, 5, 11,
  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
  9, 14, 15, 5, 2,8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

  4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

  13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12,7,
  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };



UINT reverse_final_permutation[] = {
  8,40,16,48,24,56,32,64,
  7, 39,15,47,23,55,31,63,
  6,38,14,46,22,54,30,62,
  5,37,13,45, 21,53,29,61,
  4,36,12,44,20,52,28,60,
  3, 35, 11,43,19,51,27,59,
  2, 34, 10, 42,18, 50,26,58,
  1,33,9,41, 17, 49, 25,57,
};

UINT Permutation_Box[] = {
  16, 7, 20, 21,
  29, 12, 28, 17,
  1, 15, 23, 26,
  5, 18, 31,10,
  2, 8, 24, 14,
  32, 27, 3, 9,
  19, 13, 30, 6,
  22, 11, 4, 25,
};

UINT Expansion_Box[] = {
  32, 1, 2, 3, 4, 5,
  4, 5,6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1
};

UINT Inverse_Permutation_Box[] = {
	9, 17, 23, 31,
	13, 28, 2, 18,
	24, 16, 30, 6,
	26, 20, 10, 1,
	8, 14, 25, 3,
	4, 29, 11, 19,
	32, 12, 22, 7,
	5, 27, 15, 21,
};


int inverse_final_Permutation_Box[]= {
 57,49,41,33,25,17,9,1,
 59,51,43,35,27,19,11,3,
 61,53,45,37,29,21,13,5,
 63,55,47,39,31,23,15,7,
 58,50,42,34,26,18,10,2,
 60,52,44,36,28,20,12,4,
 62,54,46,38,30,22,14,6,
 64,56,48,40,32,24,16,8
};

unsigned short shiftings[] = {
1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

UINT PerCom[] = {
  14, 17, 11, 24,  1, 5,
  3, 28 ,15,  6, 21, 10,
  23, 19, 12,  4, 26, 8,
  16,  7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55,
  30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53,
  46, 42, 50, 36, 29, 32
};
  
int inverse_initial_permutation[]={
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25};

BYTE Key_Scheduler[16][48];
int main()
{
    BYTE password[9];
    BYTE key[56]={0,1,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1};
    set_Key(1,key,6);
    BYTE encrypted_password_1[9]={10,100,209,148,165,47,95,129,'\0'};
    BYTE encrypted_password_2[9]={245,142,170,88,20,13,65,87,'\0'};
    des_6_round_function(encrypted_password_1,password,6,'N');
    int i=0;
    while(i<8){
      cout<<password[i];
      i++;
    }
    
    des_6_round_function(encrypted_password_2,password,6,'N');
    for(int i=0;i<8;i++)
    cout<<password[i];
    return 0;
}
void unpacking_bytes(BYTE *packed, BYTE *binary_representation) {
    register UINT i = 0, j, k;

    while (i < 8) {
        k = *packed++;
        j = 0;
        while (j < 8) {
            *binary_representation++ = (k >> (7 - j)) & 1;
            ++j;
        }
        ++i;
    }
}

void packing_bytes(BYTE *packed, BYTE *binary_representation) {
    register UINT i = 0, j, k;

    while (i < 8) {
        k = 0;
        j = 0;
        while (j < 8) {
            k = (k << 1) + *binary_representation++;
            ++j;
        }
        *packed++ = k;
        ++i;
    }
}

void set_Key(int s1, BYTE *DC, int r) {
    register UINT i = 0, j, k, t1, t2;
    int z;
    while (i < r) {
        j = 0;
        while (j < shiftings[i]) {
            t1 = DC[0];
            t2 = DC[28];
            k = 0;
            while (k < 27) {
                DC[k] = DC[k + 1];
                DC[k + 28] = DC[k + 29];
                ++k;
            }
            DC[27] = t1;
            DC[55] = t2;
            ++j;
        }
        j = s1 ? r - 1 - i : i;
        k = 0;
        while (k < 48) {
            Key_Scheduler[j][k] = DC[PerCom[k] - 1];
            ++k;
        }
        ++i;
    }
}

void des_6_round_function(BYTE *in, BYTE *out, UINT r, char flag) {
    register UINT i = 0, j, k, t;
    static BYTE block[64];
    static BYTE LR[64], f[32], preS[48];
    int z;
    unpacking_bytes(in, block);
    j = 0;
    while (j < 64) {
        LR[j] = block[inverse_final_Permutation_Box[j] - 1];
        ++j;
    }
    while (i < r) {
        j = 0;
        while (j < 48) {
            preS[j] = LR[Expansion_Box[j] - 1] ^ Key_Scheduler[i][j];
            ++j;
        }
        j = 0;
        while (j < 8) {
            k = 6 * j;
            t = preS[k];
            t = (t << 1) | preS[k + 5];
            t = (t << 1) | preS[k + 1];
            t = (t << 1) | preS[k + 2];
            t = (t << 1) | preS[k + 3];
            t = (t << 1) | preS[k + 4];
            t = Sbox[j][t];
            k = 4 * j;
            f[k] = (t >> 3) & 1;
            f[k + 1] = (t >> 2) & 1;
            f[k + 2] = (t >> 1) & 1;
            f[k + 3] = t & 1;
            ++j;
        }
        j = 0;
        while (j < 32) {
            t = LR[j];
            if (flag == 'N')
                LR[j] = LR[j + 32] ^ f[Permutation_Box[j] - 1];
            else
                LR[j] = LR[j + 32] ^ f[Inverse_Permutation_Box[j] - 1];
            LR[j + 32] = t;
            ++j;
        }
        ++i;
    }
    j = 0;
    while (j < 64) {
        block[j] = LR[inverse_initial_permutation[j] - 1];
        ++j;
    }
    packing_bytes(out, block);
    out[9] = '\0';
}
