#!/bin/bash

GPP='g++'
DEL='rm -f'
WRN='-Wall -Wextra'

$GPP -c include/*.cpp $WRN
$GPP main.cpp *.o -o salesman $WRN
$DEL *.o
