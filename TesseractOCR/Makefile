LEPTON_NAME = leptonica-1.72

include libtiff-ios/Common.make

TESSERACT_SRC = $(shell pwd)/tesseract-ocr
LEPTON_SRC = $(shell pwd)/$(LEPTON_NAME)
IMAGE_SRC = $(shell pwd)/libtiff-ios

IMAGE_LIB_DIR = $(IMAGE_SRC)/dependencies/lib
IMAGE_INC_DIR = $(IMAGE_SRC)/dependencies/include
INCLUDE_DIR   = $(shell pwd)/include
LEPT_INC_DIR  = $(INCLUDE_DIR)
TESS_INC_DIR  = $(INCLUDE_DIR)
LIB_FAT_DIR   = $(shell pwd)/lib

libtessfiles = libtesseract.a
libleptfiles = liblept.a
libpngfiles = libpng.a
libjpegfiles = libjpeg.a
libtifffiles = libtiff.a

libleptfolders = $(foreach config, $(config_names), $(LEPTON_SRC)/$(config)/)
libtessfolders = $(foreach config, $(config_names), $(TESSERACT_SRC)/$(config)/)
libleptfolders_all = $(foreach config, $(config_names_all), $(LEPTON_SRC)/$(config)/)
libtessfolders_all = $(foreach config, $(config_names_all), $(TESSERACT_SRC)/$(config)/)

libleptmakefile = $(foreach folder, $(libleptfolders), $(addprefix $(folder), Makefile) )
libtessmakefile = $(foreach folder, $(libtessfolders), $(addprefix $(folder), Makefile) )
imagesmakefile  = $(addprefix $(IMAGE_SRC)/, Makefile)

libleptfat = $(foreach platform, $(PLATFORMS), $(LIB_FAT_DIR)/$(platform)/$(libleptfiles))
libtessfat = $(foreach platform, $(PLATFORMS), $(LIB_FAT_DIR)/$(platform)/$(libtessfiles))
imagesfat  = $(libpngfat) $(libjpegfat) $(libtifffat)
libpngfat  = $(foreach platform, $(PLATFORMS), $(LIB_FAT_DIR)/$(platform)/$(libpngfiles))
libjpegfat = $(foreach platform, $(PLATFORMS), $(LIB_FAT_DIR)/$(platform)/$(libjpegfiles))
libtifffat = $(foreach platform, $(PLATFORMS), $(LIB_FAT_DIR)/$(platform)/$(libtifffiles))

libtess    = $(foreach folder, $(libtessfolders), $(addprefix $(folder)/lib/, $(libtessfiles)) )
liblept    = $(foreach folder, $(libleptfolders), $(addprefix $(folder)/lib/, $(libleptfiles)) )
images     = $(libpng) $(libjpeg) $(libtiff)
libpng     = $(foreach platform, $(PLATFORMS), $(addprefix $(IMAGE_LIB_DIR)/$(platform)/, $(libpngfiles)))
libjpeg    = $(foreach platform, $(PLATFORMS), $(addprefix $(IMAGE_LIB_DIR)/$(platform)/, $(libjpegfiles)))
libtiff    = $(foreach platform, $(PLATFORMS), $(addprefix $(IMAGE_LIB_DIR)/$(platform)/, $(libtifffiles)))

libtessautogen = $(TESSERACT_SRC)/autogen.sh
libtessconfig = $(TESSERACT_SRC)/configure
libleptconfig = $(LEPTON_SRC)/configure

dependant_libs = $(libtessfat) $(libleptfat) $(libpngfat) $(libjpegfat) $(libtifffat)

common_cflags = \
  	-L$(LIB_FAT_DIR)/$(call get_platform, $*) \
  	-Qunused-arguments \
  	-arch $(call get_arch, $*) \
  	-pipe \
  	-no-cpp-precomp \
  	-isysroot $$SDKROOT \
  	$(call get_min_version $*) \
  	-O2

.PHONY : all
all : $(dependant_libs)

#######################
# TESSERACT-OCR
#######################
$(libtessfat) : $(libtess)
	mkdir -p $(@D)
	$(eval p = $(notdir $(@D)))
	$(eval p_folders = $(call filter_by_platform, $(p), $(libtessfolders_all)))
	xcrun lipo $(realpath $(addsuffix lib/$(@F), $(p_folders)) ) -create -output $@
	mkdir -p $(TESS_INC_DIR)
	cp -rvf $(firstword $(libtessfolders))/include/tesseract $(TESS_INC_DIR)

$(libtess) : $(libtessmakefile)
	cd $(abspath $(@D)/..) && $(MAKE) -sj8 && $(MAKE) install

