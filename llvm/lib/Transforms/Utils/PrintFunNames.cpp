#include "llvm/Transforms/Utils/PrintFunNames.h"
#include "llvm/IR/Function.h"

using namespace llvm;

PreservedAnalyses PrintFunNamesPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  return PreservedAnalyses::all();
}
