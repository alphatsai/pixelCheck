#!/bin/tcsh
if ( !( -e ../log ) ) then
	mkdir ../log
endif

set where_=`echo $HOST | grep lxplus`
if ( $where_ != "" ) then
	date >! ../log/hostPdf.log
	echo $HOST >> ../log/hostPdf.log
	cmsenv
endif
rm -f ../log/drawPlotsPdf.log
root drawPlotsPdf.cc+ -l -b -q >&! ../log/drawPlotsPdf.log
date >> ../log/drawPlotsPdf.log
