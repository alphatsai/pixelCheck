#!/bin/tcsh
if ( !( -e result/root ) ) then
	mkdir -p result/root
	echo "result/root created "
endif
if ( !( -e result/png ) ) then
	mkdir -p result/png
	echo "result/png created "
endif
cd myAna
	root pixelCheck.cc+ -l -b -q
cd -

