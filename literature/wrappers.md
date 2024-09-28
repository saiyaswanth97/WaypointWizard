To call C++ functions from Python, several methods can be used, depending on the level of integration, complexity, and performance requirements. Below are the common methods along with explanations:

### 1. **Using `ctypes` (Standard Library)**
   `ctypes` is a Python library for calling functions in shared libraries/DLLs. It's straightforward and doesn't require additional dependencies, but it's lower-level, meaning you need to handle the conversion of data types manually.

   **Steps:**
   - Compile the C++ code into a shared library (`.so` for Linux, `.dll` for Windows).
   - Use `ctypes` to load the shared library and call the C++ functions.

   ```cpp
   // C++ code (example.cpp)
   extern "C" int add(int a, int b) {
       return a + b;
   }

   // Compile as a shared library:
   // g++ -shared -o libexample.so -fPIC example.cpp
   ```

   ```python
   # Python code (example.py)
   from ctypes import CDLL

   lib = CDLL('./libexample.so')  # Load the shared library
   result = lib.add(3, 4)
   print(result)  # Outputs: 7
   ```

   **Pros:**
   - Built-in Python library.
   - No need for additional software.
   
   **Cons:**
   - Limited to simple functions and manual type conversions.
   - Complex data types like classes and structs are harder to handle.

### 2. **Using `Cython`**
   `Cython` is a popular tool for writing C/C++-like code that is compiled into Python extensions. It allows direct access to C++ classes and functions from Python with minimal performance overhead.

   **Steps:**
   - Write a `.pyx` file with Cython syntax to wrap C++ functions.
   - Use a `setup.py` script to compile the Cython file into a Python extension.

   ```cpp
   // C++ code (example.cpp)
   int multiply(int a, int b) {
       return a * b;
   }
   ```

   ```cython
   # example.pyx (Cython code)
   cdef extern from "example.cpp":
       int multiply(int, int)

   def py_multiply(int a, int b):
       return multiply(a, b)
   ```

   **Pros:**
   - Can handle both simple and complex C++ structures.
   - Excellent for performance-critical applications.
   
   **Cons:**
   - Requires learning some Cython syntax.
   - Needs a compilation step with a `setup.py`.

### 3. **Using `SWIG` (Simplified Wrapper and Interface Generator)**
   SWIG is a tool that automatically generates the wrapper code needed to call C/C++ functions from multiple languages, including Python.

   **Steps:**
   - Create an interface file (`.i`) for the C++ functions.
   - Use SWIG to generate Python bindings from the interface file.
   - Compile the generated files into a Python module.

   ```cpp
   // C++ code (example.cpp)
   int subtract(int a, int b) {
       return a - b;
   }
   ```

   ```swig
   // example.i (SWIG interface file)
   %module example
   extern int subtract(int a, int b);
   ```

   **Pros:**
   - Automatically generates bindings for large C++ codebases.
   - Supports many complex data types and class methods.
   
   **Cons:**
   - Interface files may need manual adjustments for more complex cases.
   - Initial setup can be complex.

### 4. **Using `pybind11`**
   `pybind11` is a modern, lightweight library that enables seamless interoperability between Python and C++. It's widely used due to its clean syntax and ability to directly work with C++11 and beyond.

   **Steps:**
   - Write C++ functions/classes, and expose them using `pybind11`.
   - Compile the code into a Python module.

   ```cpp
   // example.cpp (with pybind11)
   #include <pybind11/pybind11.h>

   int divide(int a, int b) {
       return a / b;
   }

   PYBIND11_MODULE(example, m) {
       m.def("divide", &divide, "A function that divides two numbers");
   }

   // Compile:
   // c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`
   ```

   ```python
   # Python code (example.py)
   import example
   print(example.divide(10, 2))  # Outputs: 5
   ```

   **Pros:**
   - Very easy to use and requires minimal boilerplate code.
   - Supports modern C++ features and complex types like classes, smart pointers, etc.
   
   **Cons:**
   - Requires a C++11 (or later) compiler.
   - Requires installation of the `pybind11` package.

### 5. **Using `Boost.Python`**
   `Boost.Python` is a library within the Boost framework, designed for interfacing C++ and Python. It supports complex C++ types and provides a high-level interface.

   **Steps:**
   - Write a C++ file with `Boost.Python` bindings.
   - Compile the code into a Python module.

   ```cpp
   // example.cpp (Boost.Python)
   #include <boost/python.hpp>

   int mod(int a, int b) {
       return a % b;
   }

   BOOST_PYTHON_MODULE(example) {
       using namespace boost::python;
       def("mod", mod);
   }
   ```

   **Pros:**
   - Rich support for complex C++ types and class hierarchies.
   - Mature and well-tested library.
   
   **Cons:**
   - The setup can be complex, and Boost has a steep learning curve.
   - `Boost.Python` can be slower compared to `pybind11`.

---

### Summary Table:

| Method        | Complexity   | Performance | Use Case                         |
|---------------|--------------|-------------|----------------------------------|
| **`ctypes`**  | Low          | Moderate    | Simple function calls            |
| **`Cython`**  | Moderate     | High        | Performance-critical, simple or complex functions |
| **`SWIG`**    | High         | High        | Large C++ codebases, automation  |
| **`pybind11`**| Moderate     | High        | Modern C++ projects, clean syntax|
| **Boost.Python** | High      | High        | Complex C++ structures           |

The choice of method depends on the complexity of your C++ code, performance requirements, and ease of use. For most modern C++ projects, **`pybind11`** is the most efficient and user-friendly.