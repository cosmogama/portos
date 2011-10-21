#### build kernel script ####
#
# http://wiki.osdev.org/Bare_Bones
#
#############################

## CLEAN
echo "cleaning..."
./clean.sh

## CONSTANTS
EXP_FLOPPY_SIZE=1474560

## assemble loader
nasm -f elf -o loader.o loader.s
if [ $? != "0" ]; then
  echo "failed to assemble loader.s!"
  exit 1
fi

echo "assemble loader success."

## compile kernel
cd kernel
i586-elf-gcc -c *.c *.s -Werror -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -nobuiltin -fno-builtin
# -fpack-struct
if [ $? != "0" ]; then
  echo "failed to compile kernel.c!"
  exit 1
fi
cd ..

# nasm -f elf -o kernel/GDTload.o kernel/GDTload.s
# nasm -f elf -o kernel/segm-asm.o kernel/segm-asm.s
#i586-elf-gcc -o kernel/segm.o kernel/segm.s
if [ $? != "0" ]; then
  echo "failed to assemble an assembly file!"
  exit 1
fi

echo "compile success."

## link loader to kernel
i586-elf-ld -T linker.ld -o kernel.bin loader.o kernel/*.o
if [ $? != "0" ]; then
  echo "failed to link loader to kernel!"
  exit 1
fi

echo "link loader to kernel success."

## CHECK DEPENDENCY FILES

## PAD 1 ***********************************

## create pad1 if it does not exist
## static size
if [ ! -f pad1 ]; then
 dd if=/dev/zero of=pad1 bs=1 count=750
 echo "create pad1 success."
fi

## STAGE 1 *********************************
if [ ! -f stage1 ]; then
 echo "FATAL ERROR ! put stage1 ( GRUB ) into build directory first"
 exit 1
fi

## STAGE 2 *********************************
if [ ! -f stage2 ]; then
 echo "FATAL ERROR ! put stage2 ( GRUB ) into build directory first"
 exit 1
fi

## FILE SIZES ******************************

## STAGE 1
stage1_size=$(stat -c%s "stage1")
echo "stage1 size=$stage1_size"

## STAGE 2
stage2_size=$(stat -c%s "stage2")
echo "stage2 size=$stage2_size"

## KERNEL
kernel_size=$(stat -c%s "kernel.bin")
echo "kernel size=$kernel_size"

## PAD 1
pad1_size=$(stat -c%s "pad1")
echo "pad1 size=$pad1_size"

## PAD 2
pad2_size=0

 
## RESHAPE PAD 2 / CREATE BOOTABLE FLOPPY IMAGE
let total_img_size=$stage1_size+$stage2_size+$pad1_size+$kernel_size+$pad2_size
let perc_floppy_capacity_used=$total_img_size*100/$EXP_FLOPPY_SIZE
echo "total image size before padding=$total_img_size"
echo "you have used $perc_floppy_capacity_used% capacity of your floppy disk"

if [ $total_img_size -gt "1474560" ]; then
  echo "reached maximum capacity of kernel image!  Implement me!"
  exit 1
elif [ $total_img_size -eq "1474560" ]; then
  echo "kernel image is already correct size."
elif [ $total_img_size -lt "1474560" ]; then
  let pad2_size=$EXP_FLOPPY_SIZE-$total_img_size
  dd if=/dev/zero of=pad2 bs=1 count=$pad2_size
	if [ $? != "0" ]; then
 		echo "failed to create pad2!"
  	exit 1
	fi
	echo "create pad2 success."
fi

## PAD 2
pad2_size=$(stat -c%s "pad2")
echo "pad2 size=$pad2_size"

## build kernel flat binary
rm floppy.img
cat stage1 stage2 pad1 kernel.bin pad2 > floppy.img

## FLOPPY IMAGE SIZE
floppy_img_size=$(stat -c%s "floppy.img")
echo "floppy image size=$floppy_img_size"

kernelbin_size_blocks=$(stat -c%s "kernel.bin")
let kernelbin_size_blocks=$kernelbin_size_blocks/512
if [ $kernelbin_size_blocks%512 > 0 ]; then
	let kernelbin_size_blocks=$kernelbin_size_blocks+1
fi

echo ""
echo "kernel is $kernelbin_size_blocks blocks in size"