$(TESSERACT_SRC)/%/Makefile : $(libtessconfig) $(libleptfat)
	export LIBS="-lz -lpng -ljpeg -ltiff" ; \
	export SDKROOT="$(call get_sdk, $*)" ; \
	export CFLAGS="-I$(TESSERACT_SRC)/$*/ $(common_cflags) -fembed-bitcode" ; \
	echo export CFLAGS="-I$(TESSERACT_SRC)/$*/ $(common_cflags) -fembed-bitcode" ; \
	export CPPFLAGS=$$CFLAGS ; \
	export CXXFLAGS="-I$(TESSERACT_SRC)/$*/ $(common_cflags) -Wno-deprecated-register"; \
	export LDFLAGS="-L$$SDKROOT/usr/lib/ -L$(LEPTON_SRC)/$*/src/.libs" ; \
	export LIBLEPT_HEADERSDIR=$(TESSERACT_SRC)/$*/ ; \
	mkdir -p $(@D) ; \
	cd $(@D) ; \
	ln -s $(LEPTON_SRC)/src/ leptonica ; \
	../configure --host=$(call get_host_name, $*) --prefix=`pwd` --enable-shared=no --disable-graphics

$(libtessconfig) : $(libtessautogen)
	cd $(@D) && ./autogen.sh 2> /dev/null

#######################
# LEPTONLIB
#######################
$(libleptfat) : $(liblept)
	mkdir -p $(@D)
	$(eval p = $(notdir $(@D)))
	$(eval p_folders = $(call filter_by_platform, $(p), $(libleptfolders_all)))
	xcrun lipo $(realpath $(addsuffix lib/$(@F), $(p_folders)) ) -create -output $@
	mkdir -p $(LEPT_INC_DIR)
	cp -rvf $(firstword $(libleptfolders))/include/leptonica $(LEPT_INC_DIR)

$(liblept) : $(libleptmakefile)
	cd $(abspath $(@D)/..) ; \
	$(MAKE) -sj8 && $(MAKE) install

$(LEPTON_SRC)/%/Makefile : $(imagesfat) $(libleptconfig)
	export LIBS="-lz -lpng -ljpeg -ltiff" ; \
	export SDKROOT="$(call get_sdk, $*)" ; \
	export CFLAGS="-I$(INCLUDE_DIR) $(common_cflags) -fembed-bitcode" ; \
	export CPPFLAGS=$$CFLAGS ; \
	export CXXFLAGS="-I$(INCLUDE_DIR) $(common_cflags) -Wno-deprecated-register"; \
    export LDFLAGS="-L$$SDKROOT/usr/lib/ -L$(LIB_FAT_DIR)/$(call get_platform, $*)/" ; \
	mkdir -p $(@D) ; \
	cd $(@D) ; \
    ../configure --host=$(call get_host_name, $*) --prefix=`pwd` --enable-shared=no --disable-programs --with-zlib --with-libpng --with-jpeg --without-giflib --with-libtiff

#######################
# Build libtiff and all of it's dependencies
#######################
$(LIB_FAT_DIR)/%.a : $(IMAGE_LIB_DIR)/%.a
	mkdir -p $(@D)
	cp -rvf $? $(@D)
	mkdir -p $(INCLUDE_DIR)
	cp -rvf $(IMAGE_INC_DIR)/ $(INCLUDE_DIR)

$(images) : $(imagesmakefile) FORCE
	cd $(IMAGE_SRC); \
	$(MAKE)

#######################
# Download dependencies
#######################
$(imagesmakefile) $(libtessautogen) :
	git submodule init
	git submodule update

$(libleptconfig) :
	curl http://leptonica.org/source/$(LEPTON_NAME).tar.gz | tar -xpf-

#######################
# Clean
#######################
.PHONY : clean
clean : cleanimages cleanlept cleantess

.PHONY : distclean
distclean : distcleanimages distcleanlept distcleantess

.PHONY : mostlyclean
mostlyclean : mostlycleanimages mostlycleanlept mostlycleantess

.PHONY : cleanimages
cleanimages :
	cd $(IMAGE_SRC) ; \
	$(MAKE) clean

.PHONY : cleanlept
cleanlept :
	for folder in $(realpath $(libleptfolders_all) ); do \
        cd $$folder; \
        $(MAKE) clean; \
	done ;

.PHONY : cleantess
cleantess :
	for folder in $(realpath $(libtessfolders_all) ); do \
        cd $$folder; \
        $(MAKE) clean; \
    done ;

.PHONY : mostlycleanimages
mostlycleanimages :

.PHONY : mostlycleanlept
mostlycleanlept :
	for folder in $(realpath $(libleptfolders) ); do \
        cd $$folder; \
        $(MAKE) mostlyclean; \
    done ;

.PHONY : mostlycleantess
mostlycleantess :
	for folder in $(realpath $(libtessfolders_all) ); do \
        cd $$folder; \
        $(MAKE) mostlyclean; \
    done ;

.PHONY : distcleanimages
distcleanimages :
	-rm -rf $(IMAGE_SRC)

PHONY : distcleanlept
distcleanlept :
	-rm -rf $(LEPT_INC_DIR)/leptonica
	-rm -rf $(libleptfat)
	-rm -rf $(LEPTON_SRC)

.PHONY : distcleantess
distcleantess :
	-rm -rf $(TESS_INC_DIR)/tesseract
	-rm -rf $(libtessfat)
	-rm -rf $(TESSERACT_SRC)

.PHONY : FORCE
FORCE :
