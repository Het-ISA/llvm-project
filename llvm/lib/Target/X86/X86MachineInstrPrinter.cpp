#include "X86.h"
#include "X86InstrInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
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

  // void addPadding(MachineBasicBlock *MBB,
  //                 MachineBasicBlock::iterator &MBBI,
  //                 unsigned int NOOPsToAdd);

};

char X86MachineInstrPrinter::ID = 0;

bool X86MachineInstrPrinter::runOnMachineFunction(MachineFunction &MF) {
  std::error_code EC;
  llvm::raw_fd_ostream File("obj/x86_code_dump.txt", EC, llvm::sys::fs::OF_Append);

  if (EC) {
    errs() << "Error opening file: " << EC.message() << "\n";
    return false;
  }
  const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
  MachineBasicBlock &EntryBlock = MF.front();
  EntryBlock.insert(EntryBlock.begin(),
                          BuildMI(EntryBlock, EntryBlock.begin(), EntryBlock.begin()->getDebugLoc(), TII.get(X86::NOOP)));

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


/// addPadding - Add the given number of NOOP instructions to the function
/// just prior to the return at MBBI
// void X86MachineInstrPrinter::addPadding(MachineBasicBlock *MBB,
//                               MachineBasicBlock::iterator &MBBI,
//                               unsigned int NOOPsToAdd) {
//   const DebugLoc &DL = MBBI->getDebugLoc();
//   unsigned IssueWidth = TSM.getIssueWidth();

//   for (unsigned i = 0, e = IssueWidth * NOOPsToAdd; i != e; ++i)
//     BuildMI(*MBB, MBBI, DL, TSM.getInstrInfo()->get(X86::NOOP));
// }
