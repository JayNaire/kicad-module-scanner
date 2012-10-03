#!/bin/sh
#this is a driver script for kicad-module-scanner.awk
#the arguments are as follows:
# kicad-module-scanner --awkscript=theawkscript --module=[all | modulename] --outputxml=[on|off] --postscript=[off | on]  --scale=n --showpinnumbers=[off | on] --outfile=outputpath --outputmode=[append | overwrite] --inputmode=[file | folder] path [path]...

# --awkscript is the name of the worker (g)awk script eg:kicad-module-scanner.awk

# --module (or -mod) is one of:
# all		(default) produce output for all modules
# somename	produce output only for the module called somename
# corresponding awk argument: --assign module=modulename|all

# --outputxml (or -ox) is one of:
# on		(default) clamp xml tags around ouput (to produce database file)
# off		no xml tags (mainly for producing postscript for direct presentation)
# corresponding awk argument: --assign outputxml=on|off

# --postscript (or -p) can be 
# off		do not include postscript in output data
# on		(default) include postscript in output data
# corresponding awk argument: --assign postscript=off|on

# --scale (or -sc) can be 
# a number n between 0.5 and 4 (default n = 1)
# scales the footprint (but not the text) by n*100% in postscript output
# corresponding awk argument: --assign scale=n

# --showpinnumbers (or -sp) can be (only used if --postscript=on)
# off		do not show pin numbers
# on		(default) show pin numbers in postscript output
# corresponding awk argument: --assign showpinnumbers=off|on

# --outfile specifies the file to which all output is written
# if --outfile (or -o) is missing all output is written to stdout

# --outputmode (or -om) is one of:
# overwrite		(default) the output will overwrite the output file
# append		the output will be appended to the output file
# corresponding awk argument:none

# --inputmode (or -im) is one of:
# file        (default) scan one or more files whose path(s) is/are given in path
# folder	  scan one or more folders (whose path(s) is/are given in path) for files with a .mod extension
# corresponding awk argument:none

echo "$0 called with $@"
#sleep 5
#exit

#defaults - export because some variable are used in () subshells
export AWK_SCRIPT="kicad-module-scanner.awk"
export INPUT_MODE="file"
export OUTPUT_MODE="overwrite"
export OUTFILE="/dev/stdout"
#default args to pass to awk script
MODULE="all"
POSTSCRIPT="on"
SHOWPINNUMBERS="on"
SCALE="1"
OUTPUTXML="on"

for i in $*   # Parse command line args.
do
	case $i in
	--awkscript=*|-a=*) export AWK_SCRIPT=${i#*=}; shift;;
	--module=*|-mod=*) MODULE=${i#*=}; shift;;
	--outputxml=*|-ox=*) OUTPUTXML=${i#*=}; shift;;
	--postscript=*|-p=*) POSTSCRIPT=${i#*=}; shift;;
	--showpinnumbers=*|-sp=*) SHOWPINNUMBERS=${i#*=}; shift;;
	--scale=*|-sc=*) SCALE=${i#*=}; shift;;
	--outfile=*|-o=*) export OUTFILE=${i#*=}; shift;;
	--outputmode=*|-om=*) export OUTPUT_MODE=${i#*=}; shift;;
	--inputmode=*|-im=*) export INPUT_MODE=${i#*=}; shift;;
	--) shift; break;;
	esac
done


# when we get here, the remaining args ($@) are folders (if $INPUT_MODE == folder) or files (if $INPUT_MODE == file)
if [ $INPUT_MODE != "file" -a  $INPUT_MODE != "folder" ]
then
	echo "Bad inputmode: $INPUT_MODE. inputmode must be either 'file' or 'folder'. $0 Exiting.";
	exit 1;
fi
if [ $OUTPUT_MODE != "append" -a  $OUTPUT_MODE != "overwrite" ]
then
	echo "Bad outputmode: $OUTPUT_MODE. outputmode must be either 'append' or 'overwrite'. $0 Exiting.";
	exit 2;
fi
if [ $POSTSCRIPT != "on" -a  $POSTSCRIPT != "off" ]
then
	echo "Bad postscript option: $POSTSCRIPT. postscript must be either 'on' or 'off'. $0 Exiting.";
	exit 3;
