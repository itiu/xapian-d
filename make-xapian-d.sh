#!/bin/sh
echo "creating lib..."
rm libxapiand.a
# static lib
g++ -c -O3 *.cpp -L-lxapian
# dynamic lib
g++ -Wall -shared -fPIC -o libxapiand.so -L-lxapian *.cpp
ar rvs libxapiand.a *.o
rm *.o