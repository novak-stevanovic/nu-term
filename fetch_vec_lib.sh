cd ..
cp generic-data-structures/include/*.h nu-term/include/lib
cd generic-data-structures
make clean && make
cd ..
cp generic-data-structures/libgds.so nu-term/lib
