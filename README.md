<!-- To read with Atom go to >Packages>Mardown Preview -->

### Projet 2 - Fractales

For our course
[Systèmes Informatiques I](https://sites.uclouvain.be/SystInfo/), we implement
a program that generates a BMP file as output from a list of fractals as input

#### Usage

How to compile?

`$ make`

How to execute?

`$ ./main [options] file1 file2 fileN fileOut`

Options:

* `-d` builds a BMP for **each** computed fractal
* `--maxthreads n` number of maximal used computations threads

How to clean?

`$ make clean`

How to make it even cleaner?

`$ make mrproper`

#### Structure

Files without a comment have a descriptive name to understand what
they contain :

* `./libfractal/fractal.c`
* `./libfractal/fractal.h`
* `./libfractal/Makefile`
* `./libfractal/tools.c` tools to build a BMP file from a `struct fractal`
* `./LICENSE.md`
* `./main.c`
* `./Makefile`
* `./README.md`
* `./test/` contains unit tests made with CUnit
