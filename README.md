## CTF Topic

Experimental evaluation of the symbolic execution resistance of a custom LLVM obfuscation pass 
(MBA + opaque constants) tested on a self-designed Reverse Engineering challenge suite using 
`angr/Z3` as attack tools.

## Question

Given a pre-defined runtime overhead and code size budget, which combination of transformations 
(MBA substitution, opaque constants, or a combination) most significantly increases the solving cost 
(time, memory, path explosion/timeout rate) of symbolic execution (`angr/Z3`), while keeping the 
binary's structure simple enough for a human to solve manually?
