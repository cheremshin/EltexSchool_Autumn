#!/bin/bash


function extractValue() {
    local given_value=$1
    echo "${given_value#*=}"
}

function handleAlreadyGivenArgument() {
    local argument_name="$1"
    local already_set_value="$2"
    local argument_value="$3"

    echo "[WARNING] $argument_name already set. Updating."
    echo "Previous value='$already_set_value'. New one value='$argument_value'"
    echo "Try 'main.sh --help' for more information."
    echo
}
