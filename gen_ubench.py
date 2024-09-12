file1 = open("ubench.cpp", "a")
file2 = open("data/header.c", "r")
file3 = open("data/footer.c", "r")

instruction = "v_mul_f64"
register_type = "v"
nb_register = 128

for line in file2:
    file1.write(line)
    
print("End of header")


for i in range(nb_register):
    #file1.write("register float register" + str(i) + " asm(\"" + register_type + str(i) + "\");\n")
    file1.write("float register" + str(i) + ";\n")
    file1.write("register" + str(i) + " = " + str(i) + ";\n")



file1.write("__asm__ volatile(\"s_waitcnt vmcnt(0)\");")


file1.write("\nstart = clock();\n")
#file1:write("for(int i = 0; i < 1000; i++){")
file1.write("__asm__ volatile(")
j = 0
#Writing the instructions
for i in range(0, (nb_register), 3):
    #file1.write("__asm__ volatile(\"" + instruction + " %0, %1, %2;\": \"=" + register_type + "\"(register" + str(i) + ") : \""+ register_type + "\"(register" + str(i+1) + ") , \""+ register_type + "\"(register" + str(i) + "));")
    file1.write("\"" + instruction + " ")
    file1.write(" %" + str(i) + " ,%" + str(i+1) + " ,%" + str(i+2) + "\"\n\t") 
    file1.write("\n")

file1.write(":")

#writing the out register
for i in range(0, (nb_register), 2):
    file1.write("\"=" + register_type + "\"(register" + str(i) + "),\n" )

file1.write(":")
for i in range(0, (nb_register), 2):
    file1.write("\"=" + register_type + "\"(register" + str(i+1) + "), \"=" + register_type + "\"(register" + str(i) + "),\n")

file1.write(")\n\n")



for line in file3:
    file1.write(line)

file1.close()
file2.close()
file3.close()


