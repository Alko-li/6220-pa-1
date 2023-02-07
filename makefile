EXECS=int_calc
MPICXX?=mpicxx
MPIRUN?= mpirun

all: ${EXECS}

int_calc: int_calc.cpp
	${MPICXX} -o int_calc int_calc.cpp

test: int_calc.cpp
	${MPICXX} -o int_calc int_calc.cpp
	@echo "Testing int_calc on n = 1000000"
	@echo "int_calc on 1 processor: "
	@${MPIRUN} -np 1 ./int_calc 1000000
	@echo "int_calc on 2 processors: "
	@${MPIRUN} -np 2 ./int_calc 1000000
	@echo "int_calc on 4 processors: "
	@${MPIRUN} -np 4 ./int_calc 1000000
	@echo "int_calc on 8 processors: "
	@${MPIRUN} -np 8 ./int_calc 1000000
	@echo "int_calc on 16 processors: "
	@${MPIRUN} -np 16 ./int_calc 1000000
	@echo "int_calc on 32 processors: "
	@${MPIRUN} -np 32 ./int_calc 1000000


clean:
	rm -f ${EXECS}
