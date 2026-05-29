set -xe

CC=gcc
CPPC=g++

BUILD_FLAGS="-Wformat -fPIC -O0 -g"
LINK_FLAGS="-shared"

C_SRC="main libdetour/src/libdetour"
CPP_SRC="log"

OBJS=""

for f in $C_SRC
do
	$CC $BUILD_FLAGS -c ${f}.c -o ${f}.o
	OBJS="$OBJS ${f}.o"
done

for f in $CPP_SRC
do
	$CC $BUILD_FLAGS -c ${f}.cpp -o ${f}.o
	OBJS="$OBJS ${f}.o"
done

$CPPC $LINK_FLAGS $OBJS -o x11_xinput_no_close.so
