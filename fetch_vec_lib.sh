cd ..
mkdir -p nu-term/include/lib/gds
cp -r generic-data-structures/include/* nu-term/include/lib/gds/
cd generic-data-structures
make clean && make
cd ..
cp generic-data-structures/libgds.so nu-term/lib
