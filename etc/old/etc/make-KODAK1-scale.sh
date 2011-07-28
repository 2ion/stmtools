#!/bin/bash
red=255
green=255
blue=255

until [[ $red = 0 && $green = 0 && blue = 0  ]]; do for index in $(seq 1 256); do 
if [[ $green != 0 &&  $index%2 = 0 ]]; then
   $green=($green-2)*$index
fi 
if [[ $blue != 0 && $index%4 = 0 ]]; then
   $blue=
\
;done;done