fi
if [ $SHOWPINNUMBERS != "on" -a  $SHOWPINNUMBERS != "off" ]
then
	echo "Bad showpinnumbers option: $SHOWPINNUMBERS. showpinnumbers must be either 'on' or 'off'. $0 Exiting.";
	exit 4;
fi
if [ $SCALE -ne $SCALE 2> /dev/null ]
then
	echo "Bad scale option: $SCALE. scale must be number. $0 Exiting.";
	exit 5;
fi
if [ $SCALE -gt 4 ] || [ $SCALE -lt 0.5 ]
then
	echo "Bad scale option: $SCALE. scale must be number between 0.5 and 4. $0 Exiting.";
	exit 6;
fi
	
if [ $OUTPUTXML != "on" -a  $OUTPUTXML != "off" ]
then
	echo "Bad OUTPUTXML option: $OUTPUTXML. outputxml must be either 'on' or 'off'. $0 Exiting.";
	exit 7;
fi
if [[ $MODULE != "all" ]]
then
	if [[ ${#MODULE} == 0 ]]
	then
		echo "Bad module option:  module must be either 'all' or a module name. $0 Exiting.";
		exit 8;
	fi
fi
#echo ${#MODULE}
#these "--assign name=value" options get handed in to the awk program directly; they don't appear as filename arguments
AWK_ASSIGN_MODULE="--assign module=$MODULE"
AWK_ASSIGN_POSTSCRIPT="--assign postscript=$POSTSCRIPT"
AWK_ASSIGN_SHOWPINNUMBERS="--assign showpinnumbers=$SHOWPINNUMBERS"
AWK_ASSIGN_SCALE="--assign scale=$SCALE"
AWK_ASSIGN_OUTPUTXML="--assign outputxml=$OUTPUTXML"

export AWK_ASSIGN_OPTIONS="$AWK_ASSIGN_MODULE $AWK_ASSIGN_POSTSCRIPT $AWK_ASSIGN_SHOWPINNUMBERS $AWK_ASSIGN_SCALE $AWK_ASSIGN_OUTPUTXML"

echo "$0:"
echo "OUTFILE is $OUTFILE"
echo "INPUT_MODE is $INPUT_MODE"
echo "OUTPUT_MODE is $OUTPUT_MODE"
echo "POSTSCRIPT is $POSTSCRIPT"
echo "SHOWPINNUMBERS is $SHOWPINNUMBERS"
echo "SCALE is $SCALE"
echo "MODULE is $MODULE"
echo "OUTPUTXML is $OUTPUTXML"

echo I will run: ${AWK_SCRIPT} $AWK_ASSIGN_OPTIONS $@
#exit 0
#if [ $OUTPUTXML == "on" ]
#then
#	echo "ON"
#else
#	echo "OFF"
#fi

if [ $OUTPUT_MODE == "overwrite" ]
then
	echo "in overwrite and OUTPUTXML is $OUTPUTXML"
	if [ $OUTPUTXML == "on" ]
	then
		echo -e "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<kms version=\"0.1\">" > "$OUTFILE"
	else
		if [ -e $OUTFILE ]
		then
			#rm $OUTFILE <-no! confuses okular
			cat /dev/null > $OUTFILE
		fi
	fi
else
	#append mode - we have to rip out the last line eg: </kms> from existing file, write new modules, then put it back
	if [ -e "$OUTFILE" ]
	then
		cp $OUTFILE "$OUTFILE.save"
		#numlines=`wc -l "$OUTFILE.save"`
		#echo $numlines
		#echo $(numlines-1)
		head --lines=-1 "$OUTFILE.save" > "$OUTFILE" #copy all but last line
	fi
fi
#when we get here we only ever need to append to $OUTFILE
if [ $INPUT_MODE == "file" ] 
then
    #echo "File mode"
	(for file in $@ #will fail if paths include spaces
	do
		"$AWK_SCRIPT" $AWK_ASSIGN_OPTIONS "$file"
	done) >> "$OUTFILE"
else
	#echo "Folder mode"
	(for folder in $@
	do
		for file in `ls $folder/*.mod`
		do
			"$AWK_SCRIPT" $AWK_ASSIGN_OPTIONS "$file"
		done
	done) >> "$OUTFILE"
fi
if [ $OUTPUTXML == "on" ]
then
	echo "</kms>" >> "$OUTFILE"
fi
if [ -e "$OUTFILE.save" ]
then
	rm "$OUTFILE.save"
fi