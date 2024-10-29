#!/bin/bash


source ./reader
source ./logic


process_name=
since=
until=

readConfig "script.conf"

getLogs
