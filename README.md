First you need the C++ antlr library here : https://github.com/DanMcLaughlin/antlr4
RIGHT NOW; I use the if guard feature from C++17. This means you to
compile the project with clang 3.9 and the libraries too. When
compiling ANTLR C++, you need to make sure that you set -DWITH_LIBCXX=Off


```
git clone https://github.com/DanMcLaughlin/antlr4.git
cd antlr4/runtime
mkdir bin
cd bin
# best case 
cmake ../Cpp
# real case 
# cmake -DWITH_LIBCXX=Off -DCMAKE_C_COMPILER=$(which clang) -DCMAKE_CXX_COMPILER=$(which clang++) -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../Cpp
make
sudo make install
```

After 
```
mkdir bin
cd bin 
cmake ../src -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DANTLR_JAR_LOCATION=../src/antlr/antlr4-4.5.4-SNAPSHOT.jar
```
