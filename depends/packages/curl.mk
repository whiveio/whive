package=curl
$(package)_version=7.78.0
$(package)_dir=7_78_0
$(package)_download_path=https://github.com/curl/curl/releases/download/$(package)-$($(package)_dir)
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=ed936c0b02c06d42cf84b39dd12bb14b62d77c7c4e875ade022280df5dcc81d7
define $(package)_set_vars
   $(package)_config_opts=--disable-shared --without-ssl --disable-libevent-regress --disable-samples
   $(package)_config_opts_release=--disable-debug-mode
   $(package)_config_opts_linux=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install $($(package)_build_opts)
endef

define $(package)_postprocess_cmds
endef

