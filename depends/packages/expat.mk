package=expat
<<<<<<< HEAD
$(package)_version=2.2.5
$(package)_download_path=https://github.com/libexpat/libexpat/releases/download/R_2_2_5/
$(package)_file_name=$(package)-$($(package)_version).tar.bz2
$(package)_sha256_hash=d9dc32efba7e74f788fcc4f212a43216fc37cf5f23f4c2339664d473353aedf6

define $(package)_set_vars
$(package)_config_opts=--disable-static
=======
$(package)_version=2.2.7
$(package)_download_path=https://github.com/libexpat/libexpat/releases/download/R_2_2_7/
$(package)_file_name=$(package)-$($(package)_version).tar.bz2
$(package)_sha256_hash=cbc9102f4a31a8dafd42d642e9a3aa31e79a0aedaa1f6efd2795ebc83174ec18

define $(package)_set_vars
  $(package)_config_opts=--disable-shared --without-docbook --without-tests --without-examples
  $(package)_config_opts_linux=--with-pic
>>>>>>> upstream/master
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
  rm lib/*.la
endef
