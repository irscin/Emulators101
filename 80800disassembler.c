#include <stdio.h>
#include <stdlib.h>
//Recebe o código todo num buffer e inicializa o PC
int Disassemble8080(unsigned char *codebuffer, int pc){
    unsigned char *code = &codebuffer[pc];
    int opbytes=1;
    //Guarda os bytes do OPCODE
    //Imprime o PC com 4 zeros na frente e formata como hexadecimal
    printf("%04x\n", pc);
    switch (*code)
    {
    case 0x00: printf("NOP\n"); break;
    case 0x01: printf("LXI    B,#$%02x%02x\n", code[2], code[1]); opbytes=3; break;
    case 0x02: printf("STAX B\n"); break;
    case 0x03: printf("INX B\n"); break;
    case 0x04: printf("INR B\n"); break;
    case 0x05: printf("DCR B\n"); break;
    case 0x06: printf("MVI B, #$%02x\n", code[1]); opbytes=2; break;
    case 0x07: printf("RLC\n"); break;
    case 0x08: printf("NOP\n"); break;
    case 0x09: printf("DAD B\n"); break;
    case 0x0a: printf("LDAX B\n"); break;
    case 0x0b: printf("DCX B\n"); break;
    case 0x0c: printf("INR C\n"); break;
    case 0x0d: printf("DCR C\n"); break;
    case 0x0e: printf("MVI C, #$%02x\n", code[1]); opbytes=2; break;
    case 0x0f: printf("RRC\n"); break;

    }
}

int main (int argc, char**argv)    
   {    
    FILE *f= fopen(argv[1], "rb");    
    if (f==NULL)    
    {    
        printf("error: Couldn't open %s\n", argv[1]);    
        exit(1);    
    }

    //Get the file size and read it into a memory buffer    
    fseek(f, 0L, SEEK_END);    
    int fsize = ftell(f);    
    fseek(f, 0L, SEEK_SET);    

    unsigned char *buffer=malloc(fsize);    

    fread(buffer, fsize, 1, f);    
    fclose(f);    

    int pc = 0;    
    
    while (pc < fsize)    
    {    
        pc += Disassemble8080(buffer, pc);    
    }    
    return 0;    
}