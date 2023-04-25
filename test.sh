#!/bin/bash

echo "Executing test..."

# move to the "python" folder
cd python

# execute the cryptoCalc.py program with the argument 1.5
result=$(python3 cryptoCalc.py 1.5 | tail -1)

# check the exit status of the cryptoCalc.py program
if [ "$?" -ne 0 ]; then
  echo "Error: cryptoCalc.py failed to execute"
  exit 1
fi

# check if the result is a valid number and is less than or equal to 0
if ! [[ "$result" =~ ^[0-9]+(\.[0-9]+)?$ ]] || (( $(echo "$result <= 0" | bc -l) )); then
  echo "Test failed with result: $result"
  exit 1
else
  echo "Test passed with result: $result"
  exit 0
fi
