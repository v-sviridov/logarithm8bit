# Light wight function for approximately calculate decibel without using math library.

Can be useful on 8-bit microcontrollers with low memory.  
This algorithm based on  "Single-precision floating-point format" (https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
that already contain exponent of 2 

Dicibel calculated as 10\*log(X).  
It can be modified to 10\*log(2)\*lg2(X) => 3.01\*lg2(X)  
Represent lg2(X) as lg2(2^N \* K) = N + lg2(K), where "K" is  X/(2^N).   
2^N is nearest lower power of 2."K" has value between 1 and 2.  
So we can split this diapasone to parts and precalculate its value.
```
K:                    1.0,  1.1     1.2     1.3     1.4     1.5     1.6     1.7     1.8     1.9     2.0
precalculated lg2 = { 0.0,  0.1375, 0.2630, 0.3785, 0.4854, 0.5850, 0.6781, 0.7655, 0.8480, 0.9260, 1.0};
```
"N" (exponent of 2) we can obtain from X, see link to floating-point format above.  
index of nearest "K": i = (int)((K - 1) * 10 + 0.5); // we add 0.5 to round for nearest 
So dB = N + lg2\[i\]

For example calculate decibel of 42:  
10\*log(42) = 3.01\*lg2(42) = 3.01\*lg2(32\*(42/32)) = 3.01\*(5 + lg2(1.3125)  
Take precalculated value for 1.3125. Its neares index is 3 and value lg2\[3\] = 0.3785  
So approximately value of dB(42) is 3.01\*(5 + 0.3785) = 16.19  
Precision value is 16.23  
Those. the inaccuracy in this case is 0.04
