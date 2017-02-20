CXX = g++
CXXFLAGS = -std=c++14 -O3
LIBS = -ltestu01 -lprobdist -lmylib

$(info Compiling...)

all :: big_wheel_smallcrush big_wheel_crush big_wheel_bigcrush

big_wheel_smallcrush : big_wheel_crushes.cpp
	$(CXX) $(CXXFLAGS) -DCRUSH_LEVEL=0 big_wheel_crushes.cpp -o big_wheel_smallcrush $(LIBS)

big_wheel_crush : big_wheel_crushes.cpp
	$(CXX) $(CXXFLAGS) -DCRUSH_LEVEL=1 big_wheel_crushes.cpp -o big_wheel_crush $(LIBS)

big_wheel_bigcrush : big_wheel_crushes.cpp
	$(CXX) $(CXXFLAGS) -DCRUSH_LEVEL=2 big_wheel_crushes.cpp -o big_wheel_bigcrush $(LIBS)

.PHONY: clean
clean:
	rm big_wheel_smallcrush
	rm big_wheel_crush
	rm big_wheel_bigcrush
	@echo "Done."

