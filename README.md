# Build

```
mkdir build
cd build
../configure --target-list=arm-softmmu --enable-gtk --enable-vte
make -j16
```

# Run

```
./qemu-system-arm -M ipod-nano-1g,firmware=../../ipod/bootloader-ipodnano1g.bin -drive file=./drive.img,id=drive,if=ide -s -S -nographic
info mtree
info qtree

# With display (not implemented yet):
./qemu-system-arm -M ipod-nano-1g,firmware=../../ipod/bootloader-ipodnano1g.bin -drive file=./drive.img,if=ide,format=raw -trace ide* -display gtk,show-tabs=on -s -S

gdb-multiarch -x .gdbinit
```
