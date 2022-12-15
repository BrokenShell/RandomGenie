# Random Genie


ChatGPT Prompt Programming
> Create a c++ component that will serve as a random number engine. This will be used to facilitate the creation of random value distribution algorithms.

Here is an example of a C++ component that can serve as a random number engine:

```cpp
#include <random>

class RandomNumberEngine
{
public:
  // Constructor
  RandomNumberEngine()
  {
    // Seed the engine with the current time
    engine_.seed(std::chrono::system_clock::now().time_since_epoch().count());
  }

  // Generate a random integer in the specified range
  int generateInt(int min, int max)
  {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine_);
  }

  // Generate a random floating point value in the specified range
  double generateDouble(double min, double max)
  {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(engine_);
  }

private:
  std::mt19937 engine_; // Mersenne Twister engine
};
```

This class uses the Mersenne Twister engine (`std::mt19937`) to generate random numbers. The constructor seeds the engine with the current time, so that the generated numbers will be different each time the program is run. The `generateInt()` and `generateDouble()` methods can be used to generate random integers and floating point values in a specified range.

To use this class, you can create an instance of it and call the `generateInt()` or `generateDouble()` methods as needed:

```cpp
RandomNumberEngine engine;

int randomInt = engine.generateInt(1, 10); 
// generates a random integer between 1 and 10 (inclusive)

double randomDouble = engine.generateDouble(0.0, 1.0); 
// generates a random double between 0.0 and 1.0 (inclusive)
```

Note that this is just one way to implement a random number engine in C++. There are many other options and variations, depending on your specific needs and requirements.

> Write a Cython wrapper for the random number engine. I want to create a Python c-extension.

Here is an example of a Cython wrapper for the random number engine from the previous answer:

```cython
cimport cython
from libcpp.random cimport mt19937, uniform_int_distribution, uniform_real_distribution
from libcpp.chrono cimport system_clock

cdef extern from "random.h":
    cdef cppclass RandomNumberEngine:
        RandomNumberEngine() except +
        int generateInt(int min, int max)
        double generateDouble(double min, double max)

cdef class PyRandomNumberEngine:
    cdef RandomNumberEngine engine

    def __cinit__(self):
        self.engine = RandomNumberEngine()

    cpdef generate_int(self, int min, int max):
        return self.engine.generateInt(min, max)

    cpdef generate_double(self, double min, double max):
        return self.engine.generateDouble(min, max)
```

This Cython code wraps the C++ `RandomNumberEngine` class in a Python extension type called `PyRandomNumberEngine`. The `__cinit__` method is used to initialize the C++ `RandomNumberEngine` object when a `PyRandomNumberEngine` is created in Python. The `generate_int` and `generate_double` methods expose the `generateInt` and `generateDouble` methods of the C++ `RandomNumberEngine` to Python, allowing you to generate random integers and floating point values from Python.

To use this extension, you can import it in your Python code and create an instance of the `PyRandomNumberEngine` class:

```python
from random_engine import PyRandomNumberEngine

engine = PyRandomNumberEngine()

random_int = engine.generate_int(1, 10)  
# generates a random integer between 1 and 10 (inclusive)

random_double = engine.generate_double(0.0, 1.0)  
# generates a random double between 0.0 and 1.0 (inclusive)
```

Note that this is just one way to create a Cython wrapper for a C++ random number engine. The exact details of the implementation will depend on the specific C++ code you are wrapping and your own requirements and preferences.

> Create the `setup.py` file for making this a true c-extension

Here is an example of a `setup.py` file that can be used to build a Cython extension for the `PyRandomNumberEngine` class from the previous answer:

```python
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = [
    Extension(
        "random_engine",
        ["random_engine.pyx"],
        extra_compile_args=["-std=c++14"],
        language="c++",
    ),
]

setup(
    name="random_engine",
    ext_modules=cythonize(extensions),
)
```

This `setup.py` file defines a single Cython extension named `random_engine`, which is built from the `random_engine.pyx` file. It also specifies that the C++14 standard should be used for compilation and links the extension against the C++ standard library.

To build the extension, you can run the following command from the command line:

```shell
python setup.py build_ext --inplace
```

This will compile the Cython code and produce a `random_engine.so` file (or `random_engine.dll` on Windows) in the same directory. This file can be imported as a regular Python module and used to create instances of the `PyRandomNumberEngine` class.

The following is another option for installing the random_genie locally.
```shell
pip install .
```

```python
import random_engine

engine = random_engine.PyRandomNumberEngine()

random_int = engine.generate_int(1, 10)  
# generates a random integer between 1 and 10 (inclusive)

random_double = engine.generate_double(0.0, 1.0)  
# generates a random double between 0.0 and 1.0 (inclusive)
```

Note that this is just one example of a `setup.py` file for a Cython extension. The exact details of the file will depend on the specific Cython code you are building and your own requirements and preferences.

