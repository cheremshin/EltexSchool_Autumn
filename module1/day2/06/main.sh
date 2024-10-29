#!/bin/bash

source ./reader
source ./validation
source ./logic


source_dir=
destination_dir=
archive_name=
period=
time=


readParameters
validateParameters
createBackup
