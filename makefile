warnings = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual

cxx = g++ -std=c++11

objects = main.o Fraction.o NumericException.o SafeArithmetics.o Utilities.o

prog_name = a.out

$(prog_name): $(objects)
	$(cxx) $(objects) -o $@

main.o: main.cpp Fraction.hpp NumericException.hpp
	$(cxx) -c main.cpp $(warnings) -o $@

Fraction.o: Fraction.cpp Fraction.hpp SafeArithmetics.hpp DivisionByZeroException.hpp NumericOverflowException.hpp
	$(cxx) -c Fraction.cpp $(warnings) -o $@

NumericException.o: NumericException.cpp NumericException.hpp
	$(cxx) -c NumericException.cpp $(warnings) -o $@

SafeArithmetics.o: SafeArithmetics.cpp SafeArithmetics.hpp NumericOverflowException.hpp
	$(cxx) -c SafeArithmetics.cpp $(warnings) -o $@

Utilities.o: Utilities.cpp Utilities.hpp NumericOverflowException.hpp
	$(cxx) -c Utilities.cpp $(warnings) -o $@

clean:
	rm -f *.o $(prog_name)

