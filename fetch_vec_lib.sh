cd ..
rm -rf generic-data-structures
git clone https://github.com/novak-stevanovic/generic-data-structures
cp generic-data-structures/include/*.h nu-term/include/lib
cd generic-data-structures
make clean && make
cd ..
cp generic-data-structures/libgds.so nu-term/lib
