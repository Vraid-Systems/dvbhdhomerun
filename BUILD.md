BUILD dvbhdhomerun
============
Standard build is just a `make` command away in the `kernel` and `userhdhomerun`
directories. Cross-compiling ... not so much.

setup CROSS_COMPILE tools
------------
I attempted to roll a cross-compile environment in Cygwin for several hours
and gave up. Everything was so much easier on a Debian 7 VM.

1. http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/arm-gnu-linux
2. Run the installer. Something like: `./arm-2013.05-24-arm-none-linux-gnueabi.bin`
3. In `~/.profile`, stick in:
`PATH="/root/CodeSourcery/Sourcery_CodeBench_Lite_for_ARM_GNU_Linux/bin:$PATH"`
... or wherever you pointed the installer to.

build XIOS M3 kernel (substitute repo for other kernel)
------------
1. `git clone https://github.com/Pivosgroup/buildroot-linux-kernel-m3.git buildroot-linux-kernel-m3`
2. `cd buildroot-linux-kernel-m3`
3. Something like `scp root@xbmc.:/proc/config.gz .` to pull down the XIOS
kernel config from your box. The password is `letmein`.
4. `zcat config.gz > .config`
5. `make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- oldconfig`

For more on this matter, see example with Rasberry PI:
http://bchavez.bitarmory.com/archive/2013/01/16/compiling-kernel-modules-for-raspberry-pi.aspx

build/load dvb .ko's for ARM A9 Cortex
------------
- make clean
- make CROSS_COMPILE=arm-none-linux-gnueabi- CFLAGS="-march=armv7-a -mcpu=cortex-a9 -marm -mlittle-endian -mglibc"
KERNEL_DIR=path/to/buildroot-linux-kernel-m3
- copy `dvb_hdhomerun_core.ko`, `dvb_hdhomerun_fe.ko`, `dvb_hdhomerun.ko` over
to your ARM box and load them:
    1. `insmod dvb_hdhomerun_core.ko`
    2. `insmod dvb_hdhomerun_fe.ko`
    3. `insmod dvb_hdhomerun.ko`
    4. `modprobe dvb_hdhomerun`

build/load userhdhomerun for ARM A9 Cortex
------------
- Be sure to set the `SET(LIBHDHOMERUN_PATH /usr/lib/libhdhomerun)` line in
`CMakeLists.txt` correctly to the location of your cross compiled libhdhomerun.
- make CC=arm-none-linux-gnueabi-gcc CXX=arm-none-linux-gnueabi-g++ CFLAGS="-march=armv7-a -mcpu=cortex-a9 -marm -mlittle-endian -mglibc"
- `scp build/userhdhomerun root@xbmc.:/media/sdcard/hdhomerun/` or the like
