# Build

```
mkdir build
cd build
../configure --target-list=arm-softmmu
make -j16
```

# Run

```
./qemu-system-arm -M ipod-nano-1g,firmware=../../ipod/bootloader-ipodnano1g.bin -drive file=./drive.img,id=drive,if=ide -s -S -nographic
info mtree
info qtree

gdb-multiarch -x .gdbinit
```
