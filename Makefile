STD = -std=c++17
OPT = -O2

FLAGS += -I$(CURDIR)/include
FLAGS += -I$(HOME)/local/include

LINK_FLAGS += -lstdc++fs

# default: gen-html
default: generate

bin:
	mkdir -p bin

gen-html: bin
	$(CXX) $(STD) $(OPT) $(FLAGS) \
		src/stdml-doc.cpp \
		src/stdtensor-doc.cpp \
		-o bin/gen-html $(LINK_FLAGS)

generate: gen-html
	./bin/gen-html
