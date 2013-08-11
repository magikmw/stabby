LINK=$(readlink $0)
if [ -z $LINK ]; then
	DIR=$(dirname $0)
else
	DIR=$(dirname $LINK)
fi

cd $DIR/bin
./stabby
