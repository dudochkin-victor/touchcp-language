#! /bin/bash

set -e

if [ $(dirname "$0") != "." ]; then
    echo "Please run me from my templates dir!"
    exit 1
fi

if [ "x$1" = "x" ]; then
    echo "Usage: $0 MyClass"
    echo "Generates a dir under ../ut_myclass with initial content for start"
    exit 0
fi

ClassName="$1"
classname=$(echo $ClassName | tr '[:upper:]' '[:lower:]')
CLASSNAME=$(echo $ClassName | tr '[:lower:]' '[:upper:]')

ut_classname="ut_$classname"
mkdir -p "../$ut_classname"
if ls ../$ut_classname/* &>/dev/null; then
    echo "FAILED: ../$ut_classname is not empty"
    exit 1
fi

for file in *.cpp *.h *.pro; do
    newName=$(echo "$file" | sed "s/template/$classname/g")
    newPath="../$ut_classname/$newName"
    echo "Creating $newPath"
    cat "$file" |
    sed -e "s/template/$classname/g" \
        -e "s/Template/$ClassName/g" \
        -e "s/TEMPLATE/$CLASSNAME/g" \
        >"$newPath"
done


