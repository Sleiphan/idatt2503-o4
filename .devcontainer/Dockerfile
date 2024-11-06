# FROM debian:latest AS base
# RUN apt update
# RUN apt install -y clang lldb make cmake git gh rustc cargo binutils nasm

FROM alpine:latest AS base
RUN apk update
RUN apk add gcc g++ gdb boost-dev make cmake git github-cli rust cargo binutils nasm openssl-dev netcat-openbsd
