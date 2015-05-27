
#include <stdio.h>

/*

chunks in file look like

<XRNDATA08192020001>LenData</XRNDATA>
where "08192" is an ASCII type designator (can expect other types)
where "020001" is an ASCII information field
where Len is a 4-byte little endian length designator
where Data is binary data of Len length

*/

#define XRN 'X', 'R', 'N', 'D', 'A', 'T', 'A'
#define T1  '0', '8', '1', '9', '2'
#define T2  '0', '0', '0', '1', '6'
#define T3  '0', '0', '0', '0', '8'
#define T4  '0', '0', '0', '0', '1'
#define I1  '0', '2', '0', '0', '0', '1'

%%{
machine tds;
write data;
}%%

int main() {
int len = 0;
unsigned char buf[] = {
'<', XRN, T1, I1, '>', 0, 0, 0, 5, 48,49,50,51,52, '<', '/', XRN, '>',
'<', XRN, T2, I1, '>', 0, 0, 0, 1, 10, '<', '/', XRN, '>',
'<', XRN, T3, I1, '>', 0, 0, 0, 1, 10, '<', '/', XRN, '>',
'<', XRN, T4, I1, '>', 0, 0, 0, 1, 10, '<', '/', XRN, '>',
'<', XRN, T1, I1, '>', 0, 0, 0, 0, '<', '/', XRN, '>',
'<', T1, I1, '>', 0, 0, 0, 0, '<', '/', XRN, '>',
};
int cs, r = 0;
unsigned char *p = (unsigned char *)&buf;
unsigned char *pe = p + sizeof(buf);
unsigned char *eof = NULL;
printf("len=%d\n", len);
%%{
t1 = '08192' @ { printf("t1\n"); };
t2 = '00016' @ { printf("t2\n"); };
t3 = '00008' @ { printf("t3\n"); };
t4 = '00001' @ { printf("t4\n"); };
type = (t1 | t2 | t3 | t4);
info = '020001';
open = '<XRNDATA' type info '>' @ { printf("begin XRNDATA\n"); len = 0; };
len = extend{4} @ { printf("len = %d\n", (int)*p); len = (len*256) + (*p); };
action check {len--}
action bad {printf("BAD\n");}
buffer = (any when check)* %when !check @ { printf("[%d]:%d\n", len, *p); };
close = '</XRNDATA>' @ { printf("end XRNDATA\n"); };
expr = (
open @ lerr(bad)
len
buffer
close
);
main := expr* ;
write init;
write exec;
}%%
return 0;
}

