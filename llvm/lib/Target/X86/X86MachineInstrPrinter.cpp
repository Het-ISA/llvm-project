#include "X86.h"
#include "X86InstrInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/Support/FileSystem.h"

using namespace llvm;


#define X86_MACHINEINSTR_PRINTER_PASS_NAME "Dummy X86 machineinstr printer pass"


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
  std::error_code EC;
  llvm::raw_fd_ostream File("code_dump.txt", EC, llvm::sys::fs::OF_Append);

  if (EC) {
    errs() << "Error opening file: " << EC.message() << "\n";
    return false;
  }

  File << "MachineFunction: " << MF.getName() << "\n";
  for (auto &MBB: MF) {
    File << "Contents of MachineBasicBlock:\n";
    File << MBB << "\n";
    const BasicBlock *BB = MBB.getBasicBlock();
    File << "Contents of BasicBlock corresponding to MachineBasicBlock:\n";
    for (const auto &Inst: *BB) {
      File << Inst << '\n';
    }
    File << BB << "\n\n\n";
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

