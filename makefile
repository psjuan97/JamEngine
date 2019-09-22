.PHONY: run


TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	src src/math src/engineModules 
DATA		:=	data
INCLUDES	:=	src




current_dir := $(dir $(CURDIR) )
#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

export BUILDDIR	:=	$(CURDIR)/$(BUILD)



#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OBJS	:=	$(addsuffix .o,$(BINFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)


INCDIR = ./include
CFLAGS = -O2 -G0 -Wall -fno-exceptions -ffast-math -DNORMALUNIX -DUNROLL -Diabs=abs -fsigned-char -DPSP -std=gnu++11
#CFLAGS += -DUSE_FLOAT_FIXED
CXXFLAGS = $(CFLAGS) -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION = 371

LIBDIR = ./lib
LIBS =    -lstdc++ -lpspwlan -lpspgum -lpspgu -lpsputility -lpspaudiolib -lpspaudio -lpsppower -lm -lSDL2_ttf -lSDL2_image  -lSDL2  -lfreetype -lpng -ljpeg  -lGL -lGLU -lglut  -lz \
         -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lpspvram 
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = JamEngine
PSP_EBOOT_ICON = "PSP/icon0.png"
PSP_EBOOT_UNKPNG = "PSP/pic0.png"
PSP_EBOOT_PIC1 = "PSP/pic1.png"
#PSP_EBOOT_SND0="snd0.at3"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
endif

run:
	ppsspp $(current_dir)$(TARGET)/EBOOT.PBP




