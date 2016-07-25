mkdir bin
cd bin 
cmake ../src -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DANTLR_JAR_LOCATION=../src/antlr/antlr4-4.5.4-SNAPSHOT.jar
