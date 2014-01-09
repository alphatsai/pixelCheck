#!/bin/tcsh
if ( !( -e ../log ) ) then
	mkdir ../log
endif

set where_=`echo $HOST | grep lxplus`
if ( $where_ != "" ) then
	date >! ../log/host.log
	echo $HOST >> ../log/host.log
	cmsenv
endif
rm -f ../log/drawIneffFlux.log
root drawIneffFlux.cc+ -l -b -q >&! ../log/drawIneffFlux.log
date >> ../log/drawIneffFlux.log
