global loader                   ; the entry symbol for ELF
extern kmain

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
; FLAGS        equ 0x00000004     ; multiboot flags
FLAGS        equ 0x00 ; multiboot flags
CHECKSUM     equ -(MAGIC_NUMBER+FLAGS)  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
  resb KERNEL_STACK_SIZE

section .multiboot
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

    dd 0
    dd 0
    dd 0
    dd 0
    dd 0

    dd 0
    dd 1024
    dd 768
    dd 32


section .text:                  ; start of the text (code) section
loader:                         ; the loader label (defined as entry point in linker script)
  mov esp, kernel_stack + KERNEL_STACK_SIZE
  push ebx
  call kmain
    
.loop:
    jmp .loop                   ; loop forever

;;;;;;;;;;;;;;;;;;;
global outb
outb:
  mov al, [esp + 8] ; Data
  mov dx, [esp + 4] ; port
  out dx, al
  ret

global inb
inb:
  mov dx, [esp + 4] ; port
  in al, dx
  ret