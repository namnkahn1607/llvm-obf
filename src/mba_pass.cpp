#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Config/llvm-config.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/Compiler.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

struct MbaPass : public PassInfoMixin<MbaPass> {
    PreservedAnalyses run(Function& F, FunctionAnalysisManager&) {
        errs() << "[MbaPass] Visiting function: " << F.getName() << '\n';

        // Phase 1: Pre-collect all transforming instrucions into container.
        SmallVector<BinaryOperator*, 16> WorkList;
        for (BasicBlock& BB : F) {
            for (Instruction& I : BB) {
                if (auto* BinOp = dyn_cast<BinaryOperator>(&I)) {
                    if (BinOp->getOpcode() == Instruction::Add && BinOp->getType()->isIntegerTy()) {
                        WorkList.push_back(BinOp);
                    }
                }
            }
        }

        errs() << "[MbaPass] Found " << WorkList.size() << "integer Add instructions.\n";
        if (WorkList.empty())
            return PreservedAnalyses::all();

        // Phase 2: Perform instruction substitution.
        bool Changed = false;
        for (BinaryOperator* BinOp : WorkList) {
            IRBuilder<> Builder{BinOp};
            // TODO: Substitution logic here
            (void)Builder;
        }

        return Changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
    }

    static bool isRequired() { return true; }
};

} // namespace

PassPluginLibraryInfo getMbaPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "MbaPass", LLVM_VERSION_STRING, [](PassBuilder& PB) {
                PB.registerPipelineParsingCallback([](StringRef Name, FunctionPassManager& FPM,
                                                       ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "mba") {
                        FPM.addPass(MbaPass());
                        return true;
                    }
                    return false;
                });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getMbaPassPluginInfo();
}
