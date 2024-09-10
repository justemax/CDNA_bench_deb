file1 = open("ubench.cpp", "a")
file2 = open("data/header.c", "r")
file3 = open("data/footer.c", "r")

instruction = "s_add_u32"
register_type = "s"
nb_register = 255

for line in file2:
    file1.write(line)
    
print("End of header")


for i in range(nb_register):
    file1.write("uint32_t register" + str(i) + " = 12;\n")




file1.write("\nstart = clock();\n")

for i in range(0, nb_register-1, 2):
    file1.write("__asm__ volatile(\"" + instruction + " %0, %1, %2;\": \"=" + register_type + "\"(register" + str(i) + ") : \""+ register_type + "\"(register" + str(i+1) + ") , \""+ register_type + "\"(register" + str(i) + "));")
    file1.write("\n")


for line in file3:
    file1.write(line)

file1.close()
file2.close()
file3.close()


