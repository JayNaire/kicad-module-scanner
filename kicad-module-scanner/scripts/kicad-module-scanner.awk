#!/bin/gawk -f
#to use this script: mode=xml|plain is now outputxml=off|on
#kicad-module-scanner.awk --assign scale=[1-10] --assign showpinnumbers=on|off --assign module=modulename|all --assign outputxml=on|off --assign postscript=off|on file
# scale: 1 = 100% 1:1
#        .5= 50%  half size
#        2 = 200% double size etc.
# note there are several #" in this script - they're just to make kate highlighting correct when using regexes
BEGIN{
	#print "Starting module= " module ", outputxml = " outputxml ", mode = " mode ", postscript= " postscript
	ppi = 72;
	pinFontSize = 4;
	widthOfChar = (pinFontSize/2) * ppi; #guess - fontsize / 2??
    OFS="|"
    numPins=0;
    inModule=0;
    inPad=0;
	if (scale == 0) scale = 1; #HERE Put scale into app
#	kicad_scale = .0001;
	kicad_scale = scale/10000;
    preamble=("\
%!\n\
/red { 1 0 0 setrgbcolor } bind def \n\
/blue { 0 0 1 setrgbcolor } bind def \n\
/green { 0 1 0 setrgbcolor } bind def \n\
/darkgreen { 0 .5 0 setrgbcolor } bind def \n\
/black { 0 0 0 setrgbcolor } bind def \n\
/yellow { 1 1 0 setrgbcolor } bind def \n\
/pointsub { 3 2 roll sub 3 1 roll exch sub exch } def\n\
/distance { pointsub dup mul exch dup mul add sqrt } def\n\
/ppi " ppi " def\n\
/kicad_scale " kicad_scale " def %kicad units are in one tenth of a mil\n\
/inch {ppi mul} bind def      % Convert inches to points (1/72 inch)\n\
/mm {inch 25 div} bind def\n\
/mil {inch 1000 div} bind def\n\
/tenthmil{mil 10 div} bind def\n\
/gs { gsave } bind def\n\
/gr { grestore } bind def\n\
/theFont /Times-Roman findfont 8 scalefont def %use in non-kicad space\n\
/theKicadFont /Courier findfont 8 scalefont def %use for pin details\n\
/thePinFont /Courier findfont " pinFontSize " 1 kicad_scale ppi mul div mul scalefont def %use for pins\n\
/T { %text x y  draw text at x y\n\
    theFont setfont\n\
    moveto\n\
    show\n\
} def\n\
/kicadT { %text x y  draw text at x y\n\
    theKicadFont setfont\n\
    moveto\n\
    show\n\
} def\n\
/DS {\n\
    newpath\n\
    pop %ignore Layer\n\
    setlinewidth\n\
    moveto\n\
    lineto\n\
    stroke\n\
    %ignore other\n\
} bind def\n\
/DC {\n\
    newpath\n\
    pop %ignore Layer\n\
    setlinewidth %width\n\
    0 360 arc %Xcentre Ycentre radius\n\
    closepath\n\
    stroke\n\
}  def\n\
/DA {\n\
    newpath\n\
    pop  %ignore Layer\n\
    setlinewidth %width\n\
    arc %Xcentre Ycentre radius startAngle endAngle \n\
    stroke\n\
} bind  def\n\
105 mm 148 mm translate %set origin in centre of A4 page\n\
gs %startKicadSpace\n\
1 setlinecap %rounded line ends\n\
kicad_scale ppi mul kicad_scale ppi mul scale\n\
1 -1 scale %invert Y axis\n\
%end preamble");
    postamble="showpage\n"
    if (outputxml == "on" ){ #mode="xml"
#	print "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
#<!DOCTYPE kms>\n\
#<kms version=\"0.1\">";
	#print "<kms version=\"0.1\">"; is now done by kicad-module-scanner.sh
		if (postscript == "on"){
			preamble ="<module>\n<postscript>" preamble ;
			postamble = postamble "</postscript>";
		}
		else{
			preamble ="<module><postscript>"
			postamble = "</postscript>";
		}
    }
    filename = ARGV[1];
    minBBoxX = 0;
    maxBBoxX = 0;
    minBBoxY = 0;
    maxBBoxY = 0;
}
END{
    #if (outputxml == "on") print "</kms>"; is now done by kicad-module-scanner.sh
}

function min(x,y){
	return x < y ? x : y;
}

