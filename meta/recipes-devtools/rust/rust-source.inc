RUST_VERSION ?= "${@d.getVar('PV').split('-')[0]}"

SRC_URI += "https://static.rust-lang.org/dist/rustc-${RUST_VERSION}-src.tar.xz;name=rust \
            file://crossbeam_atomic.patch;patchdir=${RUSTSRC} \
            file://hardcodepaths.patch;patchdir=${RUSTSRC} \
            file://getrandom-open64.patch;patchdir=${RUSTSRC} \
            file://0001-Do-not-use-LFS64-on-linux-with-musl.patch;patchdir=${RUSTSRC} \
            file://zlib-off64_t.patch;patchdir=${RUSTSRC} \
"
SRC_URI[rust.sha256sum] = "8651245e8708f11d0f65ba9fdb394c4b9300d603d318045664b371729da9eac4"

RUSTSRC = "${WORKDIR}/rustc-${RUST_VERSION}-src"

# Used by crossbeam_atomic.patch
export TARGET_VENDOR

UPSTREAM_CHECK_URI = "https://forge.rust-lang.org/infra/other-installation-methods.html"
UPSTREAM_CHECK_REGEX = "rustc-(?P<pver>\d+(\.\d+)+)-src"

# see recipes-devtools/gcc/gcc/0018-Add-ssp_nonshared-to-link-commandline-for-musl-targe.patch
# we need to link with ssp_nonshared on musl to avoid "undefined reference to `__stack_chk_fail_local'"
# when building MACHINE=qemux86 for musl
WRAPPER_TARGET_EXTRALD:libc-musl = "-lssp_nonshared"
