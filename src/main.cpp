#include <pybind11/pybind11.h>

int64_t collatz(int64_t n) {
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

class MyInt {
 private:
  int64_t x = 42;
 public:
  int64_t get() const {
    return x;
  }
};

namespace py = pybind11;

PYBIND11_PLUGIN(pybind11_benchmark) {
    py::module m("pybind11_benchmark");

    m.def("collatz", &collatz,
          "Run one iteration of the mapping underlying the Collatz cojecture");

    py::class_<MyInt>(m, "MyInt")
      .def(py::init<>())
      .def("get", &MyInt::get);

#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    return m.ptr();
}
