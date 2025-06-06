## Big Num Calculator
This is a calculator meant to do large and precise calculations, started as an high school project (meaning I don't know if I'll keep it updated).
### What does work?
- Basic operations (addition, subtraction, multiplication, division);
- Factorial;
- Expression evaluation;
- Powers.
### What does NOT work yet?
- Modular expressions;
- Radical;
- Logarithms;
- Drag and dropping files;
- Negative and decimal numbers;
- Numbers too big (like 10000!, but not 1000!) appear to be broken in the release, but not while debugging.
### Algorithms used:
- Shunting yard to evaluate expressions;
- Karatsuba for multiplication;
- Binary search (and slight dp) for division;
- Factorized factorial;
