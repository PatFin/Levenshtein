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

echo "$sRun"
eval "$sRun"

returnCode=$?

resultGlobal=1

#Could compare return code

resultOut=2
if [ -r "std.out" ]
then
	touch temp.txt
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
	touch temperr.txt
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

exit
#Write to the csv file provided
cd ..
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
