#include <SoftwareSerial.h>
#include"public.h"
#include"get_file.h"

#define COLS 20

unsigned int MEM[MAX_MEM] = {0}, ADDER = 0;
unsigned int STACK[MAX_STACK] = {0};
unsigned int buf[MAX_BUF] = {0};
SoftwareSerial mySerial(10, 11); // RX, TX


enum
{
  _INPUT = 10, PRINT, LOAD = 20, STORE, SET,
  ADD = 30, SUB, MUL, DIV, MOD, INC, _DEC, NEG,
  JMP = 40, JMPN, JMPZ, HALT,
  AND = 50, OR, XOR,
  PUSH = 60, POP
};
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("\tSimple Machine Language Simulator v5.0");
}

void loop()
{
  help();
  console();
}

void init_SML()
{
  memset(MEM, 0, sizeof(int) * MAX_MEM);
}

int input_code()
{
  Serial.println("\nEnter FFFF to end input.\n\n");
  unsigned int ct = 0, li = 0;
  while (1)
  {
    Serial.println(li);
    Scanf(buf);
    ct = convert_N(buf);
    Serial.println(ct);
    if (ct == 65535)
    {
      break;
    }
    MEM[li++] = ct;
  }
  return li - 1;
}

void runSML() //
{
  uint operand = 0, pcode = 0, pstack = 0;
  while (pcode < MAX_MEM)
  {
    int op = MEM[pcode] / 1000;    //xxbb
    operand = MEM[pcode] % 1000;
    switch (op)
    {
      case _INPUT: Serial.print("INPUT:");
        Serial.println(MEM[operand] = Scanf_data());
        break;
      case PRINT: Serial.println(MEM[operand]);
        break;
      case LOAD: ADDER = MEM[operand];
        break;
      case STORE: MEM[operand] = ADDER;
        break;
      case SET: ADDER = operand;
        break;
      case ADD: ADDER += MEM[operand];
        break;
      case SUB: ADDER -= MEM[operand];
        break;
      case MUL: ADDER *= MEM[operand];
        break;
      case DIV: ADDER /= MEM[operand];
        break;
      case MOD: ADDER %= MEM[operand];
        break;
      case INC: MEM[operand]++;
        break;
      case _DEC: MEM[operand]--;
        break;
      case NEG: MEM[operand] = -MEM[operand];
        break;
      case JMP: pcode = operand - 1;
        break;
      case JMPN: ADDER < 0 ? pcode = operand - 1 : 0;
        break;
      case JMPZ: ADDER == 0 ? pcode = operand - 1 : 0;
        break;
      case AND: ADDER = ADDER & MEM[operand];
        break;
      case OR: ADDER = ADDER | MEM[operand];
        break;
      case XOR: ADDER = ADDER ^ MEM[operand];
        break;
      case PUSH: pstack < MAX_STACK ? STACK[pstack++] = ADDER : Serial.println("STACK OVERFLOW.");
        break;
      case POP: pstack > 0 ? ADDER = STACK[--pstack] : Serial.println("STACK EMPTY.");
        break;
      case HALT: pcode = MAX_MEM;
        break;
      default: break;
    }
    pcode++;
  }
  Serial.println("HALT.");
}
void split(char *dst, char *str)//for single line chars split to words
{
}

void console()
{
  while (1)
  {
    char dst[10] = {0};
    Serial.println("");
    Serial.print("SML >");
    Scanf(buf);
    convert_S(buf, dst);
    //   split(dst,buf);
    if (0 == strcmp(dst, "help") || 0 == strcmp(dst, "?"))
    {
      help();
      Serial.println(" ");
    }
    else if (0 == strcmp(dst, "dump"))
    {
      dump();
      Serial.println(" ");
    }
    else if (0 == strcmp(dst, "input"))
    {
      init_SML();
      input_code();
      runSML();
    }
    else if (0 == strcmp(dst, "load"))
    {
      Serial.println("get:");
      init_SML();
      get_file();
      runSML();
    }
  }
}

void dump() //Pretty Show Memory For Debugging
{
  int i;
  Serial.println("");
  Serial.print(" ADDER:");
  Serial.println(ADDER);
  Serial.println("MEM   ");
  Serial.print("   ");
  for (i = 0; i < COLS; i++)
  {
    if (i < 10)
    {
      Serial.print("  ");
      Serial.print(' ');
    }
    else Serial.print("  ");
    Serial.print(i);
    Serial.print(" ");
  }
  for (i = 0; i < MAX_MEM; i++)
  {
    if (i % COLS == 0)
    {
      Serial.println(" ");
      Serial.print(" ");
      if (i / COLS < 10)Serial.print(' ');
      Serial.print(i / COLS);
    }
    Serial.print("   ");
    Serial.print( MEM[i]);
    Serial.print(" ");
  }
  Serial.println( );
}
void help()
{
  //  Serial.println("THIS MACHINE HAVE %d(int)MEMORY, %d(int)STACK\n");
  Serial.println("");
  Serial.println("INSTRUCTION IS 5 DECIMAL DIGITS, FORMAT: AABBB");
  Serial.println("AA IS OPERATOR, BBB IS OPERAND");
  Serial.println("PLEASE SEND THE INSTRUCTION CONVERT TO HEX");
  Serial.println("ONLY HAVE ONE REGISTER\n");
  Serial.println("INSTRUCTIONS:");
  Serial.println("\tINPUT:10\tPRINT:11\tLOAD:20\tSTORE:21\tSET:22");
  Serial.println("\tADD:30\tSUB:31\tMUL:32\tDIV:33\tMOD:34\tINC:35\tDEC:36\tNEG:37");
  Serial.println("\tJMP:40\tJMPN:41\tJMPZ:42");
  Serial.println("\tAND:50\tOR:51\tXOR:52");
  Serial.println("\tPUSH:60\tPOP:61");
  Serial.println("\tHALT:FFFF\n");
  Serial.println("THIS SHELL SUPPORTED COMMAND:");
  //  Serial.println("ls\t\t\t[list SML source codes]");
  Serial.println("help | ? \t\t[help]");
  //  Serial.println("load name.sml\t\t[load and run source code]");
  Serial.println("input\t\t\t[open code input mode]");
  //  Serial.println("freq 100000\t\t[set running frequency to 100K Hz]");
  //  Serial.println("exit\t\t\t[exit program]");
  Serial.println("dump\t\t\t[show memories]");
}

unsigned int Scanf_data()
{ byte i;
  unsigned int ct = 0;
  while (1)
  {
    
    i = 0;

    while (Serial.available() > 0 && i < 2)
    {
      ct = (ct << 8) + Serial.read();
      delay(2);
      i++;
    }
    if (ct > 0)return ct;
  }
}
void Scanf(unsigned int *buf)
{
  byte i = 0;
  bool flag = 0;
  while (1)
  {
    while (Serial.available() > 0)
    {
      buf[i++] = Serial.read();
      delay(2);
      flag = 1;
    }
    if (flag == 1)
    {
      break;
    }
  }
}
void convert_S(unsigned int *buf, char * dst)
{
  byte i = 0;
  while (i < 10)
  {
    dst[i] = char(buf[i++]);
  }
}
unsigned int convert_N(unsigned int *buf)
{
  return (buf[0] << 8) + buf[1];
}
