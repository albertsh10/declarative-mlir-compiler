LUAC=../bin/lua/mluac

bin/main: bin bin/impl.o bin/luallvm.o
	g++ bin/impl.o bin/luallvm.o -o bin/main

bin/impl.o: bin impl.cpp
	clang -std=c++17 impl.cpp -c -o bin/impl.o -g -Wall

bin/luallvm.o: bin $(LUAC) bin/luallvm.ll
	clang -c bin/luallvm.ll -o bin/luallvm.o

bin/luallvm.ll: bin $(LUAC) bin/luallvm.mlir
	mlir-translate --mlir-to-llvmir bin/luallvm.mlir -o bin/luallvm.ll

bin/luallvm.mlir: bin $(LUAC) main.mlir dialect.mlir lib.mlir
	$(LUAC) main.mlir -dialect=dialect.mlir -lower-to-luac -lower-to-lua-lib -lualib=lib.mlir -loop-to-std -lower-to-llvm -o bin/luallvm.mlir

bin:
	mkdir -p bin