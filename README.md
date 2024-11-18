# Contest template

Setting up a contest repo based on this template:
1. Make sure all files are included (e.g. `.gitignore`)
2. Adjust README.md
3. Choose translations:
   - If not planning to use translations, remove `template/statement-*.md` and
     keep only `statement.md`
   - Otherwise, add appropriate languages to the template task

Cut here
--------

# Contest name

Useful links or info here

## Workflow for creating a new task
1. Copy `template/` as `new-task/`.
2. Write the problem statement.
3. Write a model solution in `new-task/solver.cpp`. This will be used for
   generating the correct outputs (`.out`). For multiple solutions, you can
   create multiple solvers, e.g. `new-task/solver1.cpp`. Remember add the
   corresponding binaries in `binaries=` list in `new-task/Makefile`.
4. Write a test generator in `new-task/generator.cpp`. The generator receives
   its input as arguments and produces the test case into standard output. The
   same arguments are also given to the model solution in case they are needed
   when generating the `.out` files, but they are commonly ignored.
5. Write test inputs in `new-task/tests.txt`, one test per line. Each line is
   given to test generator one-by-one.
6. If you need a custom grader, write one in `new-task/grader.cpp`. Add
   `grader` to `binaries=` list in `new-task/Makefile` to compile grader
   automatically when you run `make`.
7. Write an input checker in `new-task/checker.cpp`. The checker tests that the
   test cases are satisfy the input conditions, for example that the parameters
   are in the correct range or that the input graph is a tree. It can also
   report which subtasks an input belongs to. Checker is the only binary that
   can use functions in `.common/cseslib.hpp`.
8. While developing, you can generate tests with `make tests`. To test your
   solution, you can run `make run-tests`. If you have another solution binary,
   you can run tests against it using `make run-tests SOLUTION=build/solver1`.
   - Use the `TESTS` parameter to generate or run only specific tests, e.g.
     `TESTS='1 2 5'`.
   - Brute test solutions against the model solver with e.g. `make brutetest
     SOLUTION=build/solver1 FMT='% 5'`. The `FMT` parameter is given to the
     generator after replacing `%` with a counter to generate different tests.
9. Once you are done with everything, you can package all tests into a zip file
   by running `make package`.

## Example
```
# Create new task
cp -r template/ new-task
cd new-task
# Write generator
cat generator.cpp
    ...
    int main(int argc, char **argv) {
        // Check argument count
        if (argc != 3) usage();

        // Parse arguments into numbers
        unsigned long long seed = stoull(argv[1]);
        r_dev.seed(seed);
        r_dev64.seed(seed);

        int n = atoi(argv[2]);

        int a = rnd(-n, n);
        int b = rnd(-n, n);

        // Output the test case to the standard output
        cout << a << " " << b << '\n';
    }

# Write model solver
cat solver.cpp
    #include <bits/stdc++.h>

    using namespace std;

    int main()
    {
        int a, b;
        cin >> a >> b;
        cout << a + b << endl;
    }

# Write checker
cat checker.cpp
    #include "cseslib.hpp"
    #include <bits/stdc++.h>

    int main()
    {
        // Check that inputs are in range
        auto v = read_ints(2, -1e6, 1e6);

        end();
    }

# Write grader
cat grader.cpp
    ...
    int main(int argc, char **argv)
    {
        string x1 = argv[1]; // correct output
        string x2 = argv[2]; // user output
        string x3 = argv[3]; // input
        ifstream correct, user, input;
        correct.open(x1);
        user.open(x2);
        input.open(x3);

        int expected;
        SAFE_READ(correct >> expected);
        int got;
        SAFE_READ(user >> got);
        if (expected != got)
        {
            fail();
        }

        accept();
    }

# Write failing solution
cat failing-solver.cpp
    #include <bits/stdc++.h>

    using namespace std;

    int main()
    {
        short a, b;
        cin >> a >> b;
        cout << a + b << endl;
    }

# Describe tests
cat tests.txt
    1 2
    2 2
    3 100000

# Add new binaries to Makefile
cat Makefile
    binaries=solver generator checker grader solver failing-solver

    include ../.common/Makefile.include

# Compile everything and generate tests
make -j
make tests
# Check solution
make run-tests
    -- Running tests on build/solver graded by build/grader
    ../common/run-tests.sh 1 2 3
    Running test 1
    Running test 2
    Running test 3
make run-tests SOLUTION=build/failing-solver TESTS="1 3"
    -- Running tests on build/failing-solver graded by build/grader
    ../common/run-tests.sh 1 3
    Running test 1
    Running test 3
    Grader returned 0
    make: *** [../common/Makefile.include:38: run-tests] Error 3
# Once everything works as expected, package tests and upload them to cses.fi
make package
```
