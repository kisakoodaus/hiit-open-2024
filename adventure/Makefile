binaries=generator checker solver

# if using custom grader
binaries+=grader
binaries+=approx-solver-non-simple
binaries+=approx-solver-shortest
binaries+=approx-solver-remove-tails
binaries+=solver-juha
binaries+=check-all
binaries+=fast-exact
binaries+=exact-any

BASE_PATH=$(shell git rev-parse --show-toplevel)

include $(BASE_PATH)/common/Makefile.include

# Use SMT solver as model solver
# $(SOLVER_BIN): smt-solver.py
# 	cp smt-solver.py $(SOLVER_BIN)
# 	chmod +x $(SOLVER_BIN)
