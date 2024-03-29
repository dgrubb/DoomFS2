JO_COMPILE_WITH_VIDEO_MODULE = 0
JO_COMPILE_WITH_BACKUP_MODULE = 0
JO_COMPILE_WITH_TGA_MODULE = 1
JO_COMPILE_WITH_AUDIO_MODULE = 1
JO_COMPILE_WITH_3D_MODULE = 0
JO_COMPILE_WITH_PSEUDO_MODE7_MODULE = 0
JO_COMPILE_WITH_EFFECTS_MODULE = 0
JO_PSEUDO_SATURN_KAI_SUPPORT = 1
JO_COMPILE_WITH_DUAL_CPU_MODULE = 1
JO_COMPILE_WITH_SOFTWARE_RENDERER_MODULE = 1
JO_DEBUG = 1
JO_NTSC = 1
JO_COMPILE_USING_SGL=1
SRCS=main.c \
	 src/hud/stuff.c \
	 src/game/game_main.c \
	 src/game/title.c \
	 src/menu/menu_main.c \
	 src/menu/misc.c \
	 src/play/setup.c \
	 src/renderer/renderer_main.c \
	 src/sys/sys_util.c \
	 src/video/video.c \
	 src/wad/wad_main.c
CCFLAGS += -I./src/
JO_ENGINE_SRC_DIR=../../jo_engine
COMPILER_DIR=../../Compiler
include $(COMPILER_DIR)/COMMON/jo_engine_makefile
