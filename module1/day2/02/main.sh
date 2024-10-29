#/!bin/bash


source ./logic
source ./validation

validateArguments $@

path=$1

folders_count=$2
subfolders_count=$3
files_count=$4

folders_name=$5
subfolders_name=$6
files_name=$7


createFoldersAndFiles