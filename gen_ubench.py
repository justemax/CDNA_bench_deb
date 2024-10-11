import os
try:
    os.remove("ubench_good.cpp")
except OSError:
    pass



file1 = open("ubench_good.cpp", "a")
file2 = open("data/header.c", "r")
file3 = open("data/footer.c", "r")

instruction = "v_mul_f64"
double_or_float = "64"
register_type = "v"
nb_register = 256

for line in file2:
    file1.write(line)
    
print("End of header")


for i in range(nb_register):
    file1.write("register float register" + str(i) + " asm(\"" + register_type + str(i) + "\");\n")
    #file1.write("float register" + str(i) + ";\n")
    file1.write("register" + str(i) + " = " + str(i) + ";\n")



file1.write("__asm__ volatile(\"s_waitcnt vmcnt(0)\");")
file1.write("\nstart = clock();\n")



#Writing the instructions
file1.write("__asm__ volatile(\n")
file1.write("\".rept 1024\\n\\t\"\n")


if double_or_float == "32":
    for i in range(0, (nb_register), 3):
        file1.write("\"" + instruction + " " + register_type + str(i) + ", " + register_type + str(i+1) + ", " + register_type + str(i+2) + "\\n\\t\"")


        file1.write("\n")

else:
    for i in range(0 , (nb_register-6), 6):
        file1.write("\"" + instruction + " " + register_type + "[" + str(i) + ":" + str(i+1) + "] , " + register_type + "[" + str(i+2) + ":" + str(i+3) + "] , " + register_type + "[" + str(i+4) + ":" + str(i+5) + "] \\n\\t\"")

        file1.write("\n")
file1.write("\".endr\\n\\t\"")
file1.write(");\n")



for line in file3:
    file1.write(line)

file1.close()
file2.close()
file3.close()


