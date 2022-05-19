package=curl
$(package)_version=7.78.0
$(package)_dir=7_78_0
$(package)_download_path=https://github.com/curl/curl/releases/download/$(package)-$($(package)_dir)
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=ed936c0b02c06d42cf84b39dd12bb14b62d77c7c4e875ade022280df5dcc81d7

define $(package)_set_vars
   $(package)_cxxflags=-std=c++17 -fvisibility=hidden
   $(package)_config_opts_release=--disable-debug-mode
   $(package)_config_opts_linux=--with-pic
endef

define $(package)_config_cmds
    ./configure --host=x86_64-w64-mingw32 --without-ssl 
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  mkdir -p $($(package)_staging_prefix_dir)/include/curl $($(package)_staging_prefix_dir)/lib &&\
        install $($(package)_extract_dir)/include/curl/*.h $($(package)_staging_prefix_dir)/include/curl &&\
	install $($(package)_extract_dir)/lib/.libs/libcurl-4.dll $($(package)_staging_prefix_dir)/lib
endef

define $(package)_postprocess_cmds
   rm -f $($(package)_extract_dir)/*
endef

