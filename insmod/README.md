# Introduction
Kernel modules are piece of code, that can be loaded and unloaded from kernel on demand.
They are basically a group of compiled object files that forms the kernel objects(ko).
Some modules are loaded by the kernel statically which may cause disaster when removed manually. The core kernel related modules should not be removed. Some modules are loaded dynamically depending on an event or requirement. These dynamically loaded kernel modules(DLKM) can be loaded and unloaded dynamically. For example, when you insert a USB stick in a linux machine, it loads the related DLKMs and they perform the necessary actions to register the USB device with the kernel. The DLKMs are unloaded when USB device is removed.

# Basic commands

1. lsmod
This command is used to check the list of all kernel modules loaded currently. This also displays the DLKMs that are depending on this module.
```
$ lsmod
nf_nat_masquerade_ipv4    16384  1 ipt_MASQUERADE
iptable_nat            16384  1 
nf_conntrack_ipv4      16384  2 
nf_defrag_ipv4         16384  1 nf_conntrack_ipv4
nf_nat_ipv4            16384  1 iptable_nat
iptable_filter         16384  1 
ip_tables              24576  2 iptable_filter,iptable_nat
x_tables               36864  7 ip_tables,xt_tcpudp,ipt_MASQUERADE,xt_conntrack,xt_nat,iptable_filter,xt_addrtype
nf_nat                 24576  3 nf_nat_ipv4,xt_nat,nf_nat_masquerade_ipv4
nf_conntrack          102400  5 nf_nat,nf_nat_ipv4,xt_conntrack,nf_nat_masquerade_ipv4,nf_conntrack_ipv4
```

2. insmod
This command inserts the DLKMs if its not already loaded. Let us use this repo to understand the command.
```
$ cd insmod # To go to the insmod demo directory
$ make # compile the code
$ insmod insmod.ko # To insert the DLKM
$ dmesg  # To see kernel prints
```

3. rmmod
This command removes the DLKMs if already loaded.
```
$ rmmod insmod.ko
```
4. modinfo
This command gives the metadata of the DLKM. This is usually the data that is specified and maintained by the author of the module.
```
$ modinfo
```

# Play with linux
Go to every folder in the workspace, compile and talk with the linux!



