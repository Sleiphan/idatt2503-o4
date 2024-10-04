(
  cd ./Exercise_4/Task_1;
  ./bin/hello 1>/dev/null

  error_code=$?
  echo "Program exited with error code: $error_code"
)