STXXL_ROOT      = /home/hindol/Softwares/stxxl-1.3.1
STXXL_CONFIG    ?= stxxl.mk
include $(STXXL_ROOT)/$(STXXL_CONFIG)

# use the variables from stxxl.mk
CXX              = $(STXXL_CXX)
CPPFLAGS        += $(STXXL_CPPFLAGS)
LDLIBS          += $(STXXL_LDLIBS)

# add your own optimization, warning, debug, ... flags
# (these are *not* set in stxxl.mk)
CPPFLAGS        += -O3 -Wall -Wextra -std=c++0x -g

# build your application
# (my_example.o is generated from my_example.cpp automatically)
mis.bin: src/main.o src/Edge.o src/Vertex.o src/PQElem.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) src/main.o src/Edge.o src/Vertex.o src/PQElem.o -o $@ $(LDLIBS)

clean:
	rm src/main.o src/Edge.o src/Vertex.o src/PQElem.o mis.bin
