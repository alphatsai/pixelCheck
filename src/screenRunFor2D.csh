#!/bin/tcsh
if ( !( -e ../log ) ) then
	mkdir ../log
endif

set where_=`echo $HOST | grep lxplus`
if ( $where_ != "" ) then
	date >! ../log/hostFor2D.log
	echo $HOST >> ../log/hostFor2D.log
	cmsenv
endif
rm -f ../log/drawPlotsFor2D.log
root drawPlotsFor2D.cc+ -l -b -q >&! ../log/drawPlotsFor2D.log
