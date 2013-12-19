#!/bin/sh
echo "creating lib..."
rm libxapiand.a
g++ -c -O3 *.cpp -L-lxapian
g++ -Wall -shared -fPIC -o libxapiand.so -L-lxapian *.cpp
ar rvs libxapiand.a *.o
rm *.o