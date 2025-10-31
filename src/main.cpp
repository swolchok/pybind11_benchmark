#include <pybind11/pybind11.h>
#ifdef PYBIND11_HAS_NATIVE_ENUM
#include <pybind11/native_enum.h>
#endif

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

enum class MyEnum {
  ONE = 1,
  TWO = 2,
};

enum class MyNativeEnum {
  THREE = 3,
  FOUR = 4,
};

namespace py = pybind11;

PYBIND11_PLUGIN(pybind11_benchmark) {
    py::module m("pybind11_benchmark");

    m.def("collatz", &collatz,
          "Run one iteration of the mapping underlying the Collatz cojecture");

    py::class_<MyInt>(m, "MyInt")
      .def(py::init<>())
      .def("get", &MyInt::get);

    py::enum_<MyEnum>(m, "MyEnum", py::arithmetic())
      .value("ONE", MyEnum::ONE)
      .value("TWO", MyEnum::TWO)
      .export_values();

#ifdef PYBIND11_HAS_NATIVE_ENUM
    py::native_enum<MyNativeEnum>(m, "MyNativeEnum", "enum.IntEnum")
      .value("THREE", MyNativeEnum::THREE)
      .value("FOUR", MyNativeEnum::FOUR)
      .export_values()
      .finalize();
#endif

#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    return m.ptr();
}
