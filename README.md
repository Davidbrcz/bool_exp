First you need the C++ antlr library here : https://github.com/DanMcLaughlin/antlr4
```
git clone https://github.com/DanMcLaughlin/antlr4.git
cd antlr4//runtime
mkdir bin
cd bin
cmake ../Cpp
make
sudo make install
```

After 
```
mkdir bin
cd bin 
cmake ../src -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DANTLR_JAR_LOCATION=../src/antlr/antlr4-4.5.4-SNAPSHOT.jar
```
