# PYPP
Python++ is a small personal project of mine. Be aware that this was written on Windows and for Windows.
The way to use it is to open CMD and pass the directory of .pypp file with code as an argument to the executable.

Features:
- variable declaration
```c++
int INT_VAR = 5; # if variable name is all caps it will be treated as a constant
float floatVar = 45 / 2 -5*3 + INT_VAR - 27;
```
- objects
```c++
object obj = {
    a: 2,
    b: max(1,6,8,3,3,7,4),
    complex: {
        a: var + 21,
        b: "bcd",
        complex: {
            a: var + 68,
            b: 'a'
        }
    },
    c: var
};
```
- if statement
```c++
if (a < 5) {
	# statements
}
```
- for and while loops (for loop is in development)
```c++
while (a < 5) {
	# statements
}
```
- native functions (print, min, max, sqrt, cbrt, sleep)
- functions
```c++
def complex(offset) -> func { # there is a func value type that can 
    def add(a, b) -> int {
         a + b + offset
    }

    add # there is not yet return keyword 
}

func addition = complex();
```
- integrated stopwatch (timerStart(), timerStop(), timerDuration())
```c++
timerStart()
timerStop()
object duration = timerDuration();
print("Duration:", duration.microseconds, "miliseconds")
print("Duration:", timerDuration().milliseconds, "miliseconds", "sep= ")
```
