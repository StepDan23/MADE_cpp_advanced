ARG BASE_CONTAINER=ubuntu:18.04

FROM $BASE_CONTAINER

RUN apt-get update -y && apt-get install qemu-user wget xz-utils -y

RUN wget http://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi.tar.xz
RUN wget http://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/sysroot-glibc-linaro-2.25-2018.05-arm-linux-gnueabi.tar.xz

RUN tar -xf gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi.tar.xz && mv gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi gcc-linaro
RUN tar -xf sysroot-glibc-linaro-2.25-2018.05-arm-linux-gnueabi.tar.xz && mv sysroot-glibc-linaro-2.25-2018.05-arm-linux-gnueabi sys-glibc

RUN echo 'PATH="$PATH:/gcc-linaro/bin"' >> ~/.bashrc
RUN echo 'PATH="$PATH:/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin"' >> ~/.bashrc
RUN echo 'export LINARO_SYSROOT="/sys-glibc"' >> ~/.bashrc

WORKDIR hw_code
