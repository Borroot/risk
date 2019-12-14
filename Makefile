all: risk

risk: risk.cpp
	$(CXX) -o $@ $<

clean:
	rm -f risk
