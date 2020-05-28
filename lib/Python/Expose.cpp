#include "Expose.h"

#include <mlir/IR/Types.h>

using namespace pybind11;

namespace mlir {
namespace py {

void expose(module &m) {
  exposeParser(m);
  exposeModule(m);
  auto type = exposeTypeBase(m);
  exposeAttribute(m);
  //exposeType(m, type);
  //exposeValue(m);
  //exposeOps(m);
}

} // end namespace py
} // end namespace mlir
