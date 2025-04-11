# GDB may have ./.gdbinit loading disabled by default.  In that case you can
# follow the instructions it prints.  They boil down to adding the following to
# your home directory's ~/.gdbinit file:
#
#   add-auto-load-safe-path /path/to/qemu/.gdbinit

# Load QEMU-specific sub-commands and settings

set pagination off
target remote localhost:1234

tui new-layout vmdebug {-horizontal asm 1 regs 1} 2 cmd 1
layout vmdebug
focus cmd
set confirm off

break *0x40000068 thread 1
command
break *0x00 t 1
break *0x04 t 1 
break *0x08 t 1 
break *0x0c t 1 
break *0x10 t 1 
break *0x14 t 1 
end

define lr
    x/20i $lr-40
end

define pc
    x/20i $pc-20
end

define con
    target remote localhost:1234
end

continue
