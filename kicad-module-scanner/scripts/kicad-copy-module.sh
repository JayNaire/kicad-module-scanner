#!/bin/sh
#Copies a module from one .mod library to a new or existing library
#kicad-copy-module.sh --allowoverwrite=[true|false] --frommodule=modulename --fromfile=filename --tomodule=newmodulename --tofile=filename
# --allowoverwrite
#        if true and the module already exists in outputfile, overwrite it
#        if false (default) and the module already exists in outputfile, do nothing
# --frommodule 
#        the name of a module which exists in --fromfile value
# --tomodule
#        the name of the copied module
#        if not given the copied module name will be the same as the --frommodule value
# --tofile
#        the file to copy the module to
#        if it exists the module will be inserted into it
#        if it doesn't exist, it will be created

function __exit(){ #exit_message exit_status
	echo $1 > /dev/stderr
	exit $2
}

echo "$0 called with $@"
for arg in $*
do
	case $arg in
	--allowoverwrite=*) ALLOWOVERWRITE=${arg#*=}; shift;;
	--frommodule=*) FROMMODULE=${arg#*=}; shift;;
	--fromfile=*) FROMFILE=${arg#*=}; shift;;
	--tomodule=*) TOMODULE=${arg#*=}; shift;;
	--tofile=*) TOFILE=${arg#*=}; shift;;
	*) __exit "$0 : Unknown option: $arg" 1;;
	esac
done
#check options and fix up defaults
if [ ${#ALLOWOVERWRITE} == 0 ]
then
	ALLOWOVERWRITE="false"
fi
if [ ${#FROMMODULE} == 0 ]
then
	__exit "No module name given" 2
fi
if [ ${#FROMFILE} == 0 ]
then
	__exit "No input file name given" 3
fi
if [ ${#TOMODULE} == 0 ]
then
	TOMODULE=$FROMMODULE #copy to same module name
fi
if [ ${#TOFILE} == 0 ]
then
	__exit "No output file name given" 4
fi
TEMPFILE="kicad-temp-mod-file"
EXTRACTMODULESCRIPT=`dirname $0`/kicad-extract-module.awk #kicad-extract-module.awk must reside in same dir as this script
#echo $EXTRACTMODULESCRIPT
#exit
#Grand plan:
#Create a temporary outputfile TEMPFILE
#if $TOFILE exists:
# check if $TOMODULE is there already
# if $TOMODULE is not there already continue
# if it is there already and --allowoverwrite is false then exit

# copy lines to TEMPOUTFILE to just before a line beginning with $EndINDEX
#
#does TOFILE exist?
OVERWRITINGMODULE=0;
MAKINGNEWFILE=0;
if [ -e $TOFILE ]
then
	if grep $TOMODULE $TOFILE > /dev/null #does it contain $FROMMODULE? NOT a good test - suppose $TOMODULE is in a comment field
	then
		echo "$TOFILE contains $TOMODULE";
		if [ $ALLOWOVERWRITE == "true" ]
		then
			OVERWRITINGMODULE=1;
		else
			__exit "Module $TOMODULE already exists in $TOFILE and overwriting is forbidden" 5
		fi
	else
		echo "$TOFILE doesn't contain $TOMODULE";
	fi
else #TOFILE doen't exist
	MAKINGNEWFILE=1;
fi
echo "MAKINGNEWFILE = $MAKINGNEWFILE";
if [ $MAKINGNEWFILE == 1 ]
then
	echo "Making $TEMPFILE"
	echo -e "PCBNEW-LibModule-V1 " `date` "\n\$INDEX\n$TOMODULE\n\$EndINDEX"  > $TEMPFILE
	$EXTRACTMODULESCRIPT --assign frommodule=$FROMMODULE --assign tomodule=$TOMODULE $FROMFILE  >> $TEMPFILE
	echo "\$EndLIBRARY" >> $TEMPFILE
	mv $TEMPFILE $TOFILE
	exit 0
fi	
#if we get here then the output file already exists and we must append or overwrite the copied module	
if [ $OVERWRITINGMODULE == 1 ]
then
	#module already exists in TOFILE - no need to disturb the index, just replace everything between $MODULE and $EndMODULE
	echo "overwriting existing module $TOMODULE in $TOFILE"
	#find lines that module starts and ends on
	startLine=$(awk "{sub(/\r\$/,\"\")}; \$1==\"\$MODULE\" && \$2==\"$FROMMODULE\"{print NR; exit;}" $FROMFILE)
	stopLine=$(awk "{sub(/\r\$/,\"\")}; \$1==\"\$EndMODULE\" && \$2==\"$FROMMODULE\"{print NR; exit;}" $FROMFILE)
	#echo $startLine $((startLine-1)) $stopLine $(($stopLine+1))
	#top, copy module then tail
	head --lines=$((startLine-1)) $FROMFILE > $TEMPFILE
	$EXTRACTMODULESCRIPT --assign frommodule=$FROMMODULE --assign tomodule=$TOMODULE $FROMFILE  >> $TEMPFILE
	tail --lines=+$((stopLine+1)) $FROMFILE  >> $TEMPFILE
else
	#$TOFILE exists and $TOMODULE doesn't already exist in $TOFILE - need to add index entry then add module
	echo "writing new module $TOMODULE in $TOFILE"
	startIndex=$(awk "{sub(/\r\$/,\"\")}; \$1==\"\$INDEX\"{print NR; exit;}" $TOFILE)
	#echo $((startIndex)) $((startIndex - 1))
	head --lines=$((startIndex)) $TOFILE > $TEMPFILE
	echo $TOMODULE >> $TEMPFILE #put new module 1st in index
	#put all other indexes after it (including $endINDEX)
	awk "BEGIN{inIndex=0};{sub(/\r\$/,\"\")}; \$1==\"\$INDEX\"{inIndex=1;next} \$1==\"\$EndINDEX\"{print \$0;exit} inIndex==1 {print \$0}" $TOFILE >> $TEMPFILE
	#copy all lines after $EndINDEX to first $MODULE 
	# 1st MODULE is probably the next line right after $EndIndex so this will probably do nothing - but who knows?
	awk "BEGIN{copying=0};{sub(/\r\$/,\"\")}; \$1==\"\$EndINDEX\"{copying=1;next} \$1==\"\$MODULE\"{exit} copying==1 {print \$0}" $TOFILE >> $TEMPFILE
	#copy module
	$EXTRACTMODULESCRIPT --assign frommodule=$FROMMODULE --assign tomodule=$TOMODULE $FROMFILE  >> $TEMPFILE
	#now copy the other modules
	startOfModules=$(awk "{sub(/\r\$/,\"\")}; \$1==\"\$MODULE\"{print NR; exit;}" $TOFILE)
	tail --lines=+$((startOfModules)) $TOFILE  >> $TEMPFILE
fi
#when we get here $TEMPFILE is complete
if mv -f $TOFILE $TOFILE.bak
then 
	mv $TEMPFILE $TOFILE
else
	__exit "Could not backup $TOFILE" 6
fi
exit 0
	