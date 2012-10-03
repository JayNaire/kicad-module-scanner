#!/bin/awk -f
#extract-module.awk --assign frommodule=frommodulename --assign tomodule=tomodulename fromfilename  
#Extracts a footprint named frommodulename in a file called fromfilename
#  to   a footprint named tomodulename (or frommodulename if tomodule is not given)
#  output is always to stdout
# WARNING: Does not try to modify file paths (in SHAPE3D sections for example).
#Example usage:kicad-extract-module.awk --assign frommodule=CP_5x6mm --assign tomodule=robbie capacitors.mod

BEGIN{
	inModule=0;
	inIndex=0;
	outputText="";
	errorOccurred=0;
	if (frommodule == ""){
		print  "kicad-extract-module.awk: Error: No module name given." > "/dev/stderr";
		errorOccurred=1;
		exit 1;
	}
	#if (tofile == "") tofile = "/dev/stdout";
	if (tomodule == "") tomodule = frommodule;
}
#this converts DOS line endings (CR,LF) to Unix line endings (LF) 
{sub(/\r$/,"")};

($1=="$MODULE" && $2==frommodule){
	inModule=1;
	outputText = $1 " " tomodule"\n";
	next;
}
{
	if (inModule==1){ 
		if ($1=="$EndMODULE") {
			outputText = outputText $1 " " tomodule;
			inModule=0;
			exit 0;
		}
		else{
			outputText = outputText $0 "\n";
		}
	}
}
END{
	if (! errorOccurred){
		print outputText;
	}
}