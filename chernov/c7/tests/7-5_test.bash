#!bin/bash

gcc -m32 -O2 -std=gnu18 -Wall -Werror -Wno-pointer-sign -Werror=vla -lm up07-5.c

for i in {1902..2037}
do
	./a.out $i
done