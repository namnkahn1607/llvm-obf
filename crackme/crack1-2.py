#!usr/bin/env python3

from z3 import BitVecNumRef, BitVecs, Solver, sat

a, b, c, d = BitVecs('a b c d', 32)

s = Solver()
s.add(a + b == 0x11223344)
s.add(b ^ c == 0x55667788)
s.add(c - d == -0x66554434)
s.add((d ^ a) + c == -0x21524111)

if s.check() == sat:
    m = s.model()
    vars_list = [a, b, c, d]

    for var in vars_list:
        val_expr = m.eval(var, model_completion=True)
        assert isinstance(val_expr, BitVecNumRef)
        val = val_expr.as_long()
        print(f"{var} = {hex(val)}")
else:
    print("No solution exists")
