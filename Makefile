SRC := $(wildcard src/*.c)
# SRC := $(SRC) $(wildcard src/*.s)
OBJECTS := $(patsubst src/%.c, dist/%.o, $(SRC))
OBJECTS := $(patsubst src/%.s, dist/%.o, $(OBJECTS))

XORRISO = ..\..\ProgramFiles\i386\xorriso\bin\xorriso.exe
LD = i386-elf-ld
CC = i386-elf-gcc
AS = nasm
CP = cp
BOCHS = ../../ProgramFiles/Bochs-2.7/bochs.exe
QEMU = ../../ProgramFiles/qemu/qemu-system-i386
GRUB_MKIMAGE = ../../ProgramFiles/grub-2.06-for-windows/grub-mkimage.exe

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I./include
GRUB_MKIMAGE_FLAGS := --format=i386-pc --prefix="(cd)" loadenv biosdisk part_msdos part_gpt fat ntfs ext2 ntfscomp iso9660 loopback search linux boot minicmd cat cpuid chain halt help ls reboot echo test configfile normal sleep memdisk tar font gfxterm gettext true vbe vga video_bochs video_cirrus multiboot multiboot2

all: os.iso

dist/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

dist/%.o: src/%.s
	$(AS) -f elf $< -o $@

dist/kernel.elf: dist/loader.o $(OBJECTS)
	$(LD) -T link.ld -melf_i386 $^  -o $@

iso/boot/grub/grub.img: iso/boot/grub/grub.cfg
	$(GRUB_MKIMAGE) --output=dist/core.img --config=$< $(GRUB_MKIMAGE_FLAGS)
	cat ../../ProgramFiles/grub-2.06-for-windows/i386-pc/cdboot.img dist/core.img > $@
	# cat  dist/core.img > $@


os.iso: dist/kernel.elf iso/boot/grub/grub.img
	$(CP) ./$< ./iso/boot/
	$(XORRISO) -as mkisofs -R -b boot/grub/grub.img -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $@ iso

run: os.iso
	$(BOCHS) -f bochsrc.bxrc -q

qemu: os.iso
	$(QEMU) -cdrom $<

qemum: dist/kernel.elf
	$(QEMU) -kernel $<

test:
	echo $(OBJECTS)

# ../../ProgramFiles/grub-2.06-for-windows/grub-mkimage.exe --format=i386-pc --prefix="(cd)" --output=dist/core.img --config="iso/boot/grub/default.cfg" 
# loadenv biosdisk part_msdos part_gpt fat ntfs ext2 ntfscomp iso9660 loopback search linux boot minicmd cat cpuid chain halt help ls reboot echo test configfile normal sleep memdisk tar font gfxterm gettext true vbe vga video_bochs video_cirrus multiboot multiboot2

# cat ../../ProgramFiles/grub-2.06-for-windows/i386-pc/cdboot.img dist/core.img > dist/grub.img