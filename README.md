# MicroKernelOS - Professional Microkernel Operating System

![MicroKernelOS Architecture](https://example.com/architecture-diagram.png) *Conceptual Architecture Diagram*

MicroKernelOS is an educational operating system featuring a production-grade microkernel architecture with custom bootloader, virtual file system, and hybrid text-based UI. It implements core OS concepts with enterprise-style modularity, supporting file operations through both CLI and GUI interfaces with protected memory isolation and IPC mechanisms.

## Features

- **Hybrid Boot Architecture**: Custom ASM bootloader + GRUB stage2 for BIOS/UEFI compatibility
- **Microkernel Core**: Essential services (VFS, IPC, Scheduler) in isolated user-space processes
- **Dual UI System**: CLI shell with POSIX-like commands + component-based text GUI
- **Virtual File System**: Inode-based RAM filesystem with create/delete/rename operations
- **Protected Memory**: Paging with privilege-level isolation (Ring 0-3)
- **Professional UI**: Modal dialogs, component rendering, and keyboard event handling
- **Error Resilience**: Graceful exception handling with user-friendly feedback

## Tech Stack

**Low-Level:**
- **NASM**: Bootloader and protected mode assembly routines
- **GCC Cross-Compiler**: Kernel-space C code compilation
- **GNU LD**: Custom kernel linking with memory alignment

**Kernel:**
- **GDT/IDT**: Protected mode segmentation and interrupt handling
- **VFS Layer**: Abstract filesystem operations with RAMFS implementation
- **PMM**: Physical Memory Manager with bitmap allocation
- **VMM**: Virtual Memory Manager with demand paging

**UI Framework:**
- **VGA Text Engine**: Attribute-based rendering (colors, positioning)
- **Component Architecture**: Buttons, text fields, modal dialogs
- **Event Bus**: Keyboard → Component event propagation
- **Focus Management**: Tab-ordered component navigation

## Installation & Building

**Prerequisites:**
```bash
sudo apt-get update
sudo apt-get install -y nasm gcc make qemu-system-x86 grub-pc-bin xorriso mtools
