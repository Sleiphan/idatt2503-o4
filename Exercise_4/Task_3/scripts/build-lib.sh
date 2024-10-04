(
  cd ./Exercise_4/Task_3/;
  gcc -c -fPIC a_function.c more_functions.c;
  gcc -shared a_function.o more_functions.o -o libfunctions.so;
  cp libfunctions.so /usr/lib;
  rm a_function.o more_functions.o libfunctions.so;
)