## Installing IgH EtherCAT Master 
***Required setup : Ubuntu 22.04 LTS***

The proposed development builds upon the [IgH EtherCAT Master](https://etherlab.org/en/ethercat/). Installation steps are summarized here:
```shell
$ sudo apt-get update
$ sudo apt-get upgrade
$ git clone https://gitlab.com/etherlab.org/ethercat.git
$ cd ethercat
$ git checkout stable-1.5
$ sudo apt-get install autoconf
$ sudo apt-get install libtool
$ sudo rm /usr/bin/ethercat
$ sudo rm /etc/init.d/ethercat
$ ./bootstrap 
$ ./configure --prefix=/usr/local/etherlab  --disable-8139too --enable-generic
$ make all modules
$ sudo make modules_install install
$ sudo depmod
$ sudo ln -s /usr/local/etherlab/bin/ethercat /usr/bin/
$ sudo ln -s /usr/local/etherlab/etc/init.d/ethercat /etc/init.d/ethercat
$ sudo mkdir -p /etc/sysconfig
$ sudo cp /usr/local/etherlab/etc/sysconfig/ethercat /etc/sysconfig/ethercat
$ sudo groupadd ecusers
$ sudo usermod -a -G ecusers $whoami
$ sudo bash -c "echo KERNEL==\"EtherCAT[0-9]*\", MODE=\"0664\", GROUP=\"ecusers\" > /etc/udev/rules.d/99-EtherCAT.rules"
```

open **Setting->Network** and then plug the EtherCAT cable to the RJ45 port you want to keep for EtherCAT communication and check if an EtherCAT interface started glowing. If yes, then that RJ45 port is the one connected to EtherCAT cable. 

If the new EtherCAT interface didn't glow then we can use ```ip address``` command before and after connecting the EtherCAT cable. The one connected to EtherCAT slaves will show additional info like

```shell
inet6 fe80::7b5d:8210:946:6269/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever 
```

or the EtherCAT interface will show LOWER_UP by running ```ip address``` command after connecting the EtherCAT cable.

```shell
<NO-CARRIER,BROADCAST,MULTICAST,UP>  #before
<BROADCAST,MULTICAST,UP,LOWER_UP>    #after
```

Also by running ```ifconfig``` this ethernet interface won't show ipv4

then go to **Setting->Network** and click on the Setting of the EtherCAT interface and select **Link-Local Only** in IPv4 and IPv6 section.

In the configuration file specify the mac address of the network card which you want to use as a ethercat master. We can get the mac address by running ```ifconfig```

```shell
$ sudo gedit /etc/sysconfig/ethercat
```
and change the MASTER0_DEVICE mac address and set DEVICE_MODULES as generic
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
```shell
$ sudo chmod 777 /dev/EtherCAT0
```

Now check the slaves connected to the EtherCAT master 
```shell
$ ethercat slaves
```

it should printed info like this
```shell
0  2:0  PREOP  +  NX-ECC201 EtherCAT coupler V1.2
```

If installation is successful and the ethercat slaves aren't detected by running ```ethercat slaves``` command then try connecting EtherCAT cable to different port if available and change mac address in ```/etc/sysconfig/ethercat``` file
