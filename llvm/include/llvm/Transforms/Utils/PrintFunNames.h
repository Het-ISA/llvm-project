#ifndef LLVM_TRANSFORMS_PRINTFUNNAMES_H
#define LLVM_TRANSFORMS_PRINTFUNNAMES_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class PrintFunNamesPass : public PassInfoMixin<PrintFunNamesPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_PRINTFUNNAMES_H