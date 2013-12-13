#!/bin/tcsh
if ( !( -e result/root ) ) then
	mkdir -p result/root
	echo "result/root created "
endif
if ( !( -e result/png ) ) then
	mkdir -p result/png
	echo "result/png created "
endif
set exit=0
while ( $exit == 0 )
	echo "######################################################"
	echo "## Would you like to change some parameters(y/n/q)? ##"
	echo "##            y(Edit), n(Run), q(Quit)              ##"		
	echo "######################################################"
	set op = $<
	if ( $op == q ) then
		exit
	else if ( $op == y ) then
		cd interface
			vi Parameters.h
		cd -	
	else if ( $op == n ) then
		set exit=1
	endif
end
cd src
	echo ""
	echo "====================== Running ========================"
	root pixelCheck.cc+ -l -b -q
cd -

