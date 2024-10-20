#include "llvm/Transforms/Utils/PrintFunNames.h"
#include "llvm/IR/Module.h"

using namespace llvm;

PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
  for (auto &F : M) {
    errs() << "I saw a function called " << F.getName() << "!\n";
  }
  return PreservedAnalyses::all();
}
