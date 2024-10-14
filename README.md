#CDNA throuput microbenchmark

## How to use it
launch python file with python

To change instruction, open python file and modify

instruction

double_or_float

register_type

nb_register

number_of_variable

## How it work


This microbenchmark generator works as follows. We have a GPU kernel in which we generate inline assembly code.

In this inline assembly, we place the maximum number of independent instructions based on the register, up to 256 registers for vector registers, for example.

Then, we use the retpt loop to execute them multiple times to stabilize the measurement (1024 repetitions in our case).

We run this kernel 1000 times, and then we calculate the average.

This gives us the average number of cycles required to execute a block of x instructions 1024 times.

