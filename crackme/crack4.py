import time
from typing import Callable, List, Tuple
from z3 import BitVec, BitVecRef, Not, Solver, sat, unsat

def mba_raw(x: BitVecRef, y: BitVecRef) -> BitVecRef:
    return x + y

def mba_add_1(x: BitVecRef, y: BitVecRef) -> BitVecRef:
    """1st form: (x ^ y) + 2 * (x & y)"""
    return (x ^ y) + 2 * (x & y)

def mba_add_2(x: BitVecRef, y: BitVecRef) -> BitVecRef:
    """2nd form: (x | y) + (x & y)"""
    return (x | y) + (x & y)


MBA_CASES: List[Tuple[str, Callable[[BitVecRef, BitVecRef], BitVecRef]]] = [
    ("Baseline (x + y)", mba_raw),
    ("MBA Add 1: (x ^ y) + 2*(x & y)", mba_add_1),
    ("MBA Add 2: (x | y) + (x & y)", mba_add_2)
]

def bench_model_finding(iterations: int = 10):
    """
    Bench root finding time (SAT): MBA(x, y) == 0x12345678
    """
    print(f"\n[*] --- Benchmark 1: Model Finding (SAT) [{iterations} iters] ---")
    TARGET = 0x12345678

    for name, expr_gen in MBA_CASES:
        total_time_ns = 0
        for _ in range(iterations):
            x = BitVec('x', 32)
            y = BitVec('y', 32)
            solver = Solver()
            solver.add(expr_gen(x, y) == TARGET)

            start = time.perf_counter_ns()
            res = solver.check()
            total_time_ns += (time.perf_counter_ns() - start)

            assert res == sat, f"No solution exists for {name}"

        avg_ms = (total_time_ns / iterations) / 1_000_000
        print(f"  {name:<45} : {avg_ms:8.3f} ms")


def bench_equivalence_proving(iterations: int = 10):
    """
    Measuring time to prove equivalence: Forall x, y: MBA(x, y) == x + y
    Encode: UNSAT of Not(MBA(x, y) == x + y)
    """
    print(f"\n[*] --- Benchmark 2: Equivalence Proof (UNSAT) [{iterations} iters] ---")

    for name, expr_gen in MBA_CASES:
        total_time_ns = 0
        for _ in range(iterations):
            x = BitVec('x', 32)
            y = BitVec('y', 32)
            solver = Solver()
            
            # Equivalance negation: Find x, y which MBA(x, y) != x + y
            solver.add(Not(expr_gen(x, y) == (x + y)))

            start = time.perf_counter_ns()
            res = solver.check()
            total_time_ns += (time.perf_counter_ns() - start)

            assert res == unsat, f"Non-equivalence equations: {name}"

        avg_ms = (total_time_ns / iterations) / 1_000_000
        print(f"  {name:<45} : {avg_ms:8.3f} ms")


bench_model_finding(iterations=20)
bench_equivalence_proving(iterations=20)
