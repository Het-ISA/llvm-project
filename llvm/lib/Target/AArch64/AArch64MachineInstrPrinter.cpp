#include "AArch64.h"
#include "AArch64InstrInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/FileSystem.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace llvm;

#define AArch64_MACHINEINSTR_PRINTER_PASS_NAME                                 \
  "Dummy AArch64 machineinstr printer pass"

namespace {

class AArch64MachineInstrPrinter : public MachineFunctionPass {
public:
  static char ID;

  AArch64MachineInstrPrinter() : MachineFunctionPass(ID) {
    initializeAArch64MachineInstrPrinterPass(*PassRegistry::getPassRegistry());
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  StringRef getPassName() const override {
    return AArch64_MACHINEINSTR_PRINTER_PASS_NAME;
  }

  // void addPadding(MachineBasicBlock *MBB,
  //                 MachineBasicBlock::iterator &MBBI,
  //                 unsigned int NOOPsToAdd);
};

char AArch64MachineInstrPrinter::ID = 0;

bool AArch64MachineInstrPrinter::runOnMachineFunction(MachineFunction &MF) {
  // std::error_code EC;
  // llvm::raw_fd_ostream File("obj/funnames", EC, llvm::sys::fs::OF_Append);

  // if (EC) {
  //   errs() << "Error opening file: " << EC.message() << "\n";
  //   return false;
  // }

  const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
  MachineBasicBlock &EntryBlock = MF.back();
  // File << MF.getName() << "\n";

  MachineBasicBlock::iterator ReturnLoc = --EntryBlock.end();

  while (ReturnLoc->isDebugInstr()) {
    --ReturnLoc;
  }

  assert(ReturnLoc->isReturn() && !ReturnLoc->isCall() &&
         "Basic block does not end with RET");

  std::unordered_set<std::string> data;
  std::ifstream paddings_file("obj/arm_pad");

  if (!paddings_file.is_open()) {
    errs() << "Error opening arm_pad in AArch64 NOP appender\n";
    return false;
  }

  std::string line;
  while (std::getline(paddings_file, line)) {
    // Process each line as needed
    std::string function_name = line.substr(0, line.find(":"));
    if (function_name == MF.getName().data()) {
      std::string size_str = line.substr(line.find(":") + 1, line.size());
      // one NOOP => 4 bytes
      int size = std::atoi(size_str.c_str()) / 4;

      for (auto i = 0; i < size; ++i) {
        BuildMI(EntryBlock, ReturnLoc, ReturnLoc->getDebugLoc(),
                TII.get(AArch64::HINT))
            .addImm(0);
      }
    }
  }

  paddings_file.close(); // Close the file

  // std::unique_ptr<llvm::MemoryBuffer> &buffer = bufferOrErr.get();
  // llvm::StringRef content = buffer->getBuffer();
  // errs() << content.data() << '\n';

  // for (llvm::StringRef line : content.split('\n')) {
  //   llvm::StringRef trimmed = line.trim();
  //   if (!trimmed.empty()) {
  //     llvm::StringRef functionName =
  //         trimmed.split(':').first.trim(); // Extract name before ':'
  //     data.insert(functionName.str());
  //   }
  // }

  // Get the function name from MockMachineFunction
  // llvm::StringRef functionName = MF.getName();

  // // Check if the function name exists in the data
  // if (data.find(functionName.data()) != data.end()) {
  //   File << "Function " << functionName << " found in data.txt\n";
  // } else {
  //   File << "Function " << functionName << " not found in data.txt\n";
  // }

  // for (auto &MBB: MF) {
  //   File << "Contents of MachineBasicBlock:\n";
  //   File << MBB << "\n";
  //   const BasicBlock *BB = MBB.getBasicBlock();
  //   File << "Contents of BasicBlock corresponding to MachineBasicBlock:\n";
  //   for (const auto &Inst: *BB) {
  //     File << Inst << '\n';
  //   }
  //   File << BB << "\n\n\n";
  // }

  return false;
}

} // end of anonymous namespace

INITIALIZE_PASS(AArch64MachineInstrPrinter, "AArch64-machineinstr-printer",
                AArch64_MACHINEINSTR_PRINTER_PASS_NAME,
                true, // is CFG only?
                true  // is analysis?
)

namespace llvm {

FunctionPass *createAArch64MachineInstrPrinterPass() {
  return new AArch64MachineInstrPrinter();
}

} // namespace llvm

/// addPadding - Add the given number of NOOP instructions to the function
/// just prior to the return at MBBI
// void AArch64MachineInstrPrinter::addPadding(MachineBasicBlock *MBB,
//                               MachineBasicBlock::iterator &MBBI,
//                               unsigned int NOOPsToAdd) {
//   const DebugLoc &DL = MBBI->getDebugLoc();
//   unsigned IssueWidth = TSM.getIssueWidth();

//   for (unsigned i = 0, e = IssueWidth * NOOPsToAdd; i != e; ++i)
//     BuildMI(*MBB, MBBI, DL, TSM.getInstrInfo()->get(AArch64::NOOP));
// }
