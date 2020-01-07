# LinearSolver

## Compile

Use CMake to compile.

Type in the following commands:

```
cd src/
mkdir build
cd build/
cmake ..
make
```

## Usage

In order to compile a specific solver (e.g. simplex method using big-M), uncomment the corresponding macro defined in `utility.h`.

```
#define SIMPLEX_BIG_M
//#define SIMPLEX_DOUBLE_STAGE
//#define DUAL
```

## Test

Enter the `data/` directory first.

For the validation of simplex method:

- `bash simplex_test.sh [PATH TO SIMPLEX SOLVER]` 

  e.g. `bash simplex_test.sh ./simplex_big_m.exe` or `bash simplex_test.sh ./simplex_double_stage.exe`

For the validation of dual method:

- `bash dual_test.sh [PATH TO DUAL SOLVER]`

  e.g. `bash dual_test.sh ./dual.exe`

After the execution of each script, a test log will be generated in current directory, and the complete output of the program is shown in stdout.