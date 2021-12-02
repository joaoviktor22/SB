Codigo do montador feito no Sistema Operacional Windows.
Feito no aplicativo CLion

Compilar no Windows:

x86_64-w64-mingw32-g++ montador.cpp -o montador
x86_64-w64-mingw32-g++ ligador.cpp -o ligador
x86_64-w64-mingw32-g++ simulador.cpp -o simulador
.\montador myprogram.asm myprogram2.asm
.\ligador myprogram.calvo myprogram2.calvo
.\simulador myprogram.obj

Considere myprogram o nome do primeiro programa(ou unico) enquanto que myprogram2 o nome do segundo programa.

Codigo da calculadora feita em Linux.

Compilar no Linux:

nasm -f elf calculadora.asm
ld -m elf_i386 -o calculadora calculadora.o
./calculadora

