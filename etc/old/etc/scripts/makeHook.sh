#!/bin/bash
# Helper script to produce project hooks in a hurry.
# written by <jens.o.john@gmail.com>
# of course, it is very simple and lacks regexp support.
# Usage:
# makeHook.sh [hook root directory]
declare -a dirs

for dir in $(find $1 -maxdepth 1 -type d -a -not \( -name '..' -o -name 'hooks' \)); do
    dirs[index++]=$dir
done

echo -e "Specify whom you do NOT want to give a hug (*^_^*)."
echo -e "Type the numbers separated by whitespaces.\n"

for entry in "${!dirs[@]}"; do
    echo -e " [$entry]\t${dirs[$entry]##../}"
done

read -a notDirs

for nogo in ${notDirs[@]}; do
    unset dirs[$nogo]
done

if [[ ${#dirs[@]} -eq 0 ]]; then
    echo "Nothing left to do. Exiting"
    exit 1
fi

while :; do
    echo -e "Whereto shall I save the archive (give a directory) ?"
    read saveTo
    [[ -d $saveTo && -w $saveTo ]] && break
done

while :; do
    echo -e "Please specify a filename."
    read filename
    [[ $filename != "" ]] && break
done

echo "Saving to $saveTo/$filename ..."
tar -cf "$saveTo/$filename" ${dirs[@]} --lzma





