ar x libxapian.a
l1=`ar t libxapian.a |  grep brass`
l2=`ar t libxapian.a |  grep flint`
l3=`ar t libxapian.a |  grep chert`
l4=`ar t libxapian.a |  grep glass`

ar rvs libxapian-backend.a $l1 $l2 $l3 $l4

rm $l1
rm $l2
rm $l3
rm $l4

ar rvs libxapian-main.a *.o

rm *.o
