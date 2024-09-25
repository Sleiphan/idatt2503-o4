(
  cd ./Exercise_4/Task_1;
  mkdir -p bin;
  nasm -f elf64 hello.s;
  ld hello.o -o bin/hello;
  rm hello.o;
)