{
  description = "Kernel development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # Compiler toolchain
            gcc
            binutils
            nasm

            # Debugging
            gdb

            # QEMU for testing
            qemu

            # Build tools
            gnumake
            xorriso   # for creating bootable ISO images
            grub2     # for bootloader
          ];

          shellHook = ''
            echo "Kernel dev environment ready."
            echo "QEMU available: $(qemu-system-x86_64 --version | head -1)"
          '';
        };
      });
}
