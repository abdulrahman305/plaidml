pml_cc_library(
  NAME transforms
  HDRS
    pass_detail.h
    passes.h
  SRCS
    boundscheck.cc
    main_closure.cc
    split_closure.cc
  DEPS
    LLVMSupport
    MLIRIR
    ::passes-gen
    pmlc::dialect::stdx::ir
  PUBLIC
)

pml_tblgen_library(
  NAME passes-gen
  TD_FILE passes.td
  OUTS
    -gen-pass-decls passes.h.inc
)