function trim(s) {
	# remove leading and trainling whitespaces
	sub(/^[[:blank:]]+/, "", s);
	sub(/[[:blank:]]+$/, "", s);
	return s
}

function setBoundingX(x){ #to keep track of the bounds of everything we draw (except pin numbers)
    if (x < minBBoxX) minBBoxX = x;
    if (x > maxBBoxX) maxBBoxX = x;
}

function setBoundingY(y){ #be very careful with scaling 1,-1, minY is the top, maxY is the bottom
    if (y < minBBoxY) minBBoxY = y;
    if (y > maxBBoxY) maxBBoxY = y;
}

function circleHere(r, colour){ #draw a "colour" circle radius r at current point (colour must be a /def in preamble) - for debugging only
    retval="%startcircleHere\n\
gs\n\
" colour "\n\
20 setlinewidth\n\
currentpoint " r " 0 360 arc\n\
closepath\n\
stroke\n\
gr\n\
%endcircleHere\n";
    return retval;
}

function redCircle(x,y,r){ #for debugging only
    retval="%startRedCircle\n\
gs\n\
red\n\
newpath\n"\
x " " y " " r " 0 360 arc\n\
closepath\n\
stroke\n\
gr\n\
%endRedCircle\n";
    return retval;
}
function nextLine(){
    return currentLine++ * textOffset;
}

