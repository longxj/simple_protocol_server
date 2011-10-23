echo "start to make cscope index ..."
find src/ -iname "*.hpp" > cscope.files
find src/ -iname "*.cpp" >> cscope.files
find src/ -iname "makefile" >> cscope.files
cscope -b

echo "Done, you can use cscope now"