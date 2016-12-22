
echo Executing Pre Build commands ...

echo Done
gcc -c -masm=intel -o *.S
gcc -c -masm=intel -o *.c
ld *.o -Tldscript -nostdlib
