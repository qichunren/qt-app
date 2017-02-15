#/bin/sh

find -name Makefile -exec rm {} \;
find -name *.o -exec rm {} \;
find -name moc_*.cpp -exec rm {} \;
find -name ui_*.h -exec rm {} \;
find -name qrc_*.cpp -exec rm {} \;
rm -rf ./bin/*
qmake && make
echo "Finished."
