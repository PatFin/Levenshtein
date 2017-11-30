#! /bin/bash
echo "--------------------------------------------------------------"
execDir=`pwd`

if [ -d "$1" ]
then
	Directory="$1"
else
	echo "Not a directory, exiting"
	exit 2
fi

cd $Directory

if [ -r "description" ]
then
	fold description -w 80 -s
	echo "--"
fi

nTestCount=0
nSuccesfulTests=0
nStrResult="$1 "

if [ -r "run" ]
then
	sRun=`cat run`
else
	echo "No run file, exiting"
	exit 2
fi

#stdin specified
if [ -r "std.in" ]
then 
	sRun="$sRun <std.in"
fi

#stdout specified
if [ -r "stdout" ]
then
	sRun="sRun > temp.txt"
fi

#stderr specified
if [ -r "stderr.out" ]
then 
	sRun="$sRun 2>temperr.txt"
fi

echo $sRun
eval $sRun
returnCode=$?

resultGlobal=1

#Could compare return code

resultOut=2
if [ -r "std.out" ]
then
	diff -wB temp.txt std.out >/dev/null
	if [ $? -eq 0 ]
	then 
		echo "STDOUT : Passed"
		resultOut=1
	else
		echo "STDOUT : Failed"
		resultOut=0
		resultGlobal=0
	fi
	rm temp.txt
fi

if [ -r "stderr.out" ]
then 
	diff -wB temperr.txt stderr.out >/dev/null
	if [ $? -eq 0 ]
	then 
		echo "STDERR : Passed"
		resultOut=1
	else
		echo "STDERR : Failed"
		resultErr=0
		resultGlobal=0
	fi
	rm temperr.txt
fi


echo "-------------------------------------------------------------------"
if [ $resultGlobal -eq 0 ]
then
	echo "GLOBAL : Failed"
else
	echo "GLOBAL : Passed"
fi

#Write to the csv file provided
cd $execDir
if [ ! -w "$2" ]
then 
	touch $2
fi
if [ -w "$2" ]
then
	echo
	"$Directory;$resultOut;$resultErr;$resultGlobal" >>$2
fi

exit $resultGlobal
