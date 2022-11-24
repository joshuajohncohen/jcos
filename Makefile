CC=gcc
TARGET=jcos
C_FILES=./kernel.c
OBJS=$(C_FILES:.c=.o)

all compile: $(TARGET)
all: final
.PHONY: all compile clean final

%.o:
	$(CC) -c $(@:.o=.c) -o $@ -ffreestanding -fno-exceptions -m32

$(TARGET): $(OBJS)
	$(shell nasm -f elf start.asm -o start.o)
	$(CC) -m32 -nostdlib -nodefaultlibs -lgcc start.o $? -T linker.ld -o $(TARGET)

final:
	$(shell cp $(TARGET) ./iso/boot/$(TARGET))
	$(shell grub2-mkrescue iso --output=$(TARGET).iso)

clean:
	rm -f *.o $(TARGET) $(TARGET).iso
	find . -name \*.o | xargs --no-run-if-empty rm

