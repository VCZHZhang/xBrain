#/bin/sh

ctags -R .
rm -fr cscope.*
find `pwd` -name "*.[ch]" > cscope.files
find `pwd` -name "*.cpp" >> cscope.files
cscope -bRq
