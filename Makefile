STD = -std=c++17
OPT = -O2

ifeq ($(shell uname), Darwin)
	FLAGS += -DHAVE_STD_CPP_FS
else
	LINK_FLAGS += -lstdc++fs
endif

FLAGS += -I$(CURDIR)/include
FLAGS += -I$(HOME)/local/include


# default: gen-html
default: generate

bin:
	mkdir -p bin

gen-html: bin
	$(CXX) $(STD) $(OPT) $(FLAGS) \
		src/main.cpp \
		src/header.cpp \
		src/stdtensor.cpp \
		src/index.cpp \
		-o bin/gen-html $(LINK_FLAGS)

generate: gen-html
	./bin/gen-html
