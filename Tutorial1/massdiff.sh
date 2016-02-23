#!/bin/bash
f="$1"

for file in ./*; 
do 
DIFF=$(diff $f $file)

if [ "$DIFF" != "" ]; then
	diff $f $file > output.txt
	echo "Appending to output.txt file"
else
	echo "$f and $file are the same."
fi
done