function fixIllegalXmlChars(str){ 
	s = str;
	gsub(/&/,"\\&amp;",s);
	gsub(/</,"\\&lt;",s);
	gsub(/>/,"\\&gt;",s);
	gsub(/\"/,"\\&quot;",s); #"
	return s;
}
function abs(x){
	return x>0?x:0-x;
}
function printPinNumberC(){
	#print pin numbers for padShapes (C)ircular
	print "%pin numbering (C) starts here"
	#move to the centre of the pad
	print padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " moveto";
	yOffset = (pinFontSize / 4) * ppi; # 2 * ppi
	xOffset = (pinFontSize / 4)  * ppi; # 2 * ppi
	xOffsetLeft = (pinFontSize / 4) * 3 * ppi;#6 * ppi
	xOffsetRight = (pinFontSize / 4) * ppi; #2 * ppi
	yOffsetTop = (pinFontSize / 4) * ppi;#2 * ppi;
	
	padX2Right = abs(maxBBoxX - padCentreX);
	padX2Left = abs(minBBoxX - padCentreX);
	padY2Top = abs(minBBoxY - padCentreY); #scaling 1,-1 minY is top
	print "%padY2Top = abs(" maxBBoxY " - " padCentreY ") = " padY2Top;
	padY2Bottom = abs(maxBBoxY - padCentreY); #scaling 1,-1 minY is top
	print "%padY2Bottom = abs(" minBBoxY " - " padCentreY ")= " padY2Bottom;
	rotateText = 0;
	#which side of bounding box is the pad closest to?
	theMin = min(padX2Right, padX2Left);
	theMin = min(theMin, padY2Top);
	theMin = min(theMin, padY2Bottom);
	numChars = length(padName);
	if (theMin == padX2Right){
		print "%Pad is on the right";
		print padRadius + (numChars * xOffsetRight) " " yOffset " rmoveto"
	}
	else if (theMin == padX2Left){
		print "%Pad is on the left";
		print -1 * ( padRadius + (numChars * xOffsetLeft) ) " " yOffset " rmoveto"
	} 
	else if (theMin == padY2Top){
		print "%Pad is at the top";
		print xOffset " " 0 - ( padRadius + (yOffsetTop) ) " rmoveto"
		rotateText = 1;
	} 
	else if (theMin == padY2Bottom){
		print "%Pad is at the bottom";
		print xOffset " " padRadius + ((1 + numChars) * widthOfChar) " rmoveto"
		rotateText = 1;
	} 
	else {
		print "%Pad is at the ???";
	} 
	print "gs blue"
	print "1 -1 scale"
	if (rotateText == 1) print "90 rotate";
	print "(" padName ") show"
	print "gr"
	print "%pin numbering (C) ends here"
}

function printPinNumber(){
	#print pin numbers for padShapes (R)ectangular, (O)val & (T)rapezoidal
	if (padSizeX > padSizeY){
		theLength = padSizeX;
		theWidth = padSizeY;
		drawLineInX = 1;
	}
	else{
		theLength = padSizeY;
		theWidth = padSizeX;
		drawLineInX = 0;
	}
	print "%pin numbering starts here"
	if ((drawLineInX == 1 && padOrientation == 0) || (drawLineInX == 0 && padOrientation != 0)){ #padOrientation != 0 well it could be anything and will go wrong for pads at some odd angle
		padIsHorizontal = 1;
		print "%pad is  horizontal"
	}
	else{
		padIsHorizontal = 0;
		print "%pad is vertical"
	}
	#move to the centre of the pad
	print padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " moveto";
	#print circleHere(200,"yellow"); #debug only
	yOffset = (pinFontSize / 4) * ppi; 
	xOffset = (pinFontSize / 4) * ppi; 
#	xOffsetLeft = 4 * ppi; #fix because I don't know the width of a char
	xOffsetRight = (pinFontSize / 4) * ppi;
	yOffsetTop = (pinFontSize / 4) * ppi;
#	yOffsetBottom = 4 * ppi; #fix because I don't know the width of a char
	if (padShape == "O"){
		theRadius = theWidth/2;
	}
	else{
		theRadius = 0;
	}
#	numChars = length(numPins);
	numChars = length(padName);
	if (padIsHorizontal == 1 ){ #pad is horizontal
		padX2Right = abs(maxBBoxX - padCentreX);
		padX2Left = abs(minBBoxX - padCentreX);
		print "%numChars: " numChars " pad2Right: " padX2Right " pad2Left: " padX2Left
		if (padX2Right < padX2Left){ #pad is closer to the right
			print "%pad is on the right"
			print (theLength/2) + (theRadius) + xOffsetRight " " yOffset " rmoveto"
		}
		else{ #pad is on the left
			print "%pad is on the left"
			#print -1 * ( (theLength/2) + (theRadius) + (numChars * xOffsetLeft) ) " " yOffset " rmoveto"
			print 0 - ( (theLength/2) + (theRadius) + ((1 + numChars) * widthOfChar) ) " " yOffset " rmoveto"
		}
		#print circleHere(200,"blue"); #debug only
	}
	else{ #pad is vertical
		padY2Top = abs(maxBBoxY - padCentreY);
		padY2Bottom = abs(minBBoxY - padCentreY);
		print "%numChars: " numChars " padY2Top: " padY2Top " padY2Bottom: " padY2Bottom
		if (padY2Bottom < padY2Top){ #pad is closer to the top (scaled 1,-1)
#			padIsAtTheTop = 1;
			print "%pad is at the top"
			print xOffset " " 0 - ((theLength/2) + (theRadius) + yOffsetTop) " rmoveto" 
		}
		else{
			print "%pad is at the bottom"
			#print xOffset " " (theLength/2) + (theRadius) + (numChars * yOffsetBottom) " rmoveto" 
			print xOffset " " (theLength/2) + (theRadius) + ((1 + numChars) * widthOfChar) " rmoveto" 
		}
		#print circleHere(200,"blue"); #debug only
	}

	print "gs blue"
	print "1 -1 scale"
	if (padIsHorizontal == 0) print "90 rotate";
#	print "(" numPins ") show"
	print "(" padName ") show"
	print "gr"
	print "%pin numbering ends here"
}

function printDetails(){
    #minBBoxX, minBBoxY etc. are relative to the module's origin in kicad space
    #as we are going to add text in postscript space (to avoid inverted text & other scaling problems)
    #we need to convert them to postscript space: x x coords are just divided by 10000, y coords by -10000
#    blx = minBBoxX*72/10000; #bl = bottom left of bounding box, tr = top right
#    bly = ((3*4*72)+maxBBoxY)*72/-10000; # no scaling in effect now so y axis is inverted!!
#    trx = maxBBoxX*72/10000;
    blx = minBBoxX * ppi * kicad_scale; #bl = bottom left of bounding box, tr = top right
    bly = 0 - (((3*4*ppi)+maxBBoxY) * ppi * kicad_scale); # no scaling in effect now so y axis is inverted!!
    trx = maxBBoxX * ppi * kicad_scale;
    #try = minBBoxY*72/-10000;
    #make a feeble stab at centralising text
    blx *= 2;
    #if module is rotated add a bit of clearance to bly before starting text
    if (modRotation != 0) bly -= (trx-blx)/2;
#    textOffset = 11; #11pt linespacing for 10pt text
    textOffset = 9; #9pt linespacing for 8pt text
    currentLine = 1;
#    modx = (maxBBoxX - minBBoxX)/10000;
#    mody = (maxBBoxY - minBBoxY)/10000;
    modx = (maxBBoxX - minBBoxX) * kicad_scale;
    mody = (maxBBoxY - minBBoxY) * kicad_scale;
    print "(Scale: " scale * 100 "%) " blx " " bly - nextLine() " T"; #place refdes 11 pts below bbox
    print "(Name: " modName ") " blx " " bly - nextLine() " T"; #place refdes 11 pts below bbox
    print "(Refdes: " modRefDes ") " blx " " bly - nextLine() " T"; #place refdes 11 pts below bbox
    print "(File: " filename ") " blx " " bly - nextLine() " T"; #place refdes 11 pts below bbox
    print "(Footprint XxY: " modx "\" x " mody  "\" (" modx*25.4 "mm x " mody*25.4 "mm))" blx " " bly - nextLine() " T";  
    if (numPins>1){
		dX = arrPinCentreX[1] - arrPinCentreX[2]; dX = dX < 0 ? (-1 * dX) : dX;
		dY = arrPinCentreY[1] - arrPinCentreY[2]; dY = dY < 0 ? (-1 * dY) : dY;
		print "(Pin Pitch	mil	(mm))" blx " " bly - nextLine() " kicadT";
		if (dX > 0){
			print "(P1-P2\tdX	" (dX/10) "	(" ((dX*2.54)/1000 ) ")) " blx " " bly - nextLine() " kicadT";  
		}
		if (dY > 0){
			print "(P1-P2 dY	" (dY/10) "	(" ((dY*2.54)/1000 ) ")) " blx " " bly - nextLine() " kicadT";    
		}
		if (numPins > 2){
			dX = arrPinCentreX[1] - arrPinCentreX[numPins]; dX = dX < 0 ? (-1 * dX) : dX;
			dY = arrPinCentreY[1] - arrPinCentreY[numPins]; dY = dY < 0 ? (-1 * dY) : dY;
			if (dX > 0){
				print "(P1-P" numPins " dX	" (dX/10) "	(" ((dX*2.54)/1000 ) ")) " blx " " bly - nextLine() " kicadT";
			}
			if (dY > 0){
				print "(P1-P" numPins " dY	" (dY/10) "	(" ((dY*2.54)/1000 ) ")) " blx " " bly - nextLine() " kicadT";
			}
		}
		if (pin1Found == 0){
			# if there isn't a pin named "1", dish out a list of pin names
			for (i=1; i<=numPins; i++){
				print "(Pin #" i " - " arrPinName[i] ") " blx " " bly - nextLine() " kicadT";
			}
		}
    }
}

# END OF FUNCTIONS

#this converts DOS line endings (CR,LF) to Unix line endings (LF) 
{sub(/\r$/,"")};
$1=="$MODULE" {
    if (module == "all" || $2 == module){
		print preamble;
		if (postscript=="on") print "%"$2"\n";
		inModule=1;
		inPad = 0;
		numPins=0;
		pin1Found = 0; #a pin named "1" has been found (pin names can be anything)
		modRefDes="";
		modKw="";
		modCd="";
		modName=$2; #possibly not the same as modRefDes but usually is
		ps_module = "";
		
		modTranslateX=0; #always 0 in a library?
		modTranslateY=0;
		modRotation = 0;
		maxBBoxX = 0;
		maxBBoxY = 0;
		minBBoxX = 0;
		maxBBoxY = 0;
	}
}
{
    if (inModule==1 && inPad==0) {
		if ($1=="Po"){
			# Po Xpos Ypos Orientation Layer TimeStamp Attribut1 Attribut2
			modRotation = $4;
			if (postscript=="on"){
				print "thePinFont setfont"
				print (modRotation / 10) " rotate";
			}
		}
		else if ($1=="T0"){
			#    $1         $2   $3   $4    $5     $6        $7    $8    $9       $10  $11  $11
			#Tfield_number Xpos Ypos Xsize Ysize Rotation PenWidth N  Visibility Layer  N  "text"
			#above fields are correct for a footprint created from scratch by kicad build 2012-01-19
			#other libraries have varying numbers of fields but the refdes if any
			#always seems to be the last field and is always in double quotes with
			#or without an N prefix. Yuck! eg:
			#sometimes $NF = N"CP_13x21mm"
			#sometimes $NF-1 = N, $NF = "K200"
			#sometimes the value is just "Ref" or "Ref**" or ">NAME"
			#do we really care about RefDes if the footprint is in a library? Better
			#to search on modName I reckon
			#theRefDes = $NF
			#just pick the bit between double quotes
			#gensub is a gawk extension; it doesn't exist in awk
			#In that case, just comment out the next line
			#and put up with a messy looking RefDes or recode with substr etc. eg: (not tested)
			#if ($NF ~ /N.*/) $NF = substr($NF,1);
			#if ($NF ~ /".*/) $NF = substr($NF,1);
			#if ($NF ~ /[^"]*"/ $NF = substr($NF,1,length($NF)-1);
			#modRefDes = $NF;
			modRefDes = gensub(/([N"]*)([^"]+)(["]*)/, "\\2", "g", $NF); #"
		}
		else if ($1=="T1"){ #same comments as for T1 above
			modVal = gensub(/([N"]*)([^"]+)(["]*)/, "\\2", "g", $NF); #" VAL*** - bit useless really
		}
		else if ($1=="Cd"){#comment description - variable length - can contain ampersands (or any xml horrors)
			modCd = substr($0,4);#lop off initial "CD " WARNING sometimes leaves newline at the end which trim doesn't remove??
			#there's something fishy going on here sometimes - newline appears in $0 from nowhere - hopefully fixed - was due to DOS line endings
			#modKw = substr(modKw,1,length(modKw)-1);#lop off trailing nl ??
			modCd = fixIllegalXmlChars(modCd);
		}
		else if ($1=="Kw"){#keywords - variable length - can contain ampersands (or any xml horrors)
			#modKw = trim(substr($0,4)) "len= " length($0);#lop off initial "Kw " same WARNING
			modKw = substr($0,4);#lop off initial "Kw " same WARNING
			modKw = fixIllegalXmlChars(modKw);
		}
		else if ($1=="DS"){
			#   DS -10000 -10000 -10000 10000 150 21
			setBoundingX($2);
			setBoundingX($4);
			setBoundingY($3);
			setBoundingY($5);
			#=> -10000 -10000 -10000 10000 150 21 DS
			#maxBBoxX = max($2)
			#when using 1 -1 scale to invert y axis:
			ps_module = ps_module $2 " " $3 " " $4 " " $5 " " $6 " " $7 " " $1"\n";
			#when NOT using 1 -1 scale to invert y axis:
			#ps_module = ps_module $2 " " $3 " neg " $4 " " $5 " neg " $6 " " $7 " " $1"\n";
		}
		else if ($1=="DC"){
			#   DC x1 y1 x2 y2 150 21
			setBoundingX($2);
			setBoundingX($4);
			setBoundingY($3);
			setBoundingY($5);
			#=>   x1  y1  x1  y1  x2  y2   distance   150 21 DC
			#when using 1 -1 scale to invert y axis:
			ps_module = ps_module $2 " " $3 " " $2 " " $3 " " $4 " " $5 " distance " $6 " " $7 " " $1 "\n";""
			#when NOT using 1 -1 scale to invert y axis:
			#ps_module = ps_module $2 " " $3 " neg " $2 " " $3 " neg " $4 " " $5 " distance " $6 " " $7 " " $1 "\n";""
		}
		else if ($1=="DA"){
			#   DA -4000 -4000 -8000 -4000 450   150       21
			#   $1 $2      $3    $4    $5  $6    $7        $8
			#   DA x1      y1    x2    y2  angle linewidth layer
			setBoundingX($2);
			setBoundingX($4);
			setBoundingY($3);
			setBoundingY($5);
			#=>
			
			#-4000 -4000 neg -4000 -4000 neg -8000 -4000 neg distance   -4000 neg -4000 atan -4000 neg -4000 atan  45        add 150 21 DA
			# $2     $3  neg  $2    $3   neg  $4    $5   neg distance    $5   neg   $4  atan   $5  neg   $4  atan  $6 10 div add $7  $8 $1 grestore
			#correct WORK HERE!!
			#-4000 -4000 neg -4000 -4000 neg -8000 -4000 neg distance   0     neg -4000 atan 450 10 div sub      0    neg -4000 atan 150  21 DA 
			# x1     y1  neg  x1    y1   neg  x2    y2   neg distance   y2-y1 neg x2-x1 atan $6  10 div sub     y2-y1 neg x2-x1 atan  $7  $8 DA grestore
			#ps_module = ps_module\
			#"%startDA\n";
			#"gsave\n";
			#ps_module = ps_module redCircle($2,$3,200); #debug only
			#when NOT using 1 -1 scale to invert y axis:
			#ps_module = ps_module\
			#$2 " " $3 " neg " $2 " " $3 " neg " $4 " " $5 " neg distance " $5 - $3 " neg " $4 - $2 " atan " $6 " 10 div sub "  $5 - $3 " neg " $4 - $2 " atan " $7 " " $8 " " $1 " \n";
			#"%endDA\n";
			#when using 1 -1 scale to invert y axis:
				#-4000 -4000  -4000 -4000  -8000 -4000  distance 0  -4000 atan 0  -4000 atan 450 10 div add 150 21 DA 
			ps_module = ps_module\
			$2 " " $3 " " $2 " " $3 " " $4 " " $5 " distance " $5 - $3 " " $4 - $2 " atan "  $5 - $3 " " $4 - $2 " atan " $6 " 10 div add " $7 " " $8 " " $1 " \n";
			"%endDA\n";
			#"grestore\n"\
	#	    #    x1     y1   neg   x1     y1   neg   x2     y2   neg distance   y2-y1     neg   x2-x1    atan   $6   10 div sub    y2-y1     neg   x2-x1     atan   $7     $8     DA
		}
    }
}
inModule==1 && $1=="$PAD" {
    inPad=1;
    numPins++;
#    print "pad found"
}

{
#    $PAD
#    Sh "9" C 1000 1000 0 0 0
#    Dr 0 0 0
#    At SMD N 00888000
#    Ne 0 ""
#    Po -2000 4300
#    $EndPAD
    if (inPad==1){ #MUST IGNORE HOLES TODO
	if ($1=="Sh"){ # Sh      2             3        4      5      6      7       8
	                #Sh     "1"            C       660    660     0      0       0
	                #Shape: [pad name]   shape     Xsize  Ysize  Xdelta Ydelta Orientation
	                #                      |         |      |      |      |      +-- tenths deg     
	                #                      |         |      |      +------+--ignore for now moves pad relative to Po?
	                #                      |         |      +--ignored for round shape?
	                #                      |         +--diameter for round shape
	                #                      +--one of C (Circle),
	                #                                R (Rectangle)
	                #                                O (Oval) rectangle with mitred corners or rounded ends
	                #                                T (Trapezoid) effectively the same as rectangle?
	    gsub(/\"/,"",$2); #remove "s from pad name 
	    padName = $2;
	    padShape = $3;
	    padSizeX = $4; #diameter for round pad
	    padSizeY = $5;
	    padOffsetX = $6;
	    padOffsetY = $7;
	    padRadius = padSizeX/2;
	    padOrientation = $8
	}
	if ($1=="Dr"){ #ROUND HOLE FORMAT:
	               # $1         $2               $3       $4
	               # Dr        500               0        0
	               # Drill [Pad drill diameter] Xoffset Yoffset
	               #                              |       |
	               #                              +-------+--shape (pad) offset (from drill centre) = shape offset X,Y in Pad Properties editor
	               #ELLIPTICAL (oval) HOLE FORMAT:
	               # $1         $2               $3       $4         $5            $6              $7
	               # Dr        500               0        0          O             500             900
	               # Drill [Pad drill diameter] Xoffset  Yoffset   [Hole shape]    [drill.x]    [drill.y] 
	               #                                                not used?       |               +--ellipse axis 1
	               #                                                                +--ellipse axis 2
	               #                                                 
	    drillDiameter = $2;
	    shapeOffsetFromOriginX = $3;
	    shapeOffsetFromOriginY = $4;
	    drillIsRound = 1;
	    if ($NF > 4){ #elliptical (slotted) drill hole
		drillIsRound = 0;
		drillEllipseX = $6;
		drillEllipseY = $7;
	    }
	}
	if ($1=="At"){ # $1       $2     $3   $4
	               # At       STD    N   00E0FFFF
	               # Attr [Pad type] N   [layer mask]
	               #          |      +------+--ignore
	               #          |
	               #          +-- one of: "STD" "SMD" "CONN" "HOLE" "MECA"
	               #          +-- these just affect the layers shapes are created on
	               #          +-- if SMD you can ignore drilling details
	    padType = $2;
	}
	if ($1=="Po"){   $1   $2    $3
	               # Po  2500  2000
	               # Pos X_pos Y_pos (drill centre coords relative to the module origin)
	    padCentreX = $2; #seems this is the nominal centre; shapeOffsetFromOriginX/Y moves the pad relative to this coord...
	    padCentreY = $3; #...it's also the drill centre for non-SMDs  
	}
	#if ($1 == "Le"){
	    #something to do with shape offset from pad origin
	#}
 	if ($1=="$EndPAD") {
	    inPad=0;
	    if (postscript=="on") print "%FP: " modName " Pad#: " numPins " Padname: " padName;#debug only
	    arrPinCentreX[numPins] = padCentreX + shapeOffsetFromOriginX; #keep a note of pin centres for measurement calculations
	    arrPinCentreY[numPins] = padCentreY + shapeOffsetFromOriginY; #keep a note of pin centres for measurement calculations
	    arrPinName[numPins] = padName; #remember actual name in case it isn't a number
	    #if the following 2 lines work in all cases then I'm a Dutchman! (doesn't give correct result if pin is rotated?)
	    setBoundingX(padCentreX + shapeOffsetFromOriginX + padSizeX/2);
	    setBoundingY(padCentreY + shapeOffsetFromOriginY + padSizeY/2);
	    if (padName == "1"){ # unfortunately some pins are named A1 or P1!!
			pin1Found = 1;
		}
	    if (numPins == 1){ # unfortunately some pins are named A1 or P1!!
			pad1CentreX = padCentreX; #remember for drawing a grid later - see drawGrid()
			pad1CentreY = padCentreY; #this is the drill centre or pad centere with no pad offset which is what we need for the grid
			padColour = "red";
	    }
	    else{
			padColour = "darkgreen";
	    }
	    if (padShape == "C"){ #circle 
		                 #Xcentre    Ycentre     radius    linewidth layer DC
			if (postscript=="on"){
				print "gs " padColour;
				print "newpath";
				print padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " " padRadius " 0 360 arc fill";
				print "gr";
			}
			setBoundingX(padCentreX + shapeOffsetFromOriginX + padRadius);
			setBoundingY(padCentreY + shapeOffsetFromOriginY + padRadius);
			if (postscript=="on" && showpinnumbers=="on"){
				printPinNumberC();
			}
		}
		else if (padShape == "O"){ #oval
			if (padSizeX > padSizeY){
				theLength = padSizeX;
				theWidth = padSizeY;
				drawLineInX = 1;
			}
			else{
				theLength = padSizeY;
				theWidth = padSizeX;
				drawLineInX = 0;
			}
			#remove width/2 from both ends of line to compensate for rounded caps
			theLength = theLength - (theWidth/2);
			if (postscript=="on") print "gs " padColour " 1 setlinecap " theWidth " setlinewidth"; #must not use rounded linecaps - they add too much to drill hole overall length
			#print "%padCentreX= " padCentreX " shapeOffsetFromOriginX= " shapeOffsetFromOriginX " padCentreX= " padCentreX " padCentreY= " padCentreY " shapeOffsetFromOriginY= "  shapeOffsetFromOriginY " moveto";
			#print "newpath " padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " moveto";
			if (postscript=="on") print "newpath " padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " moveto"; #translate??
			if (padOrientation != 0){
				if (postscript=="on") print padOrientation/10 " rotate";
			}
			#remove y/2 from both ends of line to compensate for rounded caps
			if (drawLineInX == 1){
				if (postscript=="on") print (-1 * (theLength)/2) " 0 rmoveto";
				if (postscript=="on") print theLength " 0 rlineto stroke";
			}
			else{
				if (postscript=="on") print "0 " (-1 * (theLength)/2) " rmoveto";
				if (postscript=="on") print "0 " theLength " rlineto stroke";
			}
			if (postscript=="on") print "gr";
			if (postscript=="on" && showpinnumbers=="on"){
				printPinNumber();
			}
	    }
	    else{ #padShape is rectangle or trapezoid - treat as rectangle
			pad_width= padSizeX;
			pad_length=padSizeY;
			if (postscript=="on") print "gs " padColour ; #padSizeY " setlinewidth" ;
			if (padOrientation != 0){
				pad_blx= shapeOffsetFromOriginX - padSizeX/2; #add pad offset (Le??) eventually HERE
				pad_bly= shapeOffsetFromOriginY - padSizeY/2;
				if (postscript=="on") print padCentreX " " padCentreY " translate";
				if (postscript=="on") print padOrientation/10 " rotate"; #counterclock
			}
			else{
				pad_blx= padCentreX + shapeOffsetFromOriginX - padSizeX/2; #add pad offset (Le??) eventually HERE
				pad_bly= padCentreY + shapeOffsetFromOriginY - padSizeY/2;
			}
			if (postscript=="on") print "[ " pad_blx " "  pad_bly " "  pad_width " "  pad_length " ] rectfill";
			if (postscript=="on") print "gr";
			if (padSizeX > padSizeY){
				theLength = padSizeX;
				theWidth = padSizeY;
				drawLineInX = 1;
			}
			else{
				theLength = padSizeY;
				theWidth = padSizeX;
				drawLineInX = 0;
			}
			if (postscript=="on" && showpinnumbers=="on"){
				printPinNumber();
			}
	    }
	    #draw drill hole - check what happens to non-circular holes if pad is rotated TODO
	    if (padType != "SMD"){
			#drill hole
			if (drillIsRound==1){
				if (postscript=="on") print "newpath\ngs black " padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " " drillDiameter/2 " 0 360 arc fill gr";
			}
			else{ #this ought to draw a path and then fill it!! TODO
				#fake a slotted hole with a capped line
				if (drillEllipseX > drillEllipseY){
					theLength = drillEllipseX;
					theWidth = drillEllipseY;
					drawLineInX = 1;
				}
				else{
					theLength = drillEllipseY;
					theWidth = drillEllipseX;
					drawLineInX = 0;
				}
				#remove width/2 from both ends of line to compensate for rounded caps
				theLength = theLength - (theWidth/2);
				if (postscript=="on") print "gs black 1 setlinecap " theWidth " setlinewidth"; #must not use rounded linecaps - they add too much to drill hole overall length
				#print "%padCentreX= " padCentreX " shapeOffsetFromOriginX= " shapeOffsetFromOriginX " padCentreX= " padCentreX " padCentreY= " padCentreY " shapeOffsetFromOriginY= "  shapeOffsetFromOriginY " moveto";
				#print "newpath " padCentreX + shapeOffsetFromOriginX " " padCentreY + shapeOffsetFromOriginY " moveto";
				if (postscript=="on") print "newpath " padCentreX " " padCentreY " moveto"; #translate??
				if (padOrientation != 0){
					if (postscript=="on") print padOrientation/10 " rotate";
				}
				#remove y/2 from both ends of line to compensate for rounded caps
				if (drawLineInX == 1){
					if (postscript=="on") print (-1 * (theLength)/2) " 0 rmoveto";
					if (postscript=="on") print theLength " 0 rlineto stroke";
				}
				else{
					if (postscript=="on") print "0 " (-1 * (theLength)/2) " rmoveto";
					if (postscript=="on") print "0 " theLength " rlineto stroke";
				}
				if (postscript=="on") print "gr";
			}
		}
	}              
   }
}
inModule==1 && $1=="$EndMODULE" {
    #add a bounding box
#    ps_module = ps_module "gs blue [ " minBBoxX " "  minBBoxY " "  maxBBoxX - minBBoxX " "  maxBBoxY - minBBoxY " ] rectstroke gr\n";
    #that's all the graphics drawn so restore original state so we can add our own text etc.
    #drawGrid();
    ps_module = ps_module "gr %endKicadSpace\n"; #this restore sets us back to no scaling at all, just a
                                  #translation to the page centre
    if (postscript=="on"){
		print ps_module;
		printDetails();
	}
	
    inModule=0;
#    print "\tFootprint", modName, "has", numPins, "pins.";
#    modTranslate=modTranslateX " " modTranslateY " translate\n"
#TODO REINSTATE ME    print filename, modName, numPins,preamble modTranslate ps_module postamble;
#    print preamble modTranslate ps_module postamble;
    #print ps_module;
    #drawDimensions(blx,bly - 4*textOffset,textOffset);
    #print "gr";
    print postamble;
    #print "\tFootprint", "fruit", "has", numPins, "pins.";
    if (outputxml == "on"){
		print "<file>" fixIllegalXmlChars(filename) "</file>";
		print "<name>" fixIllegalXmlChars(modName) "</name>";
		print "<refdes>" fixIllegalXmlChars(modRefDes) "</refdes>";
		print "<numpins>" numPins "</numpins>";
		print "<commentdesc>" modCd "</commentdesc>";
		print "<keywords>" modKw "</keywords>";
		print "</module>";
    }
}