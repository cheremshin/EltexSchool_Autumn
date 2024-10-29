#!/bin/bash


source ./validation
source ./logic


process_name=
since=
until=

validateArguments "$@"

getLogs
