# Build

```
mkdir build
cd build
../configure --target-list=arm-softmmu
make -j16
```

# Run

```
./qemu-system-arm -M ipod-nano-1g,firmware=osos.bin -nographic -S -s

gdb-multiarch -x .gdbinit
```
