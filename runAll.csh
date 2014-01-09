#!/bin/tcsh
set where_=`echo $HOST | grep lxplus`
if ( $where_ != "" ) then
	cmsenv
endif
if ( !( -e result/root ) ) then
	mkdir -p result/root
	echo "result/root created "
endif
if ( !( -e result/plots ) ) then
	mkdir -p result/plots
	echo "result/plots created "
endif
set exit=0
while ( $exit == 0 )
	echo "########################################################"
	echo "##                      Part 1/5                      ##"
	echo "##      Store plots in .root files '"'result/root'"'      ##"
	echo "## Would you like to change some parameters(e/r/q/s)? ##"
	echo "##         e(Edit), r(Run), q(Quit), s(Skip)          ##"		
	echo "########################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == e ) then
		cd interface
			vi Parameters.h
		cd -	
	else if ( $op == r ) then
		cd src
			echo ""
			echo "                For src/pixelCheck.cc                  "
			echo "====================== Running ========================"
			root pixelCheck.cc+ -l -b -q
			echo "====================== The End ========================"
			echo ""
			echo "              For src/saveFitParameter.cc                  "
			echo "====================== Running ========================"
			root saveFitParameter.cc+ -l -b -q
			echo "====================== The End ========================"
		cd -
		set exit=1
	else if ( $op == s ) then
		set exit=1
	endif
end

set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "##                     Part 2/5                     ##"
	echo "##        Create some 2D plots '"'result/plots'"'       ##"
	echo "##      NOTE: Please make sure you can use root     ##"
	echo "##                                                  ##"
	echo "##   Would you like to use screen to run the macro  ##"
	echo "##      r(Run screen), n(No), q(Quit), s(Skip)      ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == r ) then
		echo ""
		echo "                For src/drawPlotsFor2D.cc                  "
		echo "========== screen job's name is 2D_Plots =============="
		echo "================= log files in ./log =================="
		cd src
			screen -dmS 2D_Plots ./screenRunFor2D.csh
		cd -
		screen -list
		echo "'"'screen -list'"' to check"
		echo "Host: $HOST, record in log/host.log"
		set exit=1
	else if ( $op == n ) then
		cd src
			echo ""
			echo "                For src/drawPlotsFor2D.cc                  "
			echo "====================== Running ========================"
			root drawPlotsFor2D.cc+ -l -b -q	
			echo "====================== The End ========================"
			set exit=1
		cd -
	else if ( $op == s ) then
		set exit=1
	endif
end
set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "##                     Part 3/5                     ##"
	echo "##       Create some plots for ineff. vs flux       ##"
	echo "##      NOTE: Please make sure you can use root     ##"
	echo "##                                                  ##"
	echo "##   Would you like to use screen to run the macro  ##"
	echo "##      r(Run screen), n(No), q(Quit), s(Skip)      ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == r ) then
		echo ""
		echo "                 For src/drawPlots.cc                  "
		echo "========== screen job's name is createPdf ============="
		echo "================= log files in ./log =================="
		cd src
			screen -dmS createIneffFlux ./screenRunIff.csh
		cd -
		screen -list
		echo "'"'screen -list'"' to check"
		echo "Host: $HOST, record in log/host.log"
		set exit=1
	else if ( $op == n ) then
		cd src
			echo ""
			echo "                For src/drawPlots.cc                  "
			echo "====================== Running ========================"
			root src/drawIneffFlux.cc+ -l -b -q	
			echo "====================== The End ========================"
			set exit=1
		cd -
	else if ( $op == s ) then
		set exit=1
	endif
end

set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "##                     Part 4/5                     ##"
	echo "##       Create some PNG plots '"'result/plots'"'       ##"
	echo "##      NOTE: Please make sure you can use root     ##"
	echo "##                                                  ##"
	echo "##   Would you like to use screen to run the macro  ##"
	echo "##      r(Run screen), n(No), q(Quit), s(Skip)      ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == r ) then
		echo ""
		echo "                 For src/drawPlots.cc                  "
		echo "========== screen job's name is createPdf ============="
		echo "================= log files in ./log =================="
		cd src
			screen -dmS createPng ./screenRun.csh
		cd -
		screen -list
		echo "'"'screen -list'"' to check"
		echo "Host: $HOST, record in log/host.log"
		set exit=1
	else if ( $op == n ) then
		cd src
			echo ""
			echo "                For src/drawPlots.cc                  "
			echo "====================== Running ========================"
			root drawPlots.cc+ -l -b -q	
			echo "====================== The End ========================"
			set exit=1
		cd -
	else if ( $op == s ) then
		set exit=1
	endif
end
set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "##                     Part 5/5                     ##"
	echo "##       Create some PDF plots '"'result/plots'"'       ##"
	echo "##      NOTE: Please make sure you can use root     ##"
	echo "##                                                  ##"
	echo "##   Would you like to use screen to run the macro  ##"
	echo "##      r(Run screen), n(No), q(Quit), s(Skip)      ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == r ) then
		echo ""
		echo "               For src/drawPlotsPdf.cc                  "
		echo "========== screen job's name is createPdf ============="
		echo "================= log files in ./log =================="
		cd src
			screen -dmS createPdf ./screenRunPdf.csh
		cd -
		screen -list
		echo "'"'screen -list'"' to check"
		echo "Host: $HOST, record in log/host.log"
		set exit=1
	else if ( $op == n ) then
		cd src
			echo ""
			echo "              For src/drawPlotsPdf.cc                  "
			echo "====================== Running ========================"
			root drawPlotsPdf.cc+ -l -b -q	
			echo "====================== The End ========================"
			set exit=1
		cd -
	else if ( $op == s ) then
		set exit=1
	endif
end
