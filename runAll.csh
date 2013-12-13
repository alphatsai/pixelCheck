#!/bin/tcsh
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
	echo "##                      Part 1/2                      ##"
	echo "##      Store plots in .root files '"'result/root'"'      ##"
	echo "## Would you like to change some parameters(y/n/q/p)? ##"
	echo "##         y(Edit), n(Run), q(Quit), p(Skip)          ##"		
	echo "########################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == y ) then
		cd interface
			vi Parameters.h
		cd -	
	else if ( $op == n ) then
		cd src
			echo ""
			echo "                For src/pixelCheck.cc                  "
			echo "====================== Running ========================"
			root pixelCheck.cc+ -l -b -q
			echo "====================== The End ========================"
		cd -
		set exit=1
	else if ( $op == p ) then
		set exit=1
	endif
end

set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "##                     Part 2/2                     ##"
	echo "##       Create some pdf plots '"'result/plots'"'       ##"
	echo "##      NOTE: Please make sure you can use root     ##"
	echo "##                                                  ##"
	echo "##   Would you like to use screen to run the macro  ##"
	echo "##         y(yes), n(run directly), q(Quit)         ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == y ) then
		echo ""
		echo "                 For src/drawPlots.cc                  "
		echo "========== screen job's name is createPdf ============="
		echo "================= log files in ./log =================="
		cd src
			screen -dmS createPdf ./screenRun.csh
		cd -
		screen -list
		echo "'"'screen -list'"' to check"
		echo "Host: $HOST"
		set exit=1
	else if ( $op == n ) then
		cd src
			echo ""
			echo "                 For src/drawPlots.cc                  "
			echo "====================== Running ========================"
			root drawPlots.cc+ -l -b -q	
			echo "====================== The End ========================"
			set exit=1
		cd -
	endif
end
