#!usr/bin/env python3

from z3 import BitVecNumRef, BitVec, Solver, sat

x = BitVec('x', 32)

s = Solver()
s.add(x * 0x13371337 == -0x21524111)

if s.check() == sat:
    m = s.model()
    vars_list = [x]

    for var in vars_list:
        val_expr = m.eval(var, model_completion=True)
        assert isinstance(val_expr, BitVecNumRef)
        val = val_expr.as_long()
        print(f"{var} = {hex(val)}")
else:
    print("No solution exists")
