#include <pybind11/pybind11.h>
#include <Crockford32.h>

PYBIND11_MODULE(crockford32, m) {
  m.doc() = "crockford base32 encoding implementation"
}
