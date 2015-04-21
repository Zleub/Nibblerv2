#!/bin/sh
export DYLD_LIBRARY_PATH=ext/SFML-2.2/lib

if [[ ! -e bin ]]; then
	mkdir bin
fi

make && ./bin/Nibbler $*
