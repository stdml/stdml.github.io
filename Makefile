STD = -std=c++17
OPT = -O2

FLAGS += -I$(CURDIR)/include

# default: gen-html
default: generate

bin:
	mkdir -p bin

gen-html: bin
	$(CXX) $(STD) $(OPT) $(FLAGS) src/stdml-doc.cpp -o bin/gen-html

generate: gen-html
	./bin/gen-html
