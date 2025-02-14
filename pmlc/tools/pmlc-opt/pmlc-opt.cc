// Copyright 2020 Intel Corporation

#include "llvm/Support/Process.h"

#include "mlir/Tools/mlir-opt/MlirOptMain.h"

#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "pmlc/all_dialects.h"
#include "pmlc/all_passes.h"
#include "pmlc/util/logging.h"

int main(int argc, char **argv) {
  auto verboseEnv = llvm::sys::Process::GetEnv("PLAIDML_VERBOSE");
  if (verboseEnv) {
    auto level = std::atoi(verboseEnv->c_str());
    if (level) {
      el::Loggers::setVerboseLevel(level);
    }
    IVLOG(level, "PLAIDML_VERBOSE=" << level);
  }

  mlir::registerAllPasses();
  pmlc::registerAllPasses();

  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  pmlc::registerAllDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "PMLC modular optimizer driver\n", registry,
                        /*preloadDialectsInContext=*/true));
}
