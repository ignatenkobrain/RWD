if [ $(uname -a|grep -c 'x86_64') -ne 0 -o $(uname -a|grep -c 'ia64') -ne 0 ];
then
yum install boost-devel.x86_64
else
yum install boost-devel.i686
fi
yum install eigen3-devel.noarch
qmake-qt4 RWD-draft.pro -r -spec linux-g++ CONFIG+=debug
make
make clean

