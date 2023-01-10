## Installing IgH EtherCAT Master 
***Required setup : Ubuntu 22.04 LTS***

The proposed development builds upon the [IgH EtherCAT Master](https://etherlab.org/en/ethercat/). Installation steps are summarized here:
```shell
$ git clone https://gitlab.com/etherlab.org/ethercat.git
$ cd ethercat
$ git checkout stable-1.5
```
```shell
$ ./bootstrap # to create the configure script, if downloaded from the repository

$ ./configure --prefix=/usr/local/etherlab  --disable-8139too --enable-generic # Ethernet driver e1000e not supported for kernels 4.X
$ make all modules
$ sudo make modules_install install
$ sudo depmod
$ sudo ln -s /usr/local/etherlab/bin/ethercat /usr/bin/
$ sudo ln -s /usr/local/etherlab/etc/init.d/ethercat /etc/init.d/ethercat
$ sudo mkdir -p /etc/sysconfig
$ sudo cp /usr/local/etherlab/etc/sysconfig/ethercat /etc/sysconfig/ethercat
$ sudo bash -c "echo KERNEL==\"EtherCAT[0-9]*\", MODE=\"0664\", GROUP=\"ecusers\" > /etc/udev/rules.d/99-EtherCAT.rules"

$ sudo gedit /etc/sysconfig/ethercat
```
In the configuration file specify the mac address of the network card which you want to use as a ethercat master
```shell
MASTER0_DEVICE="ff:ff:ff:ff:ff:ff"  # mac address
DEVICE_MODULES="generic"
```

Now you can start the EtherCAT master:
```shell
$ sudo /etc/init.d/ethercat start
```
it should print
```shell
Starting EtherCAT master 1.5.2  done
```

Now check the slaves connected to the EtherCAT master 
```shell
$ ethercat slaves
```

it should printed info like this
```shell
0  2:0  PREOP  +  NX-ECC201 EtherCAT coupler V1.2
```