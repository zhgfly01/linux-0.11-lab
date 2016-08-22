Linux 0.11 Lab
==============

## Build on Ubuntu 16.04 64 bit


### Hack Linux 0.11 on Linux

    $ make help		// get help
    $ make  		// compile
    $ make start-hd	// boot it on qemu with hard disk image
    $ make debug-hd	// debug it via qemu & gdb, you'd start gdb to connect it.
    $ make start-hd G=0 // Use curses based terminal instead of graphics, friendly for ssh login

    $ gdb images/kernel.sym
    (gdb) target remote :1234
    (gdb) b main
    (gdb) c

    $ gdb boot/bootsect.sym  // debug bootsect, step one instruction
    (gdb) target remote :1234
    (gdb) b _start
    (gdb) si

    $ gdb boot/setup.sym     // debug setup, similar as above
    (gdb) target remote :1234
    (gdb) b _start
    (gdb) si



## Hack Rootfs

Three different root filesystem images are stored in `rootfs/`:

* rootram.img -- RAM image
* rootimage   -- Floppy image
* hdc-0.11.img-- Harddisk image

### Ram image

`rootram.img` is mountable directly:

    $ mkdir /path/to/rootram/
    $ sudo mount -o rootfs/rootram.img /path/to/rootram/

### Floppy image

`rootimage-0.11` is a minix filesystem, must with `-t minix` obviously:

    $ sudo mkdir /path/to/rootimage/
    $ sudo mount -t minix rootfs/rootimage-0.11 /path/to/rootimage

### Harddisk image

`hdc-0.11.img` has a partition table, should be mounted with an offset:

    $ mkdir /path/to/hdc/
    $ fdisk -lu rootfs/hdc-0.11.img
    $ fdisk -l rootfs/hdc-0.11.img

    Disk rootfs/hdc-0.11.img: 127 MB, 127631360 bytes
    16 heads, 38 sectors/track, 410 cylinders, total 249280 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O size (minimum/optimal): 512 bytes / 512 bytes
    Disk identifier: 0x00000000

                  Device Boot      Start         End      Blocks   Id  System
    rootfs/hdc-0.11.img1               2      124031       62015   81  Minix / old Linux
    rootfs/hdc-0.11.img2          124032      248063       62016   81  Minix / old Linux

    $ sudo mount -o offset=$((2*512)) rootfs/hdc-0.11.img /path/to/hdc/

# Examples

Some examples are stored in `examples/` with their own README.md:

* syscall -- shows how to add a new system call

