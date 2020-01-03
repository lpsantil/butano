
#---------------------------------------------------------------------------------------------------------------------
# Options for code generation
#---------------------------------------------------------------------------------------------------------------------
ARCH        :=	-mthumb -mthumb-interwork

CFLAGS      :=	-Wall -Wextra -g -O2 -flto -mcpu=arm7tdmi -mtune=arm7tdmi -ffast-math -DNDEBUG $(ARCH)
CFLAGS      +=	$(INCLUDE)
CFLAGS      +=	$(USERFLAGS)

CXXFLAGS    :=	$(CFLAGS) -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics

ASFLAGS     :=	-g $(ARCH)
LDFLAGS     =	-g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------------------------------------------
# Any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------------------------------------------
LIBS        :=  -ltonc -lmm

#---------------------------------------------------------------------------------------------------------------------
# List of directories containing libraries, this must be the top level containing include and lib directories
#---------------------------------------------------------------------------------------------------------------------
LIBDIRS     :=	$(LIBGBA) $(DEVKITPRO)/libtonc $(LIBBUTANOABS)

#---------------------------------------------------------------------------------------------------------------------
# List of directories containing all butano source files
#---------------------------------------------------------------------------------------------------------------------
BTNSOURCES  :=	$(LIBBUTANOABS)/src $(LIBBUTANOABS)/hw/src $(LIBBUTANOABS)/hw/3rd_party/posprintf/src

#---------------------------------------------------------------------------------------------------------------------
# No real need to edit anything past this point unless you need to add additional rules for different file extensions
#---------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------
# Don't remove intermediary files (avoid rebuilding graphics files more than once)
#---------------------------------------------------------------------------------------------------------------------
.SECONDARY:

ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------------------------------------------
 
export OUTPUT	:=	$(CURDIR)/$(TARGET)
 
export VPATH	:=  	$(foreach dir,	$(SOURCES),	$(CURDIR)/$(dir)) \
                        $(foreach dir,	$(BTNSOURCES),	$(dir)) \
                        $(foreach dir,	$(DATA),	$(CURDIR)/$(dir)) \
                        $(foreach dir,	$(GRAPHICS),	$(CURDIR)/$(dir))

export DEPSDIR	:=  	$(CURDIR)/$(BUILD)

CFILES          :=  	$(foreach dir,	$(SOURCES),	$(notdir $(wildcard $(dir)/*.c))) \
			$(foreach dir,	$(BTNSOURCES),	$(notdir $(wildcard $(dir)/*.c)))
CPPFILES        :=	$(foreach dir,	$(SOURCES),	$(notdir $(wildcard $(dir)/*.cpp))) \
			$(foreach dir,	$(BTNSOURCES),	$(notdir $(wildcard $(dir)/*.cpp)))
SFILES          :=	$(foreach dir,	$(SOURCES),	$(notdir $(wildcard $(dir)/*.s))) \
			$(foreach dir,	$(BTNSOURCES),	$(notdir $(wildcard $(dir)/*.s)))
BINFILES        :=	$(foreach dir,	$(DATA),	$(notdir $(wildcard $(dir)/*.*))) \
			_btn_audio_soundbank.bin
GRAPHICSFILES	:=	$(foreach dir,	$(GRAPHICS),	$(notdir $(wildcard $(dir)/*.bmp)))

#---------------------------------------------------------------------------------------------------------------------
# Use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------------------------------------------
    export LD   :=  $(CC)
#---------------------------------------------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------------------------------------------
    export LD	:=  $(CXX)
#---------------------------------------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------------------------------------

export OFILES_BIN       :=  $(addsuffix .o,$(BINFILES))

export OFILES_GRAPHICS	:=  $(GRAPHICSFILES:.bmp=_btn_graphics.o)

export OFILES_SOURCES   :=  $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
 
export OFILES           :=  $(OFILES_BIN) $(OFILES_GRAPHICS) $(OFILES_SOURCES)

#---------------------------------------------------------------------------------------------------------------------
# Don't generate header files from audio soundbank (avoid rebuilding all sources when audio files are updated)
#---------------------------------------------------------------------------------------------------------------------
export HFILES           :=  $(filter-out _btn_audio_soundbank_bin.h,$(addsuffix .h,$(subst .,_,$(BINFILES))))

export INCLUDE          :=  $(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
                                $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                                -I$(CURDIR)/$(BUILD)
 
export LIBPATHS         :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean
 
#---------------------------------------------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(PYTHON) $(LIBBUTANOABS)/tools/butano-audio-tool.py --audio="$(AUDIO)" --build=$(BUILD)
	@$(PYTHON) $(LIBBUTANOABS)/tools/butano-graphics-tool.py --info=$(CURDIR)/graphics.json \
		--graphics="$(GRAPHICS)" --build=$(BUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba 

#---------------------------------------------------------------------------------------------------------------------
else
 
#---------------------------------------------------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------------------------------------------------

$(OUTPUT).gba       :   $(OUTPUT).elf

$(OUTPUT).elf       :	$(OFILES)

$(OFILES_SOURCES)   :   $(HFILES)

#---------------------------------------------------------------------------------------------------------------------
# The bin2o rule should be copied and modified for each extension used in the data directories
#---------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------------------------------------------
%.bin.o	%_bin.h : %.bin
#---------------------------------------------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------------------------------------