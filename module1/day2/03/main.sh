#!/bin/bash


source ./validation
source ./logic

# Definition of main script variables
script_name=$0
process_name=
timeout=300
run_as_daemon=1
has_sudo=$(id -u)

validateArguments "$@"

if [ $run_as_daemon -eq 0 ]; then
    checkAndRestartProcess 1>/dev/null &
else
    checkAndRestartProcess
fi
