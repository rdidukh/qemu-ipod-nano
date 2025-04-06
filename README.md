# Build

```
mkdir build
cd build
../configure --target-list=arm-softmmu
make -j16
```

# Run

```
./qemu-system-arm -M virt,firmware=osos.bin -nographic -S -s

gdb-multiarch -ex "target remote localhost:1234"
```
