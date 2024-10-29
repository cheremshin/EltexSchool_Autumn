#!/bin/bash

source ./validation
source ./logic


input_file=
output_file=

validateArguments "$@"
translateFile