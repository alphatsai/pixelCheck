#!/bin/tcsh
if ( !( -e result/root ) ) then
	mkdir -p result/root
endif
if ( !( -e result/png ) ) then
	mkdir -p result/png
endif
cd myAna
	root pixelCheck.cc+ -l -b -q
cd -

