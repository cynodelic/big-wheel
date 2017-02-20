CXX = g++
CXXFLAGS = -std=c++14 -O3 -g

$(info Compiling...)

all :: five_dice monte_carlo_pi stream_demo

five_dice : five_dice.cpp
	$(CXX) $(CXXFLAGS) five_dice.cpp -o five_dice

monte_carlo_pi : monte_carlo_pi.cpp
	$(CXX) $(CXXFLAGS) monte_carlo_pi.cpp -o monte_carlo_pi -lpthread

stream_demo : stream_demo.cpp
	$(CXX) $(CXXFLAGS) stream_demo.cpp -o stream_demo

.PHONY: clean
clean:
	rm five_dice
	rm monte_carlo_pi
	rm stream_demo
	@echo "Done."

