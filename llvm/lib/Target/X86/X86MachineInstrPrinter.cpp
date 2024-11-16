#include "X86.h"
#include "X86InstrInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

using namespace llvm;


#define X86_MACHINEINSTR_PRINTER_PASS_NAME "Dummey X86 machineinstr printer pass"


namespace {

class X86MachineInstrPrinter : public MachineFunctionPass {
public:
  static char ID;

  X86MachineInstrPrinter() : MachineFunctionPass(ID) {
    initializeX86MachineInstrPrinterPass(*PassRegistry::getPassRegistry());
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  StringRef getPassName() const override { return X86_MACHINEINSTR_PRINTER_PASS_NAME;}

};

char X86MachineInstrPrinter::ID = 0;

bool X86MachineInstrPrinter::runOnMachineFunction(MachineFunction &MF) {
  for (auto &MBB: MF) {
    errs() << "Contents of MachineBasicBlock:\n";
    errs() << MBB << "\n";
    const BasicBlock *BB = MBB.getBasicBlock();
    errs() << "Contents of BasicBlock corresponding to MachineBasicBlock:\n";
    errs() << BB << "\n";
  }
  return false;
}

} // end of anonymous namespace


INITIALIZE_PASS(X86MachineInstrPrinter, "x86-machineinstr-printer",
  X86_MACHINEINSTR_PRINTER_PASS_NAME,
  true, // is CFG only?
  true  // is analysis?
)

namespace llvm {
  
FunctionPass *createX86MachineInstrPrinterPass() { return new X86MachineInstrPrinter();}

}

